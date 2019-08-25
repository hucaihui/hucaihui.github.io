---
layout: post
title: linux 命令学习汇总
tags: shell
---

##目录
* [killall](#killall) 
* [lsof](#lsof) 
* [netstat](#netstat)  
* [学习计划](#plan) 

[**linux man**](http://linux.die.net/)

<a id="killall"></a>
## killall

`killall(kill processes by nane)` 表示通过进程名字`kill`进程，可以一次`kill`多个进程


`kill -9 pid` 基本可以`kill`掉所有的进程，除了`init`进程。

`killall -9 nginx` 可以杀掉所有通过`nginx`命令启动的进程

<a id="lsof"></a>
##lsof

###lsof简介
`lsof` 是 `list open files`的缩写，可以列出当前系统所有打开的文件。Linux环境下所有的事物都是以文件形式存在的。

`lsof` 通常在`/usr/sbin/`目录下，所以执行时，需要有相应的权限 `/usr/sbin/lsof`

##lsof输出结果介绍

lsof输出各列信息的意义如下：

```
COMMAND：进程的名称
PID：进程标识符
USER：进程所有者
FD：文件描述符，应用程序通过文件描述符识别该文件。如cwd、txt等 TYPE：文件类型，如DIR、REG等
DEVICE：指定磁盘的名称
SIZE：文件的大小
NODE：索引节点（文件在磁盘上的标识）
NAME：打开文件的确切名称
```
###lsof常用参数

常用参数和例子

```
lsof abc.txt 显示开启文件abc.txt的进程
lsof -c abc 显示abc进程现在打开的文件
lsof -c -p 1234 列出进程号为1234的进程所打开的文件
lsof -g gid 显示归属gid的进程情况
lsof +d /usr/local/ 显示目录下被进程开启的文件
lsof +D /usr/local/ 同上，但是会搜索目录下的目录，时间较长
lsof -d 4 显示使用fd为4的进程
lsof -i 显示所有打开的端口 
lsof -i:6000 显示端口号是6000的进程
```
<a id="netstat"></a>
##netstat

参考[netstat commands samples](http://www.binarytides.com/linux-netstat-command-examples/)

###`netstat -alntp` 其中

a是显示所有的连接， 

l是显示监听的连接, 

n是显示ip，不显示主机名

p是显示连接相关的进程

###`netstat -nr` 

ip形式显示本机的路由表

n是显示ip不显示主机名

r是route路由表

###`netstat -i` 

显示网络接口（network interfaces)

<a id="plan"></a>
##准备学习的命令 ltrace strace


