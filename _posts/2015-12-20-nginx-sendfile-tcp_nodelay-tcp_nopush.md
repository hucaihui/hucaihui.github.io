---
layout: post
title: nginx 的 sendfile tcp_nodelay  tcp_nopush 配置详解
tags: shell  nginx program protocol
---

## sendfile

现在流行的web 服务器里面都提供 sendfile 选项用来提高服务器性能，那到底 sendfile是什么，怎么影响性能的呢？

sendfile实际上是 Linux2.0+以后的推出的一个系统调用，web服务器可以通过调整自身的配置来决定是否利用 sendfile这个系统调用。

#### 先来看一下不用 sendfile的传统网络传输过程：

```
read(file,tmp_buf, len);
write(socket,tmp_buf, len);
硬盘 >> kernel buffer >> user buffer>> kernel socket buffer >>协议栈
```

**一般来说一个网络应用是通过读硬盘数据，然后写数据到socket 来完成网络传输的。

上面2行用代码解释了这一点，不过上面2行简单的代码掩盖了底层的很多操作。来看看底层是怎么执行上面2行代码的:**

1. 系统调用 `read()`产生一个上下文切换：从 `user mode` 切换到 `kernel mode`，然后 DMA 执行拷贝，把文件数据从硬盘读到一个 `kernel buffer` 里。
2. 数据从 `kernel buffer`拷贝到 `user buffer`，然后系统调用 `read()` 返回，这时又产生一个上下文切换：从`kernel mode` 切换到 `user mode`。
3. 系统调用`write()`产生一个上下文切换：从 `user mode`切换到 `kernel mode`，然后把步骤2读到 `user buffer`的数据拷贝到 `kernel buffer`（数据第2次拷贝到 `kernel buffer`），不过这次是个不同的 `kernel buffer`，这个 `buffer`和 `socket`相关联。
4. 系统调用 `write()`返回，产生一个上下文切换：从 `kernel mode` 切换到 `user mode`（第4次切换了），然后 DMA 从 `kernel buffer`拷贝数据到协议栈（第4次拷贝了）。

**上面4个步骤有4次上下文切换，有4次拷贝，我们发现如果能减少切换次数和拷贝次数将会有效提升性能。在kernel2.0+ 版本中，系统调用 sendfile() 就是用来简化上面步骤提升性能的。sendfile() 不但能减少切换次数而且还能减少拷贝次数。**

#### 再来看一下用 sendfile()来进行网络传输的过程：

```
sendfile(socket,file, len);
```

**硬盘 >> kernel buffer (快速拷贝到kernelsocket buffer) >>协议栈**

1. 系统调用`sendfile()`通过 DMA把硬盘数据拷贝到 `kernel buffer`，然后数据被 `kernel`直接拷贝到另外一个与 `socket`相关的 `kernel buffer`。这里没有 `user mode`和 `kernel mode`之间的切换，在 `kernel`中直接完成了从一个`buffer`到另一个 `buffer`的拷贝。
2. DMA 把数据从 `kernel buffer` 直接拷贝给协议栈，没有切换，也不需要数据从 `user mode` 拷贝到 `kernel mode`，因为数据就在 `kernel` 里。


**步骤减少了，切换减少了，拷贝减少了，自然性能就提升了。**
 
## tcp_nopush
官方文档:

```
tcp_nopush
Syntax: tcp_nopush on | off
Default: off
Context: http
server
location
Reference: tcp_nopush
 
This directive permits or forbids the use of the socket options TCP_NOPUSH on FreeBSD or TCP_CORK on Linux. 
This option is only available when using sendfile.
Setting this option causes nginx to attempt to send it’s HTTP response headers in one packet on Linux and FreeBSD 4.x.
You can read more about the TCP_NOPUSH and TCP_CORK socket options here.
```
 
linux 下是tcp_cork, 上面的意思就是说，当使用sendfile函数时，tcp_nopush才起作用，它和指令tcp_nodelay是互斥的。

tcp_cork是linux下tcp/ip传输的一个标准了，这个标准的大概的意思是，一般情况下，
 
在tcp交互的过程中，当应用程序接收到数据包后马上传送出去，不等待，

而tcp_cork选项是数据包不会马上传送出去，等到数据包最大时，一次性的传输出去，这样有助于解决网络堵塞，已经是默认了。

也就是说tcp_nopush = on 会设置调用tcp_cork方法，这个也是默认的，结果就是数据包不会马上传送出去，等到数据包最大时，一次性的传输出去，这样有助于解决网络堵塞。

*以快递投递举例说明一下（以下是我的理解，也许是不正确的），当快递东西时，快递员收到一个包裹，马上投递，

这样保证了即时性，但是会耗费大量的人力物力，在网络上表现就是会引起网络堵塞.

而当快递收到一个包裹，把包裹放到集散地，等一定数量后统一投递，这样就是tcp_cork的选项干的事情，这样的话，会最大化的利用网络资源，虽然有一点点延迟。
*

***对于nginx配置文件中的tcp_nopush，默认就是tcp_nopush,不需要特别指定，这个选项对于www，ftp等大文件很有帮助。***
 
## tcp_nodelay

`TCP_NODELAY`和`TCP_CORK(tcp_nopush)`基本上控制了包的`nagle化`，agle化在这里的含义是采用Nagle算法把较小的包组装为更大的帧。

`John Nagle`是`Nagle`算法的发明人，后者就是用他的名字来命名的，他在1984年首次用这种方法来尝试解决福特汽车公司的网络拥塞问题（欲了解详情请参看IETF RFC 896）。

他解决的问题就是所谓的silly window syndrome，中文称“愚蠢窗口症候群”

，具体含义是，因为普遍终端应用程序每产生一次击键操作就会发送一个包，

而典型情况下一个包会拥有1个字节的数据载荷以及40个字节长的包头，于是产生**4000%的过载**，很轻易地就能令网络发生拥塞。

 Nagle化后来成了一种标准并且立即在因特网上得以实现。它现在已经成为缺省配置了.

但在我们看来，有些场合下把这一选项关掉也是合乎需要的。

现在让我们假设某个应用程序发出了一个请求，希望发送小块数据。我们可以选择立即发送数据或者等待产生更多的数据然后再一次发送两种策略。

如果我们马上发送数据，那么交互性的以及客户/服务器型的应用程序将极大地受益。

如果请求立即发出那么响应时间也会快一些。以上操作可以通过设置套接字的TCP_NODELAY = on 选项来完成，这样就禁用了Nagle 算法。 

另外一种情况则需要我们等到数据量达到最大时才通过网络一次发送全部数据，这种数据传输方式有益于大量数据的通信性能，典型的应用就是文件服务器。

应用 Nagle算法在这种情况下就会产生问题。但是，如果你正在发送大量数据，你可以设置TCP_CORK选项禁用Nagle化，其方式正好同 TCP_NODELAY相反（TCP_CORK和 TCP_NODELAY是互相排斥的）。 


## 参考

[*nginx sendfile tcp_onpush tcp_nodelay 详解*](http://www.2cto.com/os/201306/222745.html)

[**ngx_http_core_module**](http://nginx.org/en/docs/http/ngx_http_core_module.html)

