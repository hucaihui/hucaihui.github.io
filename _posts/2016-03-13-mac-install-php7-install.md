---
layout: post
title: mac 安装php7
tags: brew php
---

###homebrew

> The missing package manager for OS X

homebrew可以用来在mac上安装一些软件和库，比如mysql, nginx, redis等，它会把所需要的依赖给你自动安装。

homebrew有基本的几个命令

* brew install xxx
* brew search xxx
* brew update
* brew unintall xxx

homebrew具体请参考官网[homebrew home](http://brew.sh/)

###brew来安装php

安装命令是:`brew install homebrew/php/php70`

安装过程中会遇到`configure: error: Cannot find libz` 的错误，

google了把，发现了个解决方案[cannot find libz](http://codex16.com/mac-osx-brew-install-php56-cannot-find-libz/)

这个问题解决后，又出现了一个GD相关的错误，搞了会没搞定。

###大招
**最后google出来一个安装方式[MAC OS 一行代码安装php7](http://php-osx.liip.ch/) **

**安装方式是`curl -s http://php-osx.liip.ch/install.sh | bash -s 7.0` **

等待一段时间后，终于安装成功了，


```
[ 10:15上午 ]  [ huyongde@huyongde:/usr/local/php5/bin(master✔) ]
 $ ./php -v
PHP 7.0.4 (cli) (built: Mar 10 2016 14:34:46) ( NTS )
Copyright (c) 1997-2016 The PHP Group
Zend Engine v3.0.0, Copyright (c) 1998-2016 Zend Technologies
    with Zend OPcache v7.0.6-dev, Copyright (c) 1999-2016, by Zend Technologies
    with Xdebug v2.4.0RC3, Copyright (c) 2002-2015, by Derick Rethans
```

建议先翻墙再执行命令。终于安装好了，迫不及待把玩一下php7.

下面是PHP7相关配置的路径：

```
 $ ./php --ini
Configuration File (php.ini) Path: /usr/local/php5/lib
Loaded Configuration File:         /usr/local/php5/lib/php.ini
Scan for additional .ini files in: /usr/local/php5/php.d
Additional .ini files parsed:      /usr/local/php5/php.d/10-extension_dir.ini,
/usr/local/php5/php.d/20-extension-opcache.ini,
/usr/local/php5/php.d/50-extension-apcu.ini,
/usr/local/php5/php.d/50-extension-curl.ini,
/usr/local/php5/php.d/50-extension-gmp.ini,
/usr/local/php5/php.d/50-extension-imap.ini,
/usr/local/php5/php.d/50-extension-intl.ini,
/usr/local/php5/php.d/50-extension-mcrypt.ini,
/usr/local/php5/php.d/50-extension-mssql.ini,
/usr/local/php5/php.d/50-extension-pdo_pgsql.ini,
/usr/local/php5/php.d/50-extension-pgsql.ini,
/usr/local/php5/php.d/50-extension-propro.ini,
/usr/local/php5/php.d/50-extension-raphf.ini,
/usr/local/php5/php.d/50-extension-readline.ini,
/usr/local/php5/php.d/50-extension-xdebug.ini,
/usr/local/php5/php.d/50-extension-xsl.ini,
/usr/local/php5/php.d/60-extension-pecl_http.ini,
/usr/local/php5/php.d/99-liip-developer.ini
```


###配置让php7成为默认的php

修改自己的系统配置，我用的是zsh，所以我在`~/.zshrc`中添加了`export PATH=/usr/local/php5/bin:$PATH` 这行代码，

保存退出后，执行`source ~/.zshrc`

现在直接命令行执行php就是php7了。

####大功告成。





