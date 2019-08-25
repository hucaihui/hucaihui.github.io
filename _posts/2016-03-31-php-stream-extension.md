---
layout: post
title: "php stream扩展学习"
tags: stream php extension
---


### 参考
* [php stream extension manual ](http://php.net/manual/zh/intro.stream.php)
* [php支持的协议和封装协议](http://php.net/manual/zh/wrappers.php) 
* [上下文选项和参数](http://php.net/manual/zh/context.php)

### 0. 简介

1. stream 扩展是PHP4.3.0版本发布出来的，用来泛华文件，网络等的操作。
stream可以简单的定义为一个资源对象,可以 提供一些流操作。
这个流可以读写，并且可以定位到流的任意位置(arbitrary location)

2. 既然是泛华了很多资源的操作，就需要有个封装来进行特定协议的解析和加密解密。

比如HTTP相关的封装会实现从一个url转换成一个标准的http请求，发送到server端。
3. php支持对多种协议的封装，详情见[php支持的协议和封装协议](http://php.net/manual/zh/wrappers.php) 

4. 可以通过函数stream_get_wrappers()来获得PHP已经注册的相关协议的封装

5. 可以通过函数stream_register_wrapper() 来注册一个协议的封装



我的机器`stream_get_wrappers()`的返回结果如下: 

```
 $ php -r "print_r(stream_get_wrappers());"
Array
(
    [0] => https
    [1] => ftps
    [2] => compress.zlib
    [3] => compress.bzip2
    [4] => php
    [5] => file
    [6] => glob
    [7] => data
    [8] => http
    [9] => ftp
    [10] => phar
    [11] => zip
)
```

### 1. 流过滤器(stream filters)

对stream流上读或者写的数据做过滤,php所有支持的过滤器可以通过`stream_get_filters()`来获得，如下：

```
$ php -r "print_r(stream_get_filters());"
Array
(
    [0] => zlib.*
    [1] => bzip2.*
    [2] => convert.iconv.*
    [3] => string.rot13
    [4] => string.toupper
    [5] => string.tolower
    [6] => string.strip_tags
    [7] => convert.*
    [8] => consumed
    [9] => dechunk
    [10] => mcrypt.*
    [11] => mdecrypt.*
    [12] => http.*
)
```

> 每个过滤器实现不同的过滤功能

### 2. 流的上下文( stream contexts)

可以通过`stream_context_create()` 来创建流的上下文， 比如为fopen, file, file_get_contents等。
上下文包括http请求的header等. 各个协议都包含自己的上下文，详情参考[上下文选项和参数](http://php.net/manual/zh/context.php)


### 3. stream类函数

详情参照[PHP stream 函数](http://php.net/manual/zh/ref.stream.php)

每个函数后续继续学习


未完待续




