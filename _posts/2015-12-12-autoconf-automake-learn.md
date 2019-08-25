---
layout: post
title: autoconf  automake 学习
tags: c++
---


## 简介

介绍如何使用`autoconf` `automake` 来为自己开发的c/c++程序生成符合自由软件惯例的Makefile,

这样的话，就可以和其他的GNU程序一样，通过`./configure; make; make install` 把自己的程序安装到linux系统中。


## helloworld 示例

简单的helloworld  c程序，通过`autoconf` 以及 `automake`来生成Makefile文件，从而实现通过`./configure; make; make install`

来实现生成可执行的二进制文件helloworld


### 需要准备的文件

#### helloworld.c
内容如下：

```
#include<stdio.h>
int main(){
    printf("hello world!\n");
    return 0;
}
```

#### Makefile.am
内容如下:

```
bin_PROGRAMS=helloworld
hello_SOURCES=helloworld.c
```

#### configure.ac
内容如下:

```
AC_INIT([Helloworld Program], [1.0],
        [huyongde <huyongde@google.com>],
        [helloworld])
AM_INIT_AUTOMAKE
AC_PROG_CC
AC_PROG_INSTALL
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
```
#### 文件内容简单介绍

* Makefile.am是用逻辑语言写的,没有比较明显的执行过程,只是给出了可执行文件和源文件的关系。

* configure.ac 是程序语言，文中每一行都是一个需要执行的命令。

    * AC_INIT 用来初始化configure 脚本。第一个参数是程序的名字，第二个参数是作者以及作者的邮箱，第三个参数是打包的文件的名字。
    * AC_INIT_AUTOMAKE 做了一下我们调用automake需要的相关的初始化。要是自己手动写Makefile.in的话就不需要执行AC_INIT_AUTOMAKE。
    * AC_PROG_CC 检查gcc的版本。
    * AC_PROG_INSTALL 
    * AC_CONFIG_FILES 设置脚本configure生成的makefile的文件名。
    * AC_OUTPUT 告诉configure 脚本生成AC_CONFIG_FILES指定的文件。
## 生成configure

按顺序执行如下命令:

1. aclocal
2. autoconf
3. touch README AUTHORS NEWS ChangeLog
4. automake -a

## 生成二进制文件

按顺序执行如下命令

1. `./configure` 生成Makefile文件
2. `make;make install` 生成可执行文件helloworld

运行`./helloworld`输出程序的执行结果。

## 参考

[**Learning the GNU development tools**](http://autotoolset.sourceforge.net/tutorial.html#Hello-World-revisited)

[**鸟哥的autoconf、automake使用详解**](http://www.laruence.com/2009/11/18/1154.html)

