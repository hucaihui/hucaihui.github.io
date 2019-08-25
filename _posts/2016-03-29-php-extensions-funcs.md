---
layout: post
title: php扩展操作相关的函数
tags: php extension
---

### 简介

> 介绍PHP中操作扩展的 相关的函数如dl(), get_loaded_extensions(), get_extension_funcs()等

### 函数学习

#### 1. dl() 

* 说明 bool dl(string $library) 动态载入指定参数$library相关的扩展
* 参数  扩展的名称
* 返回值 成功返回true, 失败返回false;
* 例子


``` php
if (!extension_loaded('sqlite')) {
    if (strtoupper(substr(PHP_OS, 0, 3)) === 'WIN') {
        dl('php_sqlite.dll');
    } else {
        dl('sqlite.so');
    }
}

```

#### 2.extension_loaded() 

* 说明 bool extension_loaded(string $name)  检查一个扩展是否已经加载
* 参数  扩展的名称，可以通过php -m来得到所有的扩展的名称
* 返回值 扩展已经加载返回true,  否则返回false
* 例子 见 dl() 的例子


#### 3. get_loaded_extensions()

* 说明 array get_loaded_extensions([ bool $zend_extension]) 返回当前所有编译并加载的php扩展模块
* 参数 $zend_extension 为true只返回zend的扩展，默认是false, 返回所有扩展 
* 返回值  返回所有扩展名组成的索引数组
* 例子  `print_r(get_loaded_extensions());`

#### 4. get_extension_funcs()

* 说明 array get_extension_funcs(string $module_name) 根据module_name返回扩展中所有定义的函数
* 参数 扩展模块的名字
* 返回值 模块内所有函数名组成的索引数组
* 例子 `php -r "print_r(get_extension_funcs('yaml'));"`


> get_extension_funcs() 可以用来初步的学习下一个扩展，获得这个扩展都实现了那些函数。



### 参考

* [php 选项信息函数](http://php.net/manual/zh/ref.info.php)


