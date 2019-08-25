---
layout: post
title: nginx error_page指令配置
tags: nginx
---

#### 背景介绍
在服务改造优化上线过程中，可能需要用之前的服务对新服务做容错，我们在nginx代理层增加了

```
error_page 403 404 408 500 501 502 503 504  @backend2;

```

当新服务出现403时，用backend2来容错，backend2正常返回了200状态码，但是端上收到的还是403状态码，
通过查看nginx文章，发现是配置存在问题导致，缺少了`=`号，
配置改为

```
    error_page 403 404 408 500 501 502 503 504 = @backend2;

```
这样，端上收到的状态码就是backend2返回的状态码了。

#### error_page 指令详解

```
Syntax: error_page code ... [=[response]] uri;
Default:    —
Context:    http, server, location, if in location
```
error_page的作用是当请求返回特定状态码时可以通过uri来容错，code是 http的状态码，可以配置多个code
error_page 可以用在http ,server ,location配置块中，以及location的if配置块中

示例:

```
error_page 404             /404.html;
error_page 500 502 503 504 /50x.html;
```

并且error_page支持通过=号来修改返回码，
示例:
```
error_page 404 =200 /empty.gif;
```
error_page还支持把uri返回的状态码返回给用户
示例:
```
error_page 404 = /404.php;
```

error_page 允许出现错误时，把请求内部重定向到另一个location, 并且把新location的状态码返回给用户
示例:
```
location / {
    error_page 404 = @fallback;
}

location @fallback {
    proxy_pass http://backend;
}
```

error_page 同样支持在出错时对请求做跳转
示例:
```
error_page 403      http://example.com/forbidden.html;
error_page 404 =301 http://example.com/notfound.html;
```

### 参考
[ngx_http_core_module](http://nginx.org/en/docs/http/ngx_http_core_module.html#error_page)
