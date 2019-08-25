---
layout: post 
title: jekyll 入门 && jekyll 搭建github page的框架
tags: jekyll blog
---

##参考

* [jekyll语法介绍](http://github.tiankonguse.com/blog/2014/11/10/jekyll-study/)

* [jekyll 安装和初始化站点](http://jobinson.ga/%E5%BB%BA%E7%AB%99%E4%B9%8B%E8%B7%AF/2014/04/27/%E4%BD%BF%E7%94%A8jekyll%E7%94%9F%E6%88%90%E9%9D%99%E6%80%81%E7%AB%99/)

* [jekyll 入门](http://trefoil.github.io/2013/10/05/jekyll.html)

* [markdown 设置图片大小](http://uliweb.clkg.org/wiki/Help/MarkdownSyntax)

主题
======

<h1> {{ page.title }} </h1>

-----

##jekyll 安装

通过gem来安装，gem是`perl`语言各种扩展包得管理工具

安装命令如下：

```
sudo gem install jekyll
```

##初始化站点

```
mdkir jekyll_site
jekyll new jekyll_site
```
执行完 jekyll new jekyll_site

执行`cd jekyll_site; tree`可以看到站点的目录结构,如下:

![jekyll站点目录](/image/tree_re.png)

通过`jekyll server` 就可以启动本地服务查看站点

jekyll server 执行结果如下：

```
Configuration file: /Users/huyongde/tmp/jekyll_site/_config.yml
            Source: /Users/huyongde/tmp/jekyll_site
       Destination: /Users/huyongde/tmp/jekyll_site/_site
 Incremental build: disabled. Enable with --incremental
      Generating...
                    done in 0.259 seconds.
 Auto-regeneration: enabled for '/Users/huyongde/tmp/jekyll_site'
Configuration file: /Users/huyongde/tmp/jekyll_site/_config.yml
    Server address: http://127.0.0.1:4000/
  Server running... press ctrl-c to stop.
```

浏览器访问`127.0.0.1:4000` 就可以在本地看到jekyll生成的blog了，

效果如下图

![本机blog效果图](/image/jekyll_server.png)

[[效果图:/image/jekyll_server.png|center|100px|100px]]


##博客迁移到github pages

github中建立一个项目，项目名称叫 `你的github名字.github.io`,比如我的github账号名字是`huyongde`,

我创建的项目名称就是`huyongde.github.io`, 然后把`jekyll new` 出来的`jekyll_site`文件夹中的文件加到项目中，

过会访问`你的github名字.github.io`, 就可以看到你的github pages 上的blog了。

下图是我的github pages效果图(改过博客主题，加了一些文章之后的)：

![my github page blog](/image/huyongde_githubpages.png)

##jekyll 配置

###代码块的功能不能用解决办法(我这边是如下解决的，仅供参考（MAC OS))：

_config.yml中的`markdown:cramdown` 配置改成`markdown:rdiscount`, 把markdown解释器改成rdiscount ,之后代码块就生效了,代码块示例：

```
$a = "php code";
echo $a;
```

下面是通过highlight高亮的代码:

{% highlight php %}
$a = "php code";
echo $a;
{% endhighlight %}


*{{ page.date | date_to_string }}*
