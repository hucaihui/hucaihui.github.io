---
layout: post
title: http 缓存策略
tags: protocol
---

##目录
* [web缓存类型](#type)
* [缓存相关的header](#header)
* [参考](#参考)

<a id="type"></a>
##web缓存的类型

<a id="header"></a>
##缓存相关的header

####response header
* cache-control
* expires
* etag
####request header
* if-modified-since
* if-none-match

####例子

**如下一个304请求的相关header**

* Request Headers

```
Accept:image/webp,image/*,*/*;q=0.8
Accept-Encoding:gzip, deflate, sdch
Accept-Language:zh-CN,zh;q=0.8,en;q=0.6,ja;q=0.4
Cache-Control:max-age=0
Connection:keep-alive
Host:www.cnblogs.com
If-Modified-Since:Sun, 03 Feb 2013 07:04:18 GMT
If-None-Match:"2a497afdc1ce1:0"
Referer:http://www.cnblogs.com/skylar/p/browser-http-caching.html
User-Agent:Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/47.0.2526.73 Safari/537.36
```

* Response Headers

```
Cache-Control:max-age=86400
Connection:keep-alive
Date:Wed, 09 Dec 2015 07:43:34 GMT
Etag:"2a497afdc1ce1:0"
```

<a id="参考"></a>
##参考

[**透过浏览器看HTTP缓存**](http://www.cnblogs.com/skylar/p/browser-http-caching.html)

[**HTTP缓存**](http://www.cnblogs.com/skylar/p/browser-http-caching.html)
