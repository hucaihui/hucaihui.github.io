---
layout: post
title:  静态变量(static) 和 全局变量(global)
tags: php  static  global 
---


#### 参考

* [php变量范围](http://php.net/manual/zh/language.variables.scope.php)


#### 静态变量

> 静态变量仅在**局部函数域**中存在，但当程序执行离开此作用域时，其值并不丢失。

```
$a = 10;

function test ($a) {
   static $a = 1;
   echo $a . "\n";
   $a ++ ;
}
test($a);
test($a);
test($a);
echo $a . "\n" ;

```
如上PHP脚本的输出应该为
```
1
2
3
10
```

> 函数内的静态变量不是存储在函数的栈空间中， 而是存储在了堆空间中，无论函数调用多少次，静态变量仅初始化一次， 并且每次对静态变量的操作的都会累积。



静态变量也提供了一种处理递归函数的方法。递归函数是一种调用自己的函数。写递归函数时要小心，因为可能会无穷递归下去。必须确保有充分的方法来中止递归。

以下这个简单的函数递归计数到 10，使用静态变量 $count 来判断何时停止

```

function test2() {
    static $a = 0;
    $a++;
    echo $a;
    if ($a >10) {
        echo $a . "end \n";
        return;
    }
    test2();
}
test2();

```

递归了10次， 一共调用test2函数11次。


#### 全局变量

函数中使用全局变量时，需要用global关键字对全局变量进行声明，声明之后就可以在函数内使用全局变量了。如下：



```
$a = 1;
$b = 2;

function Sum()
{
    global $a, $b;

    $b = $a + $b;
}

Sum();
echo $b;
```


还可以使用$GLOBALS超全局变量来访问全局变量。
如下：

```
$a = 1;
$b = 2;

function Sum()
{
    $GLOBALS['b'] = $GLOBALS['a'] + $GLOBALS['b'];
}

Sum();
echo $b;
```

超全局变量 $GLOBALS 是一个关联数组，每一个变量为一个元素，键名对应变量名，值对应变量的内容。