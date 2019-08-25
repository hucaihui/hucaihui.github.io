---
layout: post 
title:  整合disqus和jekyll，打造一个支持评论的blog
tags: disqus jekyll blog
---

##目录

* [简介](#简介)
* [教程](#教程)
* [总结](#总结)

<a id="简介"></a>
##一、[disqus](https://disqus.com/) 简介

Millions of people are talking about what they love on Disqus. 

(很多人都在disqus上问题) 

Everything from breaking news to science fiction. 

(自己领会这句话)


<a id="教程"></a>
##二、主要参考教程

[**adding disqus to jekyll**](http://www.perfectlyrandom.org/2014/06/29/adding-disqus-to-your-jekyll-powered-github-pages/)这个大概介绍了怎么添加`disqus`到`jekyll`

[**We were unable to load Disqus**](https://help.disqus.com/customer/portal/articles/472007-i-m-receiving-the-message-%22we-were-unable-to-load-disqus-%22)  里面介绍了，那些原因会导致添加`disqus`失败，

我是因为`this.page.url`设置导致失败的，`this.page.url=window.location.href`之后就OK了。

[**trust domain**](https://help.disqus.com/customer/portal/articles/1261429)

`trust domain` 主要介绍如何把自己的github pages网址，设置到`disqus`信任的域名列表中，

不设置的话 会遇到`We were unable to load Disqus` 错误。

[**disqus configuration variables**](https://help.disqus.com/customer/portal/articles/472098-javascript-configuration-variables) 介绍如何设置相关的变量值，比如 `this.page.url`等。

<a id="总结"></a>
##三、总结

*一定要认真阅读教程，按照理解教程的每一步。*
