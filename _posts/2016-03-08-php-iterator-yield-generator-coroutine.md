---
layout: post
title: php 迭代器、yield、生成器以及协程
tags: iterator yeild generator coroutine
---


####参考
* [php生成器和协程实现](http://www.cnblogs.com/whoamme/p/5039533.html)
* [在PHP中使用协程实现多任务调度(鸟哥)](http://www.laruence.com/2015/05/28/3038.html)
* [php生成器和协程的实现](https://phphub.org/topics/1430)

###学习总结
0. 迭代器的优点是在处理大量数据的时候不需要一次性全部加载到内存中.
1. 协程是基于iterator, yield, generator 实现的.
2. 有yield的函数就变成了一个generator.
3. yield返回的是一个iterator.
4. yield既可以返回也可以接收数据.
