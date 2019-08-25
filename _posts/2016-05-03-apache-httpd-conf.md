---
title: apache配置
layout: post
tags: httpd apache
---

### 0. 简介
学习apache配置，主要是按照指令来学习，争取每天学习几个

### 1. 配置指令

#### 1.1 BrowserMatch
对不同的UA进行一些特殊的配置，包括
* nokeepalive 禁用keepalive; eg:BrowserMatch ^Mozilla nokeepalive
* force-response-1.0 对所有请求强制进行http1.0的响应
* downgrade-1.0 对所有的请求强制当作http 1.0 的请求来处理
 
例子:
* BrowserMatch "Mozilla/2" nokeepalive 
* BrowserMatch "MSIE 4\.0b2;" nokeepalive downgrade-1.0 force-response-1.0
* BrowserMatch "RealPlayer 4\.0" force-response-1.0 
* BrowserMatch "Java/1\.0" force-response-1.0 
* BrowserMatch "JDK/1\.0" force-response-1.0

#### 1.2 ErrorDocument

用来配置当出现特定的http code的时候提示文本或者转向的链接

例子：
* ErrorDocument 400 "400 了, please check"
* ErrorDocument 400 "/400.html"

#### 1.3 rewrite
rewirte主要的功能就是实现URL的跳转，它的正则表达式是基于Perl语言。
可基于服务器级的(httpd.conf)和目录级的 (.htaccess)两种方式。
使用rewrite模块前，需要先安装或加载rewrite模块。

基于服务器级的(httpd.conf)有两种方法，

* 一种是在httpd.conf的全局下直接利用RewriteEngine on来打开rewrite功能;
* 另一种是在局部里利用RewriteEngine on来打开rewrite功能

> 下面将会举例说明，需要注意的是,必须在每个virtualhost里用RewriteEngine on来打开rewrite功能。否则virtualhost里没有RewriteEngine on它里面的规则也不会生效。
> 基于目录级的(.htaccess),要注意一点那就是必须打开此目录的FollowSymLinks属性且在.htaccess里要声明RewriteEngine on。

相关配置的指令
* RewriteEngine 设置打开rewrite引擎, `RewriteEngine on`
* RewriteCond 为接下来的第一个RewriteRule，设置条件
* RewriteRule  为满足前面RewriteCond设定的条件的URL，设置跳转规则

完整的例子:

    RewriteCond %{REQUEST_URI} ^/test/
    RewriteCond %{REQUEST_URI} !^.*(.css|.js|.gif|.png|.jpg|.jpeg|.ico|.txt|.swf|.mp3|.mp4|.csv|.xls|.xlsx|.json)$
    RewriteRule /test/(.*) /test/index.php

    
#### 1.4 一些基本的设置
* `ServerRoot`: 之处服务器保存其配置、错误日志和行为日志的根目录， **路径的结尾不要加斜线**. `ServerRoot "/usr/local/apache2"`
* `PidFile`: 设置服务进程，进程号的存放文件， 相对于ServerRoot的路径，`pidFile logs/httpd.pid`
* `KeepAlive`: 设置是否开启链接复用，`KeepAlive On`
* `MaxKeepAliveRequests`: 设置单个链接可以处理的最大请求数,`MaxKeepAliveRequests 100`
* `Listen`: 设置监听得的主机以及端口号
* `ExtendedStatus`: 当调用`server-status`时，是否返回比较全面的信息`ExtendedStatus On`
* `LoadModule`: 设置一些模块加载一些DSO模式编译的模块(DSO是Dynamic Shared Objects（动态共享目标）的缩写)
* `ServerName`: 设定服务器的名字和端口号，和`Listen` 区别开, 若是不能进行DNS解析的域名，可以直接用ip地址代替。
* `DocumentRoot`: 设定文档的根目录，默认情况下，所有请求都从这个目录进行应答, `DocumentRoot "/home/website/html"`
* `<Directory></Directory>`: 设置Apache可以存取目录的存取权限
* `DirectoryIndex`: 定义请求是一个目录时，Apache向用户提供服务的文件名, `DirectoryIndex index.php index.htm index.html index.html.var`
* `EnableSendfile`: 设置是否支持sendfile, sendfile介绍见[nginx sendfile配置](http://huyongde.github.io/2015/12/20/nginx-sendfile-tcp_nodelay-tcp_nopush.html)，`EnableSendfile On` 设置 支持sendfile
* 
* `ErrorLog`, `LogLevel`: 错误日志配置，`ErrorLog logs/error.log`, `LogLevel warn` 
* `CustomLog`, `LogFormat`: 指定access的记录文件，以及accessLog的格式`LogFormat "%h %l %u %t \"%r\" %>s %b \"%{Referer}i\" \"%{User-Agent}i\" %I %O" combinedio`, `CustomLog logs/access_log combinedio`

* `ServerTokens` 设置http response header中server的信息，`Server:Apache`. 默认为“Full”， 这表示在回应头中将包含模块中的操作系统类型和编译信息。可以设为列各值中的一个： Full | OS | Minor | Minimal | Major | Prod. Full传达的信息最多，而Prod最少。

#### 1.5 VirtualHost (update on 2016-05-22 22:27:10 )

VirtualHost 通过设置虚拟主机，来实现一个机器多个域名，多个主机名等
看几个例子:

#### 1.5.1 一个IP上部署多个服务
```
Listen 80
NameVirtualHost *:80
<VirtualHost *:80>
    DocumentRoot /www/example1
    ServerName www.example1.com
    # 其他的一些指令配置
</VirtualHost>

<VirtualHost *:80>
    DocumentRoot /www/example2
    ServerName www.example2.com
    # 其他的指令配置

</VirtualHOst>
```
**多个虚拟主机域名时，当一个不存在的主机域名请求到来时，第一个虚拟主机会服务这个请求**

#### 1.5.2 不同的域名部署在不同的IP上

```
##主服务 运行在172.20.30.40 上
ServerName server.domain.com
DocumentRoot /www/mainserver

###另一个IP
NameVirtualHost 172.20.30.50

<VirtualHost 172.20.30.50>
    DocumentRoot /www/example1
    ServerName www.example1.com
    # 其他的一些指令配置
</VirtualHost>

<VirtualHost 172.20.30.50>
    DocumentRoot /www/example2
    ServerName www.example2.com
    # 其他的一些指令配置
</VirtualHost>
```

**所有不是到.50IP 的请求都是主服务来服务， 所有到.50的，不带Host,或者host不是www.example1.com 和 www.example2.com的都将被第一个虚拟主机来服务**

#### 1.5.3 多个IP上部署同一个服务
```
NameVirtualHost 192.168.0.1
NameVirtualHost 172.20.30.40

<VirtualHost 192.168.0.1 172.20.30.40>
    DocumentRoot /www/server
    ServerName www.server.example.com
    ServerAlias server
</VirtualHost>
```

**可以通过serverAlias server来代替www.server.example.com域名来访问服务**

#### 1.5.4 不同的端口部署不同的服务

```
Listen 80
Listen 8080

NameVirtualHost 172.20.30.40:80
NameVirtualHost 172.20.30.40:8080

<VirtualHost 172.20.30.40:80>
    ServerName www.example1.com
    DocumentRoot /www/domain-80
</VirtualHost>

<VirtualHost 172.20.30.40:8080>
    ServerName www.example1.com
    DocumentRoot /www/domain-8080
</VirtualHost>

<VirtualHost 172.20.30.40:80>
    ServerName www.example2.org
    DocumentRoot /www/otherdomain-80
</VirtualHost>

<VirtualHost 172.20.30.40:8080>
    ServerName www.example2.org
    DocumentRoot /www/otherdomain-8080
</VirtualHost>

```

#### 1.6 目录访问权限控制
主要指令: Order, Allow, Deny。 Order来控制指令Allow和Deny的生效顺序,

也就是说Allow和deny的生效顺序和他们在配置中的位置没有关系，和Order的配置有关。

下面看几个例子

```
<Directory /www/web>
    Order Allow Deny
    Allow from all
    Deny from 112.10.20.30
    ### 先允许所有用户访问再拒绝ip112.10.20.30的访问

</Directory>
```

```
<Directory /web>
    Order Deny,Allow
    Deny from 112.2.10.2
    Allow from all
    Deny from 123.10.10.1
    #先拒绝112.2.10.2访问
    #再拒绝123.10.10.1访问
    #最后允许所有用户访问
    #总结：允许所有用户访问
    #(即使Allow指令在Deny指令前，但是根据Order Deny,Allow语句，仍然先看Deny，再看Allow)
</Directory>
```
#### 1.7 rotatelogs进行日志的切分
`rotatelogs` 可以按照日期或者日志文件大小对日志进行切分.
前面介绍了CustomLog和ErrorLog指令都可以用配合`rotatelogs`使用，

```
CustomLog logs/access.log combinedio

ErrorLog logs/error.log
```
**可以修改为 按照时间来切分日志**

```
CustomLog "| /usr/sbin/rotatelogs -l logs/access-%Y%m%d.log 86400" combinedio

ErrorLog "| /usr/sbin/rotatelogs -l logs/error-%Y%m%d.log 86400" 
```
这样后，会把access.log 和 error.log按照时间进行切分，到达指定的时间点后会对日志进行切分，
86400指定了多长时间进行一次日志切分，单位是秒，如上设置是1天进行一次日志切分， 会产生类似如下文件名的日志文件：

```
access-20160616.log

error-20160616.log
```

**还可以修改为 按照时间来切分日志**

```
CustomLog "| /usr/sbin/rotatelogs  logs/access-%Y%m%d.log 100M" combinedio

ErrorLog "| /usr/sbin/rotatelogs logs/error-%Y%m%d.log 50M" 
```

修改之后，access.log达到100M之后会进行日志切分，error.log日志达到50M后会进行切分，都会加上当前日期的后缀，

**总结rotatelogs用法**

* 格式: `rotatelogs [ -l ] logfile [ rotationtime [ offset ]] | [ filesizeM ]`
* 参数说明

    * -l 使用本地时间代替GMT时间作为时间基准。
    * logfile 日志文件名
    * rotationtime 日志切分进行的时间间隔， 时间单位秒
    * offet 相对UTC的时差分钟数， 可以省略，如果省略， 则假定为0并使用UTC时间
    * filesizeM 指定文件达到多大时进行切分，文件大小单位是M

**配置切分日志格式的字符串**

*  星期名全称(本地的) 
*  %a 3个字符的星期名(本地的) 
*  %B 月份名的全称(本地的) 
*  %b 3个字符的月份名(本地的) 
*  %c 日期和时间(本地的) 
*  %d 2位数的一个月中的日期数 
*  %H 2位数的小时数(24小时制) 
*  %I 2位数的小时数(12小时制) 
*  %j 3位数的一年中的日期数 
*  %M 2位数的分钟数 
*  %m 2位数的月份数 
*  %p am/pm12小时制的上下午(本地的) 
*  %S 2位数的秒数 
*  %U 2位数的一年中的星期数(星期天为一周的第一天) 
*  %W 2位数的一年中的星期数(星期一为一周的第一天) 
*  %w 1位数的星期几(星期天为一周的第一天) 
*  %X 时间(本地的) 
*  %x 日期(本地的) 
*  %Y 4位数的年份 
*  %y 2位数的年份 
*  %Z 时区名 
*  %% 符号"%"本身 

未完待续

#### 参考 
* [apache配置文件httpd.conf内容翻译](http://wiki.ubuntu.org.cn/index.php?title=Apache%E9%85%8D%E7%BD%AE%E6%96%87%E4%BB%B6httpd.conf%E5%86%85%E5%AE%B9%E7%BF%BB%E8%AF%91&variant=zh-hans)
