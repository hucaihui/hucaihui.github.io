---
layout: post
titile: nginx proxy_next_upstream 配置指令
tags: nginx
---

### 介绍
在使用nginx做代理时，为了容错单点故障，保证服务高可用，可以通过proxy_next_upstream指令来实现某些错误时进行请求重试，
下面详细介绍下proxy_next_upsream相关的几个指令

### proxy_next_upstream
```
Syntax: proxy_next_upstream error | timeout | invalid_header | http_500 | http_502 | http_503 | http_504 | http_403 | http_404 | http_429 | non_idempotent | off ...;
Default: proxy_next_upstream error timeout;
Context: http, server, location

```
1. 当通过proxy模块转发请求时，若后端出现` error | timeout | invalid_header | http_500 | http_502 | http_503 | http_504 | http_403 | http_404 | http_429 | non_idempotent`错误时可以重试到upstream配置的下一个后端上，
2. 默认是在error 和 timeout时会重试
3. proxy_next_upstream指令用在http, server以及location配置块中

配置选项详细介绍:
1. error: 和后端建立连接出错，或者从后端读取数据时出错
2. timeout: 和后端交互时发生了超时
3. invalid_header: 后端返回了空的或者非法的数据
4. http_xxx: 后端返回的错误码时xxx, xxx可能为: 500,502,503,504,403,404,429
5. non_idempotent: 默认情况下，对于非幂等请求(POST, LOCK,PATH等) 是不会进行重试的; 但是在增加了这个配置选项时，非幂等的请求也会重试
6. off: 关闭重试

### proxy_next_upstream_timeout

```
Syntax: proxy_next_upstream_timeout time;
Default: proxy_next_upstream_timeout 0;
Context: http, server, location
This directive appeared in version 1.7.5.
```
proxy_next_upstream_timeout用来设定重试时的超时时间，默认值时0，没有超时时间；只在1.7.5以及以后的版本支持

### proxy_next_upstream_tries 

```
Syntax: proxy_next_upstream_tries number;
Default: proxy_next_upstream_tries 0;
Context: http, server, location
This directive appeared in version 1.7.5.
```

proxy_next_upstream_tries 设置可以重试的次数，默认值为0， 表示只要出错，就一直重试下去


### 参考
[proxy_next_upstream](http://nginx.org/en/docs/http/ngx_http_proxy_module.html#proxy_next_upstream)

