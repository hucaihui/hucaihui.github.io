---
layout: post
title: php 扩展开发--- config.m4解读
tags: php extension
---
### 1. ext_skel 扩展骨架生成的 config.m4解读

#### config.m4 实例
```
dnl $Id$
dnl config.m4 for extension example
PHP_ARG_WITH(example, for example support,
[  --with-example[=FILE]       Include example support. File is the optional path to example-config])
PHP_ARG_ENABLE(example-debug, whether to enable debugging support in example,
[  --enable-example-debug        example: Enable debugging support in example], no, no)
PHP_ARG_WITH(example-extra, for extra libraries for example,
[  --with-example-extra=DIR      example: Location of extra libraries for example], no, no)

dnl 检测扩展是否已启用
if test "$PHP_EXAMPLE" != "no"; then
  
  dnl 检测 example-config。首先尝试所给出的路径，然后在 $PATH 中寻找
  AC_MSG_CHECKING([for example-config])
  EXAMPLE_CONFIG="example-config"
  if test "$PHP_EXAMPLE" != "yes"; then
    EXAMPLE_PATH=$PHP_EXAMPLE
  else
    EXAMPLE_PATH=`$php_shtool path $EXAMPLE_CONFIG`
  fi
  
  dnl 如果找到可用的 example-config，就使用它
  if test -f "$EXAMPLE_PATH" && test -x "$EXAMPLE_PATH" && $EXAMPLE_PATH --version > /dev/null 2>&1; then
    AC_MSG_RESULT([$EXAMPLE_PATH])
    EXAMPLE_LIB_NAME=`$EXAMPLE_PATH --libname`
    EXAMPLE_INCDIRS=`$EXAMPLE_PATH --incdirs`
    EXAMPLE_LIBS=`$EXAMPLE_PATH --libs`
    
    dnl 检测扩展库是否工作正常
    PHP_CHECK_LIBRARY($EXAMPLE_LIB_NAME, example_critical_function,
    [
      dnl 添加所需的 include 目录
      PHP_EVAL_INCLINE($EXAMPLE_INCDIRS)
      dnl 添加所需的扩展库及扩展库所在目录
      PHP_EVAL_LIBLINE($EXAMPLE_LIBS, EXAMPLE_SHARED_LIBADD)
    ],[
      dnl 打印错误信息，并推出./configure
      AC_MSG_ERROR([example library not found. Check config.log for more information.])
    ],[$EXAMPLE_LIBS]
    )
  else
    dnl 没有可用的 example-config，跳出
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please check your example installation.])
  fi
  
  dnl 检测是否启用调试
  if test "$PHP_EXAMPLE_DEBUG" != "no"; then
    dnl 是，则设置 C 语言宏指令
    AC_DEFINE(USE_EXAMPLE_DEBUG,1,[Include debugging support in example])
  fi
  
  dnl 检测额外的支持
  if test "$PHP_EXAMPLE_EXTRA" != "no"; then
    if test "$PHP_EXAMPLE_EXTRA" == "yes"; then
      AC_MSG_ERROR([You must specify a path when using --with-example-extra])
    fi
    
    PHP_CHECK_LIBRARY(example-extra, example_critical_extra_function,
    [
      dnl 添加所需路径
      PHP_ADD_INCLUDE($PHP_EXAMPLE_EXTRA/include)
      PHP_ADD_LIBRARY_WITH_PATH(example-extra, $PHP_EXAMPLE_EXTRA/lib, EXAMPLE_SHARED_LIBADD)
      AC_DEFINE(HAVE_EXAMPLEEXTRALIB,1,[Whether example-extra support is present and requested])
      EXAMPLE_SOURCES="$EXAMPLE_SOURCES example_extra.c"
    ],[
      AC_MSG_ERROR([example-extra lib not found. See config.log for more information.])
    ],[-L$PHP_EXAMPLE_EXTRA/lib]
    )
  fi
  
  dnl 最后，将扩展及其所需文件等信息传给构建系统
  PHP_NEW_EXTENSION(example, example.c $EXAMPLE_SOURCES, $ext_shared)
  PHP_SUBST(EXAMPLE_SHARED_LIBADD)
fi
```

#### 简单解读

* dnl 表示注释
* PHP_ARG_WITH | PHP_ARG_ENABLE： 有三个参数，第一个参数是我们的扩展名(注意不用加引号)，第二个参数是当我们运行./configure脚本时显示的内容，最后一个参数则是我们在调用./configure --help时显示的帮助信息
* AC_MSG_\*: AC 是autoconf的缩写，\* 可以为：checking, result, notice, error, failure, warn。AC_MSG_* 均为autoconf宏。
    *  AC_MSG_CHECKING()，一个 autoconf 宏，输出一行标准的如 "checking for ..." 的信息
    * AC_MSG_\* 每个宏的具体用处可以参考[autoconf printing messages](https://www.gnu.org/software/autoconf/manual/autoconf-2.60/autoconf.html)

* PHP_ADD_INCLUDE: PHP_ADD_INCLUDE() 和 PHP_ADD_LIBRARY_WITH_PATH() 用于构建额外功能所需的头文件路径、库文件路径和库标志
* PHP_CHECK_LIBRARY，这是 PHP 构建系统提供的一个宏，包装了 autoconf 的 AC_CHECK_LIB() 函数， 用来检查扩展库是否正常工作。PHP_CHECK_LIBRARY()尝试编译、链接和执行程序，在第一个参数指定的库中调用由第二个参数指定的符号，使用第五个参数给出的字符串作为额外的链接选项。如果尝试成功了，则运行第三个参数所给出的脚本。此脚本从 example-config 所提供的原始的选项字符串中取出头文件路径、库文件路径和库名称，告诉 PHP 构建系统。如果尝试失败，脚本则运行第四个参数中的脚本。此时调用 AC_MSG_ERROR() 来中断程序执行
* AC_DEFINE: 设置C语言宏指令
* PHP_SUBST() 来启用扩展的共享构建
* PHP_NEW_EXTENSION: 告诉构建系统去构建扩展本身和被其用到的文件, 第一个参数是扩展的名称，也就是config.m4所在的目录名称, 第二个参数是做为扩展的一部分的所有源文件的列表。参见 PHP_ADD_BUILD_DIR() 以获取将在子目录中源文件添加到构建过程的相关信息。第三个参数总是 $ext_shared， 当为了 --with-example[=FILE] 而调用 PHP_ARG_WITH()时，由 configure 决定参数的值。第四个参数指定一个“SAPI 类”，仅用于专门需要 CGI 或 CLI SAPI 的扩展。其他情况下应留空。第五个参数指定了构建时要加入 CFLAGS 的标志列表。第六个参数是一个布尔值，为 "yes" 时会强迫整个扩展使用 $CXX 代替 $CC 来构建。第三个以后的所有参数都是可选的

### 参考
* [PHP骇客 之 与UNIX构建系统交互: config.m4](http://php.net/manual/zh/internals2.buildsys.configunix.php)
* [autoconf manual](https://www.gnu.org/software/autoconf/manual/autoconf-2.60/autoconf.html)
