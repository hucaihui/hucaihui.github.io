---
layout: post
title: redis主从复制介绍
tags: redis replication
---

### 简介
Redis的replication机制允许slave从master那里通过网络传输拷贝到完整的数据备份。具有以下特点：

1. 异步复制。从2.8版本开始，slave能不时地从master那里获取到数据。
2. 允许单个master配置多个slave
3. slave允许其它slave连接到自己。一个slave除了可以连接master外，它还可以连接其它的slave。形成一个图状的架构。
4. master在进行replication时是非阻塞的，这意味着在replication期间，master依然能够处理客户端的请求。
5. slave在replication期间也是非阻塞的，也可以接受来自客户端的请求，但是它用的是之前的旧数据。
可以通过配置来决定slave是否在进行replication时用旧数据响应客户端的请求，如果配置为否，那么slave将会返回一个错误消息给客户端。不过当新的数据接收完全后，必须将新数据与旧数据替换，即删除旧数据，在替换数据的这个时间窗口内，slave将会拒绝客户端的请求和连接。
6. 一般使用replication来可以实现扩展性，例如说，可以将多个slave配置为“只读”，或者是纯粹的数据冗余备份。
7. 能够通过replication来避免master每次持久化时都将整个数据集持久化到硬盘中。只需把master配置为不进行持久化操作(把配置文件中save相关的配置项注释掉即可)，然后连接上一个slave，这个slave则被配置为不时地进行持久化操作的。
不过需要注意的是，在这个用例中，必须确保master不会自动启动,具体原因请继续看下面的内容。


### redis master关闭持久化可能存在的问题

> 当有需要使用到replication机制时，一般都会强烈建议把master的持久化开关打开。即使为了避免持久化带来的延迟影响，不把持久化开关打开，那么也应该把master配置为不会自动启动的。

为了更好的解释不进行持久化的master为什么要关闭自动启动，请看下面的例子：
> 假设我们有一个redis节点A，设置为master，并且关闭持久化功能，另外两个节点B和C是它的slave，并从A复制数据。

```
如果A节点崩溃了导致所有的数据都丢失了，它会有重启系统来重启进程。
但是由于持久化功能被关闭了，所以即使它重启了，它的数据集是空的。
而B和C依然会通过replication机制从A复制数据，所以B和C会从A那里复制到一份空的数据集，
并用这份空的数据集将自己本身的非空的数据集替换掉。于是就相当于丢失了所有的数据。

即使使用一些HA工具，比如说sentinel来监控master-slaves集群，
也会发生上述的情形，因为master可能崩溃后迅速恢复。
速度太快而导致sentinel无法察觉到一个failure的发生。
```
**当数据的安全很重要、持久化开关被关闭并且有replication发生的时候，那么应该禁止实例的自启动。**

### redis主从复制(replication)的原理

1. 如果你为master配置了一个slave，不管这个slave是否是第一次连接上Master，它都会发送一个SYNC命令给master请求复制数据。

2. master收到SYNC命令后，会在后台进行数据持久化，持久化期间，master会继续接收客户端的请求，它会把这些可能修改数据集的请求缓存在内存中。
3. 当持久化进行完毕以后，master会把这份数据集发送给slave，slave会把接收到的数据进行持久化，然后再加载到内存中。
然后，master再将之前缓存在内存中的命令发送给slave。

3. 当master与slave之间的连接由于某些原因而断开时，slave能够自动重连Master，
如果master收到了多个slave并发连接请求，**它只会进行一次持久化，而不是一个连接一次，然后再把这一份持久化的数据发送给多个并发连接的slave。**

4. 当master和slave断开重连后，一般都会对整份数据进行复制。但从redis2.8版本开始，支持部分复制。

### master slave的部分复制

```
从2.8版本开始，slave与master能够在网络连接断开重连后只进行部分数据复制。
master会在其内存中创建一个复制流的等待队列，
master和它所有的slave都维护了复制的数据下标和master的进程id，
因此，当网络连接断开后，slave会请求master继续进行未完成的复制，
从所记录的数据下标开始。如果进程id变化了，或者数据下标不可用，那么将会进行一次全部数据的复制。

支持部分数据复制的命令是*PSYNC*

```

### 不需要持久化的replication

```
一般情况下，一次复制需要将内存的数据写到硬盘中，再将数据从硬盘读进内存，再发送给slave。

对于速度比较慢的硬盘，这个操作会给master带来性能上的损失。
Redis2.8版本开始，实验性地加上了无硬盘复制的功能。
这个功能能将数据从内存中直接发送到slave，而不用经过硬盘的存储。
不过这个功能目前处于实验阶段，还未正式发布。
```
### 其他

1. slaveof master_ip master_Port 来配置slave的master
2. repl-diskless-sync 来配置不需要持久化的replication
3. slave-read-only 来配置slave只读


### 参考
[深入剖析Redis主从复制](http://daoluan.net/blog/2014/04/22/decode-redis-replication/)

