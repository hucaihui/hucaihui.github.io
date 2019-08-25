---
layout: post
title: nginx 学习(1) - nginx配置
tags: nginx
---

### 简介 
重新学习nginx配置， 简单记录下。	

> 学习连接： http://openresty.org/cn/ebooks.html


#### 0. 变量分类： 

* 用户自定义变量
* 内建变量


#### 1. nginx变量创建赋值作用域

nginx配置里面的变量是nginx服务启动时创建，   请求到达时进行赋值， 每个请求都有一个变量的副本， 请求内部跳转时变量可以跨location使用。也就是说变量的生命期是和请求绑定的， 可以跨多个location。


“回到先前对 Nginx 变量值容器的生命期的讨论，我们现在依旧可以说，它们的生命期是与当前请求相关联的。每个请求都有所有变量值容器的独立副本，只不过当前请求既可以是“主请求”，也可以是“子请求”。即便是父子请求之间，同名变量一般也不会相互干扰。”

摘录来自: agentzh. “agentzh的Nginx教程（2016.07.21版）”。 iBooks. 

> echo_location 或者echo_location_async 发起的子请求， 主请求和子请求都会有自己的变量副本， 不会共用。
> auth_request 发起的子请求， 主请求和子请求会公用变量副本， 共享变量空间。

#### 2.  内建变量

* $request_uri 包含参数的url,
* $uri 不包含参数

#### 2.1 xxxx变量群

* $arg_xxxx 表示xxxx参数，  xxxx字符串不区分大小写
* $http_xxxx, xxxx不区分大小写 用来获取请求头中的xxxx header, 
* $cookie_xxxx ， 不区分大小写 用来获取请求中的cookie xxxx的值
* $sent_http_xxxx， xxxx不区分大小写 返回头xxxx的值

#### 2.2 存取器

设置和读取变量都封装相应的handler

#### 3 nginx配置中指令执行顺序

3.1 nginx对处理请求分为十几个阶段(phase)
指令执行顺序依赖于指令属于哪个阶段， nginx 请求的三个主要阶段，先后顺序是rewrite, access, content

3.2 一个location中只能使用一个content 阶段的指令， 比如echo ,或者content_by_lua, 两个同时使用时， 只会有一个生效。但是可以在一个location中使用多个echo, 因为多个echo同属于ngx_echo模块。

3.3 content阶段存在三个垫底的静态资源服务模块ngx_index, ngx_autoindex 以及ngx_static。

3.4 Nginx处理请求的11个阶段： 

1. post-read 阶段， 此阶段存在的指令有ngx_realip模块的指令： set_real_ip_from, 以及 real_ip_header, 这两个指令配合使用， 使用示例：
` set_real_ip_from 127.0.0.1; real_ip_header X-Real-ip; `
把来自127.0.0.1的请求的remote_addr 设置为header x-real-ip的值。 后续的阶段或者后端CGI读取的remote_addr都是post-read修改之后的值。 
""注意 只有在x-real-ip header的值是合法ip时， 才会在post_read阶段替换remote_addr""

2. server-rewrite 阶段， ngx_rewrite模块的指令直接在server模块中调用就属于server-rewrite阶段， 比如set, rewrite指令
3. find-config阶段， 此阶段会完成请求和location的配对。
4. rewrite阶段， 请求和某个location配对之后， 便是rewrite阶段， ngx_rewrite模块的指令运行在location中便是在rewrite阶段， 以及ngx_lua的set_by_lua， rewrite_by_lua。
5. post-rewrite阶段， rewrite之后是post-rewrite阶段，来做内部跳转，内部跳转的本质是把请求回退到find-config阶段， 对重写后的请求继续和location进行配对
6. preaccess阶段， post-rewrite 之后便是preaccess 阶段， ngx_limit_req和ngx_limit_zone模块的指令就运行在preaccessJ阶段
7. access 阶段， preaccess之后便是access阶段
8. post-access阶段，satisfy 作用于post-access阶段， satisfy指令用来配合access阶段的控制命令来使用。
9. try-files阶段，此阶段主要是来实现try-files指令， 
10. content
11. log

> try_files 指令接受两个以上任意数量的参数，每个参数都指定了一个 URI. 这里假设配置了 N 个参数，则 Nginx 会在 try-files 阶段，依次把前 N-1 个参数映射为文件系统上的对象（文件或者目录（/结尾会查找目录， 非/结尾会查找文件），然后检查这些对象是否存在。一旦 Nginx 发现某个文件系统对象存在，就会在 try-files 阶段把当前请求的 URI 改写为该对象所对应的参数 URI（但不会包含末尾的斜杠字符，也不会发生 “内部跳转”）。如果前 N-1 个参数所对应的文件系统对象都不存在，try-files 阶段就会立即发起“内部跳转”到最后一个参数（即第 N 个参数）所指定的 URI.

摘录来自: agentzh. “agentzh的Nginx教程（2016.07.21版）”。 iBooks. 


### 参考
[agentzh 的 Nginx 教程（版本 2016.07.21）](https://openresty.org/download/agentzh-nginx-tutorials-zhcn.html)

### 备注
> 文中内容仅供参考， 实际使用请自行测试。

附上相关看nginx教程时写的nginx conf


```
worker_processes 1;
error_log /Users/huyongde/log/nginx/error.log debug;
pid /Users/huyongde/log/nginx.pid;

events {
    worker_connections 1024;
}

http {
    log_format main  '$remote_addr - $remote_user [$time_local] "$request" '
                      '$status $body_bytes_sent "$http_referer" '
                      '"$http_user_agent" "$http_x_forwarded_for"';
    access_log /Users/huyongde/log/nginx/access.log main;
    sendfile on;
    tcp_nopush on;
    tcp_nodelay  on;
    keepalive_timeout 10;
    types_hash_max_size 2048;

    server {
        listen 8666;
        server_name default;

        set $addr $remote_addr;   ##set指令属于ngx_rewrite模块 运行于server-rewrite阶段, 在post-read阶段之后

        set_real_ip_from 127.0.0.1;    ##这两个指令属于ngx_realio模块运行在post-read阶段，post阶段是nginx处理请求的最早阶段
        real_ip_header Real-Ip;

        location /satisfy {
            satisfy any;
            deny all;
            access_by_lua "ngx.exit(ngx.OK)";
            echo "satisfy all";
        }

        location /foo {
            rewrite ^ /bar;
            rewrite ^ /baz;
        }

        location /bar {
            echo "bar";
        }

        location /baz {
            echo "baz";
        }



        location /test {
            echo "addr $addr";
            echo "remote_addr : $remote_addr";
            set $b "$a , test";
            echo "b: $b";
        }
        set $a "Hello from Server_rewrite"; ## 运行在server_rewrite 阶段， 所以早于所有location内的指令

        location /test2 {
            echo "args : $args";
        }

    }

    server {
        listen 8070;
        server_name default;
        location /static2 {
            root /Users/huyongde/Desktop/html;
            try_files /foo =404;  # 在root目录下查找foo文件， 找不到就返回404 , 404可以修改为任一http状态码
        }
        location /static3 {
            root /Users/huyongde/Desktop/html;
            try_files /bar/ =404; # 在root目录下查找bar目录， 若不存在则返回404 , 若存在bar目录， 则请求uri会被设置为/bar匹配/bar location, 测试时直接返回了301， response header location 是/bar?$args
#bar 目录存在时请求 127.0.0.1:8070/static3?a=1&b=2 返回如下：
#< HTTP/1.1 301 Moved Permanently
#< Server: openresty/1.11.2.5
#< Date: Sun, 05 Nov 2017 14:05:07 GMT
#< Content-Type: text/html
#< Content-Length: 191
#< Location: http://127.0.0.1:8070/bar/?a=1&b=2
#< Connection: keep-alive
#<
#<html>
#<head><title>301 Moved Permanently</title></head>
#<body bgcolor="white">
#<center><h1>301 Moved Permanently</h1></center>
#<hr><center>openresty/1.11.2.5</center>
#</body>
#</html>

        }

        location /static {
            set $orig_uri $uri;
            set $orig_request_uri $request_uri;
            root /Users/huyongde/Desktop/html;
            try_files /index.html /index.htm /not_found; ### 在根目录下查找index.html文件以及index.htm文件，若找到，则把当前请求的uri改写为匹配的try_files参数中的URI， 若前n-1个都不匹配则会跳转到第n个参数指定的uri.
            #echo "Orig_uri: $orig_uri, now uri: $uri";
            #echo "Orig_request_uri: $orig_request_uri, now uri: $request_uri";
            #index index.html index.htm; ### index 指令就是执行了内部跳转
        }

        location /not_found {
            echo "not found";
        }
        location /index.html {
            set $a 10000;
            echo "a : $a";
        }
        location /phase {
            # rewrite phase
            set $age 100;
            rewrite_by_lua "ngx.var.age = ngx.var.age + 10";
            # access phase
            allow 127.0.0.1;
            deny all;
            access_by_lua "ngx.var.age = ngx.var.age + 12";

            #content phase
            echo "Age : $age";

        }
        location /lua {
            content_by_lua '
                if ngx.var.arg_name == nil then
                    ngx.say("param missing")
                else
                    ngx.say("name:[", ngx.var.arg_name, "]" )
                end
            ';
        }
        location /auth {
            allow 127.0.0.1;
            deny all;
            echo "auth example";
            access_by_lua '
                if ngx.var.remote_addr == "127.0.0.1"  then
                    ngx.say("from access_by_lua")
                else
                    ngx.exit(403)
                end
            ';
        }

        location /main {  ## 测试主请求  子请求
            set $var main;
            echo_location /child1;
            echo_location /child2;
            echo "main : var $var";
        }

        location /child1 {
            echo "child1";
            set $var child1_var;
            echo "child1 var : $var";
        }
        location /child2 {
            echo "child2";
            set $var "child2_var";
            echo "child2 var: $var";
        }

        location /proxy {
            set $args "a=1&b=2";
            echo_before_body "before proxy";
            # 不能直接使用echo指令， echo指令和proxy_pass指令同属content阶段，只会执行proxy_pass, 下面的echo_after_body同理
            #
            proxy_pass http://127.0.0.1:8666/test2; ## 参数会自动带到新的请求上
            echo_after_body "after proxy";
        }

        location /test {
            set $foo "Hello nginx " ;
            set $a "$foo  $foo ${foo}xxxx";
            echo "test echo :$a";
            echo  "uri = $uri";
            echo  "request_uri: $request_uri";
            echo "params a arg_a: $arg_a";
            echo "params a arg_A: $arg_A";
            echo "header test: $http_test";
            echo "header Test: $http_Test";
            echo "cookie test: $cookie_test";
            echo "cookie Test: $cookie_Test";
            set $sent_http_test "res test header";

            set $orig_test $arg_test;
            echo "origin param test: $orig_test";
            set $args "test=confset";
            echo "param test : $arg_test";
        }

        location /foo {
            set $a  "foo";
            #echo_exec /bar;
            rewrite ^ /bar;
        }
        location /bar {
            echo "a=${a}";
        }

    }
}
```
