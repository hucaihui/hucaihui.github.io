---
layout: post
title: 为浏览器添加vim的快捷键--for vimmer
tags: shell
---

###目录
* [简介](#简介)
* [chrome浏览器](#chrome)
* [firefox浏览器](#firefox)

<a id="简介"></a>
##简介

好长一段时间都在用firefox(因为没有个靠谱的vpn,没法用chrome相关功能，包括扩展更新),

最近折腾好了vpn，可以用起来google的相关功能了。 

想知道怎么折腾vpn的移步[翻墙看世界](http://huyongde.github.io/2015/11/24/goout-see-world.html)

对于vimmer来说，vim的各种快捷键想移植到各个用到的东西上，比如chrome浏览器，visual studio， 有道云笔记(这个暂时还没有插件)等。

下面介绍下如何在chrome和firefox中使用vim的快捷键

<a id="chrome"></a>
##chrome浏览器

需要安装chrome的插件(需要翻墙奥)vrome，相关资料如下:

[vrome主页](chrome-extension://godjoomfiimiddapohpmfklhgmbfffjj/background/html/options.html#dashboard)

[vrome github](https://github.com/jinzhu/vrome)

[vrome chrome插件安装](https://chrome.google.com/webstore/detail/vrome/godjoomfiimiddapohpmfklhgmbfffjj)

[vrome rc配置](chrome-extension://godjoomfiimiddapohpmfklhgmbfffjj/background/html/options.html#setting) 和vimrc类似可以配置自己的快捷键

[vromerc 示例](https://github.com/jinzhu/vrome/wiki/vromerc-example-file)

[vrome wiki](https://github.com/jinzhu/vrome/wiki)

###简单的快捷键 
* gg: 到页面首部
* G: 到也面尾部
* /: 当前页面进行搜索
* n: 搜索到的下一个位置
* N: 搜索到的上一个位置
* C+y: 复制当前页面的URL
* j k hl ：下 上 左 右移动
* H L
    * H 后退一个页面
    * 2 H 后退两个页面
    * L 前进一个页面
    * 2 L 前进两个页面

###[**vrome所有快捷键**](https://github.com/jinzhu/vrome/blob/master/Features.mkd)
 

<a id="firefox"></a>
##firefox浏览器

*待续*

