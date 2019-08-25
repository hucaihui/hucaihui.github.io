---
layout: post
title: tcpdump tutorial - sniffing and analysing packets from commandline
tags: network command tcpdump
---

##[tcpdump](http://www.tcpdump.org/) 

###**目录**
* [**参考**](#参考)

####tcpdump -D

D 选项option(开关switch)显示机器所有的网络接口,输出示例如下：

```
$ sudo tcpdump -D
1.en0
2.awdl0
3.bridge0
4.ppp0
5.en1
6.en2
7.p2p0
8.lo0 [Loopback]
```

####tcpdump -n -vv -e -A -i 

n 显示ip地址，而不是显示主机名或域名

-vv 显示详细信息，包括ttl，tcp flags, 数据包长度等信息

-e 显示链路层头信息，包括源物理地址，目的物理地址等

-A 以ascii 码显示包得内容信息

-i 指定-D选项列出来的某个网络接口， -i 1 等价于-i en0

tcpdump -n -vv -e -A -i 的输出如下:

```
i19:54:24.717900 ac:bc:32:83:47:71 > a4:93:4c:76:18:4d, ethertype IPv4 (0x0800), length 46: (tos 0x0, ttl 255, id 18849, offset 0, flags [none], proto GRE (47), length 32)
    172.22.156.47 > 104.238.157.0: GREv1, Flags [key present, ack present], call 6656, ack 7460, no-payload, proto PPP (0x880b), length 12
E.. I..../#..../h... ..........$
19:54:24.787462 ac:bc:32:83:47:71 > a4:93:4c:76:18:4d, ethertype IPv4 (0x0800), length 156: (tos 0x0, ttl 255, id 42803, offset 0, flags [none], proto GRE (47), length 142)
    172.22.156.47 > 104.238.157.0: GREv1, Flags [key present, sequence# present, ack present], call 6656, seq 8011, ack 7460, proto PPP (0x880b), length 122
    Compressed (0x00fd), length 106: compressed PPP data
E....3.../...../h...0....j.....K...$..=o.\...\q..Oj.....b@......e_2D.?.........x1kvF
].=..r.... Y......C...D.....I.y..N?^...........-6vQ<b\...
19:54:24.860033 ac:bc:32:83:47:71 > a4:93:4c:76:18:4d, ethertype IPv4 (0x0800), length 120: (tos 0x0, ttl 127, id 37743, offset 0, flags [none], proto UDP (17), length 106)
    172.22.156.47.52693 > 112.80.248.135.8829: UDP, length 78
E..j.o........./pP....  K..B.A.>...... r.Ar..e-g..3..bZ
```

####tcpdump -w filename.pcap

把抓到的包信息存储到filename.pcap文件中， 可以用[wireshark](https://www.wireshark.org/)分析

####其他选项开关介绍

**-C filesize** : 当用-w filename 把抓到的数据包写到filename文件时，检查文件大小，当文件大小达到filesize，新建文件filename1继续写,直到tcpdump收到结束命令

示例: tcpdump -vvv -C 1 -w filename

运行一段时间后，当前文件夹下生成如下文件列表：

```
$ ls -lht
total 22352
-rw-r--r--  1 root  staff   396K 11 27 21:25 filename11
-rw-r--r--  1 root  staff   977K 11 27 21:25 filename10
-rw-r--r--  1 root  staff   977K 11 27 21:25 filename9
-rw-r--r--  1 root  staff   977K 11 27 21:25 filename7
-rw-r--r--  1 root  staff   977K 11 27 21:25 filename8
-rw-r--r--  1 root  staff   977K 11 27 21:25 filename6
-rw-r--r--  1 root  staff   977K 11 27 21:25 filename5
-rw-r--r--  1 root  staff   977K 11 27 21:25 filename2
-rw-r--r--  1 root  staff   977K 11 27 21:25 filename3
-rw-r--r--  1 root  staff   978K 11 27 21:25 filename4
-rw-r--r--  1 root  staff   978K 11 27 21:25 filename1
-rw-r--r--  1 root  staff   977K 11 27 21:25 filename
```

<a id="参考"></a>
##参考

[tcpdump tutorial](http://www.binarytides.com/tcpdump-tutorial-sniffing-analysing-packets/)

[man tcpdump](http://www.tcpdump.org/tcpdump_man.html)
