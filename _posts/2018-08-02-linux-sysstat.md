---
layout: post
title: linux sysstat netstat vmstat 介绍
tags: linux performance sysstat
---
### 1. sysstat 简介
sysstat 是linux的一个软件包， 里面包含多个linux 各项性能监控的命令，可以查看监控linux cpu io memory net 等信息

#### 1.1 sysstat 包含的命令列表
* iostat：统计并报告你的设备的CPU状态和I/O状态数据。
* mpstat：监控和显示关于每个逻辑CPU的细节信息。
* pidstat：统计正在运行的进程/任务的CPU、内存等信息, 可以单独查看某个进程的各项信息。
* tapestat 查看连接到系统的U盘等外接设备的信息
* sysstat：解释sysstat的各种作用。

* sar：保存和报告不同资源（CPU、内存、输入输出、网络、内核等）的详细信息。
* sadc：系统活动数据收集器，用于为sar收集后台的数据。
* sa1：读取和存储sadc的数据文件的二进制数据。
* sa2：和sar协作，用于总结每日报告。
* sadf：以不同的格式（CSV或XML）显示sar生成的数据。
* nfsiostat-sysstat:统计NFS协议的网络文件系统的 I/O状态数据。
* cifsiostat：统计CIFS协议的网络文件系统的 I/O状态数据。
#### 1.2 mpstat 使用示例


