---
layout: post 
title: markdown 学习 
tags: markdown blog
---

主题
======

<h1> {{ page.title }} </h1>

-----

TOC

##Table of Content
* [主题](#主题)
* [参考](#参考)

##段落
通过空行来形成不同的段落

##标题

###atx标题
\# The largest heading (an <h1> tag)

\#\# The second largest heading (an <h2> tag)

.....

\#\#\#\#\#\# The 6th largest heading (an <h6> tag)

###setext标题

\=\=\= 一级标题

\-\-\-二级标题

##引用(blockquotes)
文字前面加上\>，

>这里是个引用

##文字加粗&&斜体
*这里是斜体* (文字前后都加上\*,可以使文字变成斜体）

**这里是粗体** （文字前后都加2个\*,可以变为粗体）

##列表
###无序列表
文字前面机上\*或者\-来表示无须列表

\* item 

\* item

\* item 

效果如下:

* item 
* item
* item 


###有序列表
文字前面加上数字表示有序列表

\1.item1

\2.item2

效果如下:

1. item1
2. item2

##表格

表头1|表头2
-----|------
xxxxx|yyyyy

##链接图片
\![]()

![网球](/image/IMG_1979.JPG )

##代码块
行内代码用\`\` 把代码包起来

代码块用\`\`\`代码\`\`\`

c的`printf()`函数

下面是一段代码

```
local a = xxxx
ngx.say(a)
ngx.print(a)
```

##参考

[*markdown basic*](https://help.github.com/articles/markdown-basics/)

[*markdown master*](https://guides.github.com/features/mastering-markdown/)

[markdown 入门2](http://www.jianshu.com/p/q81RER)

[**markdown 入门精选**](http://ibruce.info/2013/11/26/markdown/)

[**markdown 简体中文教程**](http://wowubuntu.com/markdown/)

[***markdown 编辑器 mou***](http://25.io/mou/)

[markdown 设置图片大小](http://uliweb.clkg.org/wiki/Help/MarkdownSyntax)

*{{ page.date | date_to_string }}*
