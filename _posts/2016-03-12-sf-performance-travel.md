---
layout: post 
title: PHP性能之路
tags: php
---

###PHP 性能之路
> 纵观语言发展历史，从0和1的机器码开始，到汇编语言，然后到C语言，再到动态脚本语言PHP。执行效率呈指数下降，但是，学习门槛也呈指数降低。PHP语言不仅屏蔽了C的内存> 管理和指针的复杂性，而且更进一步屏蔽了变量类型的复杂性。提升了项目开发的效率，降低了学习的门槛，但同时牺牲了一定的执行性能。然后，HHVM的Hack给我们一种“回归> 原始”的感觉，重新引入了变量的复杂性。当然，不同的语言解决不同场景下的问题，并不能够一概而论

![二进制机器码到PHP](/image/php.jpg)
 

####前戏

* 95年php诞生，
* php (personal home page)
* 81.9%的网站是PHP开发
* php中1+"aaa" 结果是？

####正文

性能所在点：

* IO
* memory
* cpu
* network

PHP7 
> php7 又称 php next generation

* [phpng](https://wiki.php.net/phpng)
* HHVM(hiphop virtual machine), HHVM提升PHP性能的途径，采用的方式就是替代Zend引擎来生成和执行PHP的中间**字节码**（HHVM生成自己格式的中间字节码），执行时通过JIT（Just In Time，即时编译是种软件优化技术，指在运行时才会去编译字节码为机器码）转为**机器码**执行。Zend引擎默认做法，是先编译为opcode，然后再逐条执行，通常每条指令对应的是C语言级别的函数。如果我们产生大量重复的opcode（纯PHP写的代码和函数），对应的则是Zend多次逐条执行这些C代码。而JIT所做的则是更进一步，将大量重复执行的字节码在运行的时候编译为机器码，达到提高执行效率的目的。通常，触发JIT的条件是代码或者函数被多次重复调用。
*  [HHVM VS PHP7,优化PHP性能](http://www.csdn.net/article/2014-12-25/2823234)
* [HHVM官网](http://hhvm.com/)

* fastercgi
* php7 array 底层结构升级
* JIT (just in time) : JIT（即时）编译器：即时编译是种软件优化技术，指在运行时才会去编译字节码。字节码会存放在内存中，然后JIT编译器会根据需要加载并编译所涉的字节码。
