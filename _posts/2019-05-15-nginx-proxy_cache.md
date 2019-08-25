---
title: nginx proxy_cache指令集详解
layout: post
tags: nginx
---
### 介绍

在使用nginx做反向代理时, 部分业务场景可能可以使用proxy_cache来降低后端的压力，
nginx 提供了丰富的指令来配置符合业务场景的cache策略。

下面分别介绍下nginx proxy_cache相关的指令和用法

### 指令介绍

#### 1. proxy_cache

```
Syntax: proxy_cache zone | off;
Default: proxy_cache off;
Context: http, server, location
```
指令`proxy_cache` 用来配置用来做cache的一块内存区域，也可以用来关闭cache功能, 
参数为off时关闭当前配置块中的cache功能。

`proxy_cache` 可以在http, server 以及location配置块中使用

#### 2. proxy_cache_background_update

```
Syntax: proxy_cache_background_update on | off;
Default: proxy_cache_background_update off;
Context: http, server, location
```
`proxy_cache_background_update` 用来控制当给用户返回一个过期的陈旧cache时
是否可以通过一个后台的子请求来更新当前cache, 需要和`proxy_cache_use_stale` 指令配合使用

#### 3. proxy_cache_use_stale
```
Syntax: proxy_cache_use_stale error | timeout | invalid_header | updating | http_500 | http_502 | http_503 | http_504 | http_403 | http_404 | http_429 | off ...;
Default: proxy_cache_use_stale off;
Context: http, server, location
```
`proxy_cache_use_stale` 来配置在请求后端时，出现那些情况，可以用一个过期的陈旧cache返回给用户
此指令的参数和proxy_next_upstream是基本一致的，额外增加了updating参数，
updating参数是指当正在更新一个cache时，对这个cache的请求可以返回一个陈旧的版本。

#### 4. proxy_cache_valid
```
Syntax: proxy_cache_valid [code ...] time;
Default: —
Context: http, server, location
```
`proxy_cache_valid` 指令用来配置每个类型状态码的cache有效时间，示例:

```
proxy_cache_valid 200 302 10m; ## 200 302 状态码，cache有效期10分钟
proxy_cache_valid 404 1m; ## 404 状态码，cache 1分钟 
```
##### code 参数介绍:
1. code参数时可以省略的，省略时code默认值是200 301 302
2. code参数取值为any时，表示所有的请求都会被cache

##### 需要注意的地方
1. 可以通过`X-Accel-Expires` 头来设置返回结果的cache时间，取值为0表示不做作cache, 取值如果以@开头，
表示在某个时间点之前有效，`X-Accel-Expires`比`proxy_cache_valid`指令优先级高
2. 可以通过`Expires` 或者 `Cache-Control` 设置cache策略
3. 带有`Set-Cookie`头的请求不会被cache
4. `Vary` 头的取值为`*`时，返回结果不会被cache, 其他取值时，可以被cache

> 上面介绍的返回头，可以通过`proxy_ignore_headers` 来禁用


#### 5. proxy_cache_bypass
```
Syntax: proxy_cache_bypass string ...;
Default: —
Context: http, server, location
```
`proxy_cache_bypass` 用来配置那些请求不使用cache, 
当配置的参数中，有一个值不为0或者不为空时，这个请求就不使用cache

#### 6. proxy_no_cache
```
Syntax: proxy_no_cache string ...;
Default: —
Context: http, server, location

```
`proxy_no_cache` 用来配置那些请求后端的结果不存储到cache
当配置的参数中，有一个值不为0或者不为空时，这个请求，请求后端获取的结果就存储到cache中

#### 7. proxy_cache_convert_head
```
Syntax: proxy_cache_convert_head on | off;
Default: proxy_cache_convert_head on;
Context: http, server, location
This directive appeared in version 1.9.7.
```
`proxy_cache_convert_head` 用来配置是否把head请求转为get请求，来做cache， 当取值为off时，
需要把`$request_method`加到cache_key的配置指令中

#### 8. proxy_cache_key 
```
Syntax: proxy_cache_key string;
Default: proxy_cache_key $scheme$proxy_host$request_uri;
Context: http, server, location
```
`proxy_cache_key` 用来配置cache时所使用的key, 示例:
```
proxy_cache_key "$host$request_uri $cookie_user";
``` 
默认情况下，参数取值和下面的是接近的
```
proxy_cache_key $scheme$proxy_host$uri$is_args$args;
```
通过请求协议、代理域名、请求路径以及参数来做cache_key

#### 9. proxy_cache_lock
```
Syntax: proxy_cache_lock on | off;
Default: proxy_cache_lock off;
Context: http, server, location
This directive appeared in version 1.1.12.
```
`proxy_cache_lock` 用来配置同一时刻更新cache, 是否限制只有一个请求更新cache。 取值为on时，
其他请求需要等待更新请求返回或者超时, 超时时间通过`proxy_cache_lock_timeout`来设置。

#### 10. proxy_cache_lock_timeout
```
Syntax: proxy_cache_lock_timeout time;
Default: proxy_cache_lock_timeout 5s;
Context: http, server, location
This directive appeared in version 1.1.12.
```
`proxy_cache_lock_time`指令用来给指令`proxy_cache_lock` 设置超时时间。
默认超时时间是5秒

#### 11. proxy_cache_lock_age
```
Syntax: proxy_cache_lock_age time;
Default: proxy_cache_lock_age 5s;
Context: http, server, location
This directive appeared in version 1.7.8.
```
当配置`proxy_cache_lock on;` 时，proxy_cache_lock_age用来配置当最新的用来更新cache的请求在time时间为能完成cache更新时 ，
 允许另外一个请求取请求后端，来更新cache, 
默认是5秒

#### 12. proxy_cache_max_range_offset
```
Syntax:	proxy_cache_max_range_offset number;
Default: —
Context: http, server, location
This directive appeared in version 1.11.6.
```

这个指令会设置一个字节单位的值，当http 分片请求的range大于设置的值时，这个分片请求不会命中cache,并且从后端请求的结果页不会更新cache.

#### 13. proxy_cache_methods
```
Syntax:	proxy_cache_methods GET | HEAD | POST ...;
Default: proxy_cache_methods GET HEAD;
Context: http, server, location
This directive appeared in version 0.7.59.
```
`proxy_cache_methods` 用来配置那些http Method的请求会启用cache

#### 14. proxy_cache_min_uses
```
Syntax:	proxy_cache_min_uses number;
Default: proxy_cache_min_uses 1;
Context: http, server, location
```

`proxy_cache_min_uses` 用来设置同样请求被请求多少次之后会写入到cache, 默认值时1,
即所有满足配置的请求的返回结果都会写入cache

#### 15. proxy_cache_path
```
Syntax:	proxy_cache_path path [levels=levels] [use_temp_path=on|off] keys_zone=name:size [inactive=time] [max_size=size] [manager_files=number] [manager_sleep=time] [manager_threshold=time] [loader_files=number] [loader_sleep=time] [loader_threshold=time] [purger=on|off] [purger_files=number] [purger_sleep=time] [purger_threshold=time];
Default: —
Context: http
```
`proxy_cache_path` 用来设置cache的路径以及一些其他配置。levels用来配置目录的层级，以及每个层级的目录命名是由几个16进制的字符表示，
示例:
```
proxy_cache_path /root/data/proxy_cache_path levels=1:2 keys_zone=cache:1024m max_size=1024m inactive=15m;
```
其中,
* levels=1:2表示，共有两层目录，第一层目录的名称都是由一个16进制字符表示，第二层目录名称是由两个16进制字符表示
* keys_zone 用来配置cache的名称以及内存空间大小
* max_size 用来配置磁盘cache空间的上限
* inactive 用来配置一个cache多久没有被访问就会失效


#### 16. proxy_cache_purge
```
Syntax:	proxy_cache_purge string ...;
Default: —
Context: http, server, location
This directive appeared in version 1.5.7.
```
`proxy_cache_purge` 用来配置cache清除的一些策略, 使用示例:

```
    location ~ /purge(/.*)
    {
        #设置值允许指定的ip或ip段才可以清除proxy缓存
        allow 127.0.0.1
        allow 192.168.0.0/16;
        deny all;
        proxy_cache_purge cache_name $host$1$is_args$args
    }
    access_log off;
}
```
其中cache_name是通过`proxy_cache`指令设置的cache名称
基于如上配置,
假设一个URL为http://xxx.com/aaa.jpg被proxy cache住了，可以通过访问, http://xxx.com/purge/aaa.jpg来清除该url对应的缓存

#### 17. proxy_cache_revalidate
```
Syntax:	proxy_cache_revalidate on | off;
Default: proxy_cache_revalidate off;
Context: http, server, location
This directive appeared in version 1.5.7.
```
`proxy_cache_revalidate` 用来配置是否开启过期cache的重新验证, 通过请求头`If-Modified-Since` 和`If-None-Match`来做验证。


### 完整的proxy_cache示例
```
location /getuserinfo {  
    proxy_pass http://userinfo_upstream;
  
    proxy_cache_revalidate on;   
  
    proxy_cache content; #根keys_zone后的内容对应
    proxy_cache_valid  200 304 301 302 1h;   #哪些状态缓存多长时间
    proxy_cache_methods GET;  # 设置那些http method启用cache, 默认是get和head
    proxy_cache_valid  any 3s;    #其他的缓存多长时间 
    proxy_cache_key $host:$server_port$uri$is_args$args;   #通过key来hash，定义KEY的值 
    proxy_cache_min_uses 1; #只要统一个url,在磁盘文件删除之前，总次数访问到达3次，就开始缓存。  
    proxy_cache_bypass $cookie_nocache $arg_nocache $arg_comment; # 如果任何一个参数值不为空，或者不等于0，nginx就不会查找缓存，直接进行代理转发  
}  
```

### 参考
[ngx_http_proxy_module](http://nginx.org/en/docs/http/ngx_http_proxy_module.html)
