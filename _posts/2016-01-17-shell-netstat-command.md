---
layout: post
title: netstat 实际使用例子
tags: netstat command
---

**本文参考:** [**netstat command examples**](http://www.binarytides.com/linux-netstat-command-examples/)


###netstat 简介
 
```
netstat - Print network connections, routing tables, interface statistics, 
masquerade connections, and multicast memberships
```
###netstat 使用例子

* netstat -a  显示所有的网络连接
* netstat -at; netstat -au  显示特定协议的连接， t 选项显示tcp协议， u 选项显示udp协议
* netstat -atn  选项n显示ip,可以更快速的显示网络连接，不需要去把ip解析成域名
* netstat -tln 选项l表示只显示监听状态的连接
* netstat -nltp 选项p 显示连接对应的进程名字
* netstat -nlte 选项e 显示连接的所有者
* netstat -s 显示相关统计信息
* netstat -r 显示内核路由信息
* netstat -re 选项e 更友好的方式显示内核路由信息
* netstat -tc 选项c 可以持续显示连接信息
* netstat -g 显示多播相关信息

###netstat返回结果解释

` Proto Recv-Q Send-Q  Local Address          Foreign Address        (state)`

一般的返回结果都有如上几列

* Ptoto 表示socket使用的协议
* Recv-Q 数据已经在本地接收缓冲,但是还没有recv().
* Send-Q 对方没有收到的数据或者说没有Ack的,还是本地缓冲区.
* Local Address 本地地址
* Foreign Address 远端地址
* state socket链接的当前状态
