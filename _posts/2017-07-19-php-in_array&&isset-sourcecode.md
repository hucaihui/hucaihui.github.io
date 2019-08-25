---
layout: post
title:  PHP in_array 源码学习， 以及in_array和isset效率比较
tags: php in_array isset
---


### 背景知识

工作中通过xhprof分析接口性能，在xhprof产生的结果中发现如下一条

Function Name |  Calls |  Calls% | Incl. Wall Time(microsec) | IWall% | Excl. Wall Time(microsec)
in_array  |  6,115  | 36.9%  | 1,857,818  | 43.6%  | 1,857,818 |


调用了6K次的in_array耗时接近2秒， 数组里面大概有1W个元素， 这个耗时明显是不能接受的。就想办法改成了通过isset来实现in_array的功能。

通过简单的脚本测试，发现isset确实比in_array快， 这也很好理解， isset是O(1)的时间复杂度， in_array则是O(n)。



### in_array 源码梳理

为了弄清楚in_array的实现，梳理了下in_array的源码。

##### 函数实现入口在`php-src/ext/standard/array.c`如下：

```c
/* proto bool in_array(mixed needle, array haystack [, bool strict])
   Checks if the given value exists in the array */
PHP_FUNCTION(in_array)
{
    php_search_array(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0);
}


```
##### 主要实现逻辑都在php_search_array中， 代码如下：

```c
/* void php_search_array(INTERNAL_FUNCTION_PARAMETERS, int behavior)
 * 0 = return boolean  in_array时 behavior为0
 * 1 = return key array_search 时behavior为1
 */
static inline void php_search_array(INTERNAL_FUNCTION_PARAMETERS, int behavior)
{
    zval *value,                /* value to check for */
         *array,                /* array to check in */
         *entry;                /* pointer to array entry */
    zend_ulong num_idx;
    zend_string *str_idx;
    zend_bool strict = 0;       /* strict comparison or not */


    /*
     * php7 使用了fast parameter parsing Api 来解析参数
     * ZEND_PARSE_PARAMETERS_START() 的两个参数分别为最少参数数和最多参数数。
     * Z_PARAM_ZVAL() 则将参数视为zval，Z_PARAM_ARRAY() 将参数视为数组。
     * Z_PARAM_OPTIONAL 则表示后面的参数为可选参数
     * Z_PARAM_BOOL 表示参数是布尔型
     * add by huyongde 参考：http://www.php-internals.com/book/?p=chapt11/11-02-01-zend-parse-parameters
     */

    ZEND_PARSE_PARAMETERS_START(2, 3) /*  */
        Z_PARAM_ZVAL(value)
        Z_PARAM_ARRAY(array)
        Z_PARAM_OPTIONAL
        Z_PARAM_BOOL(strict)
    ZEND_PARSE_PARAMETERS_END();

    if (strict) {
        ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(array), num_idx, str_idx, entry) {  // 对数组进行遍历
            ZVAL_DEREF(entry);
            if (fast_is_identical_function(value, entry)) {
                if (behavior == 0) {
                    RETURN_TRUE;
                } else {
                    if (str_idx) {
                        RETVAL_STR_COPY(str_idx);
                    } else {
                        RETVAL_LONG(num_idx);
                    }
                    return;
                }
            }
        } ZEND_HASH_FOREACH_END(); // 数组遍历结束
    } else {
        if (Z_TYPE_P(value) == IS_LONG) {
            ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(array), num_idx, str_idx, entry) {
                if (fast_equal_check_long(value, entry)) {
                    if (behavior == 0) {
                        RETURN_TRUE;
                    } else {
                        if (str_idx) {
                            RETVAL_STR_COPY(str_idx);
                        } else {
                            RETVAL_LONG(num_idx);
                        }
                        return;
                    }
                }
            } ZEND_HASH_FOREACH_END();
        } else if (Z_TYPE_P(value) == IS_STRING) { 
            ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(array), num_idx, str_idx, entry) {
                if (fast_equal_check_string(value, entry)) {
                    if (behavior == 0) {
                        RETURN_TRUE;
                    } else {
                        if (str_idx) {
                            RETVAL_STR_COPY(str_idx);
                        } else {
                            RETVAL_LONG(num_idx);
                        }
                        return;
                    }
                }
            } ZEND_HASH_FOREACH_END();
        } else {
            ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(array), num_idx, str_idx, entry) {
                if (fast_equal_check_function(value, entry)) {
                    if (behavior == 0) {
                        RETURN_TRUE;
                    } else {
                        if (str_idx) {
                            RETVAL_STR_COPY(str_idx);
                        } else {
                            RETVAL_LONG(num_idx);
                        }
                        return;
                    }
                }
            } ZEND_HASH_FOREACH_END();
        }
    }

    RETURN_FALSE;
}

```

##### php_search_array 中一些主要的宏或者函数介绍如下
* ZEND_HASH_FOREACH_KEY_VAL 和 ZEND_HASH_FOREACH_END 两个宏 定义在`php-src/Zend/zend_hash.h` 中， 用来实现遍历数组中的元素
* fast_is_identical_function 定义在`php-src/Zend/zend_operators.h` 中， 用来弱类型比较两个对象是否相等
* fast_equal_check_[string|long|function] 三个函数也定义在`php-src/Zend/zend_operators.h` 中用来比较字符串是否相等， 整型是否相等，函数是否相等


从源码可以看到in_array时间复杂度确实是O(n)。

#### isset 和 in_array性能比较

简单的测试代码如下： 

```php
function testInArray($arr) {
    for($i=0; $i<10000; $i++) {
        $rand = rand(0, 10000);
        in_array($rand, $arr);

    }

}
function testIsset($arr) {
    for($i=0; $i<10000; $i++) {
        $rand = rand(0, 10000);
        isset($arr[$rand]);

    }

}
$arr = array();
for($i=0; $i<10000; $i++) {
    array_push($arr, $i);
}
$arr2 = array();
for($i=0; $i<10000; $i++) {
    $arr2[$i] = 1;
}

$start = microtime(true);
testInArray($arr);
$start2 = microtime(true);
testIsset($arr2);
$end = microtime(true);
echo "in_array time: " . ($start2 - $start) * 1000 . "\n";
echo "isset time: " . ($end - $start2) * 1000 . "\n";

```

测试结果输出结果如下： 

```
in_array time: 717.60702133179
isset time: 44.092893600464
```


时间单位毫秒， 差别还是挺明显的。