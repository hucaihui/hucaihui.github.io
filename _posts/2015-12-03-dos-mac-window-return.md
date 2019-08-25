---
layout: post
title: unix 查看window开发的代码，如何处理^M特殊字符
tags: shell
---

**去除代码中的`^M`**

*由于mac, linux, windows对行末尾的回车符的处理不一致，会导致在mac或者linux下查看window开发的代码的时候，行末尾存在特殊字符`^M`*

可以通过`dos2unix`来去掉文件的^M


mac需要安装`dos2unix` 

`brew install dos2unix`, [brew](http://brew.sh/index_zh-cn.html) 是OS X 不可或缺的套件管理工,brew的安装和使用详见[**官网**](http://brew.sh/index_zh-cn.html)。

安装完`dos2unix`之后，直接`dos2unix filename`就可以把`filename`文件中的`^M`去掉


