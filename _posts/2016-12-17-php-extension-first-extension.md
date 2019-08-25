---
layout: post
title: php 扩展开发--- 开发PHP第一个扩展
tags: php extension
---

### 开发PHP第一个扩展
#### 1 使用ext_skel 生成扩展的骨架
下载php源码，源码的ext目录下有个shell脚本`ext_skel`, 此脚本是用来生成PHP扩展框架的， 使用示例：

```
cd ./ext/ ;
./ext_skel --extname=myext // 生成名为myext的扩展
```

生成之后目录结构如下：

```
$ tree .
.
|-- CREDITS
|-- EXPERIMENTAL
|-- config.m4
|-- config.w32
|-- myext.c
|-- myext.php
|-- php_myext.h
`-- tests
    `-- 001.phpt

1 directory, 8 files

```

#### 2 修改配置文件config.m4
需要把配置文件中相关的注释去掉，去掉注释的地方如下:
```
dnl PHP_ARG_WITH(myext, for myext support,
dnl Make sure that the comment is aligned:
dnl [  --with-myext             Include myext support])
```
需要把第一行和第三行的dnl去掉，
config.m4 是unix平台开发扩展的配置文件，config.w32是windows下开发扩展用到的配置文件。

#### 3 动态编译扩展
依次执行如下命令：

* `phpize`
* `./configure --with-php-config=/your_path/php-config`
* `make`
* `make install`

执行完make之后，在当前目录的modules目录下会生成一个myext.so的文件,
`make install` 负责把myext.so复制到php的extension_dir(php.ini中配置的php扩展文件所在目录)目录，

通过`php -i | grep extension` 可以查看相关的配置， 我的开发机运行结果如下:

```
$ php -i | grep extension
extension_dir => /usr/local/php/lib/extensions/ => /usr/local/php/lib/extensions/
```

`make install` 这步可能会遇到没有权限的问题，需要切换到root后再执行，或者直接自己手动copy过去


到此第一个php扩展开发完成，为了验证扩展是否可以正确使用可以进行如下操作
` php -r "var_dump(confirm_myext_compiled('test'));" ` 

正常情况下会返回如下结果:

`string(106) "Congratulations! You have successfully modified ext/myext/config.m4. Module test is now compiled into PHP."`


#### 4 在扩展中编写自己的函数
在myext扩展中增加函数hello_world,需要如下三个操作：

1. php_myext.h 中添加: `PHP_FUNCTION(hello_world);`
2. myext.c 的myext_functions数组中添加` PHP_FE(hello_world, NULL)`
3. myext.c 中进行hello_world函数体的编写,代码如下：

```c
PHP_FUNCTION(hello_world)
{
    char *arg = NULL;
    int arg_len, len;
    char *strg;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
        return;
    }

    len = spprintf(&strg, 0, "hello world %s", arg);
    RETURN_STRINGL(strg, len, 0);
}

```

完成如上三步之后，进行编译三连发： `./configure --with-php-config=/yourpath/php-config; make; make install`

PHP 中验证hello_world函数：

```
$ php -r "var_dump(hello_world('test'));"
string(16) "hello world test"

```

至此基本完成了开发PHP扩展的基本流程， happy coding!

#### 5 遇到的问题

添加hello_world函数时，遇到了 'zif_hello_world' undeclared here (not in a function)
类似的错误，这个错误是因为没有再php_myext.h中添加响应函数声明导致，php_myext.h中添加：`PHP_FUNCTION(hello_world);` 后问题解决



### 参考
* [php扩展编译的两种方式](http://521-wf.com/archives/227.html)