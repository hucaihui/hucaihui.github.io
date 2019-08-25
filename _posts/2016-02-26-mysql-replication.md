---
layout: post
title: mysql 主从复制
tags: mysql replication
---
###简介

* MySQL的Replication是一个异步复制的过程,现在新的版本支持异步和半同步的过程，
它是从一个Mysql master 实例 复制到Mysql slave instance的过程。
在master与slave之间实现整个复制过程主要由三个线程来完成，
slave端包括SQL线程和IO线程，master端包括一个IO线程。

* 要实现MySQL的Replication，第一必须打开master端的binlog。 因为mysql的整个主从复制过程实际上就是：
slave端从master端获取binlog日志，然后再在自己身上完全顺序的执行该日志中所记录的各种SQL操作。

###mysql 主从复制的具体过程

1. slave端的IO线程连接上master端，并请求从指定binlog日志文件的指定pos节点位置(或者从最开始的日志)开始复制之后的日志内容。

2. master端在接收到来自slave端的IO线程请求后，通知master端负责复制binlog的IO线程，根据slave端IO线程的请求信息，读取指定binlog日志指定pos节点位置之后的日志信息，然后返回给slave端的IO线程。该返回信息中除了binlog日志所包含的信息之外，还包括本次返回的信息在master端的binlog文件名以及在该binlog日志中的pos节点位置。

3. slave端的IO线程在接收到master端IO返回的信息后，将接收到的binlog日志内容依次写入到slave端的relaylog文件(mysql-relay-bin.xxxxxx)的最末端，并将读取到的master端的binlog文件名和pos节点位置记录到master-info（该文件存在slave端）文件中，以便在下一次读取的时候能够清楚的告诉master“我需要从哪个binlog文件的哪个pos节点位置开始，请把此节点以后的日志内容发给我”。

4. slave端的SQL线程在检测到relaylog文件中新增内容后，会马上解析该log文件中的内容。然后还原成在master端真实执行的那些SQL语句，并在自身按顺丰依次执行这些SQL语句。这样，实际上就是在master端和slave端执行了同样的SQL语句，所以master端和slave端的数据是完全一样的。

#####复制过程简化描述如下：

1. master在执行sql之后，记录二进制log文件（bin-log）。

2. slave连接master，并从master获取binlog，存于本地relay-log中，然后从上次记住的位置起执行SQL语句，一旦遇到错误则停止同步。

