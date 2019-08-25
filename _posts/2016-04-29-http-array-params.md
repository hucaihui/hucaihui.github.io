---
title: http 传递数组形式的参数
tags: http 
layout: post
---

###  http两中传参方式
#### 1.普通字符串
    eg:  a=1&b=2

#### 2.数组
    info[name]=huyongde&info[age]=20

后端`$_GET['info']`或者`$_POST['info']` 是一个数组，`array('name'=>'huyongde', 'age'=>20);`

** 注意：无论post还是Get请求都是可以传递数组参数奥。**



