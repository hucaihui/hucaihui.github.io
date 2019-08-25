---
layout: post
title: 抓包神器 charles, 抓移动端的包
tags: socket charles
---

### 简介

```
之前在thinkpad上，是用猎豹建wifi, 电脑建个热点，手机链接热点，然后wireshark抓包，
但是wireshark follow tcp 流之后看不到请求的response header,
 好坑，好坑，好坑(很low的，大家轻拍)

自从转战mac之后，就没再怎么定位移动端的问题了， 最近PM们又开始说移动端有问题了，
然后说是我们server导致的, 又有了抓移动端的包的需求.

从全能QA 同学那里了解到了charles,看了第一眼我就爱上了这个东西，
logo既然是个大茶壶,谁都不要阻拦我去用它。
```

**charles官网[charles](http://www.charlesproxy.com/)**


### 安装
charles需要是付费的，自然需要安装破解版，

安装文件和破解jar见网盘链接  [链接](http://pan.baidu.com/s/1i4s3rlr) 密码: wg2v

安装很简单，下面说下如何破解， 下载分享链接中的charles.jar,放到指定charles安装的指定目录中，替换原来的charles.jar,如何替换请看下面两个图片：

![one](/image/charles.png)
![two](/image/charles2.png)



### 使用1

启动charles之后，本机端口8888会被监听，若想抓移动端的包，

需要手动设置移动端的网络代理,设置成本机的ip, port 是8888， 本机ip获取可以通过 (系统偏好设置->网络皆可以看得到)，

我的手机是屌丝小米手机，设置截图如下：

![mi note set](/image/charles3.png)


设置好了之后就可以看到移动端访问网络的包了。


### 使用2

```
抓取移动端的https包
```

* 移动端需要配置： 对于移动端https的包，需要移动端额外安装个证书才行，移动端浏览器下载 网盘链接  [链接](http://pan.baidu.com/s/1i4s3rlr) 密码: wg2v 

中的`charles-proxy-ssl-proxying-certificate.crt` 文件提示要安装，随便给证书起个名字，安装好， 移动端配置完成。

* charles需要的配置： charles菜单栏的`Proxy` => `Proxy setting` => `SSL` => `Enable SSL Proxying` ; 之后配置Locations: host为*， port 为443.


```
配置好移动端和charles之后就可以看到详细的https的信息了。

```




### 抓取本机的包

我这遇到一个问题，安装了之后，mac本机的包既然抓不到， 同理，我也去`系统偏好设置->网络`面板，选定mac当前链接的网络，点击`高级`
出现如下面板，在代理中设置web代理为本机8888端口， 就可以从charles看到mac本机的包了。 代理配置如下图：

![mac本机设置](/image/charles4.png)


> 以后再也不怕抓不到移动端的包了。

**charles是java开发的，可移植性很好，支持各个系统，只要有java环境就好。**



#### 参考

* [mac上抓包工具Charles](http://blog.csdn.net/jiangwei0910410003/article/details/41620363)

