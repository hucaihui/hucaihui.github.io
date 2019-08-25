---
layout: post
title: 为jekyll搭建的blog生成tags页面
tags: jekyll tag blog
---

##参考

[Adding tag cloud and archives page to Jekyll](http://blog.meinside.pe.kr/Adding-tag-cloud-and-archives-page-to-Jekyll/)

##简介
本文介绍如何不使用插件为github page添加标签页

##1. touch tags.html

在博客根目录生成一个tags.html文件，内容如下：


{% highlight html linenos %}
{% raw %}

---
layout: page
permalink: /tags/
---
<ul class="tag-cloud">
{% for tag in site.tags %}
  <li style="font-size: {{ tag | last | size | times: 100 | divided_by: site.tags.size | plus: 70  }}%">
    <a href="#{{ tag | first | slugize }}">
      {{ tag | first }}
    </a>
  </li>
{% endfor %}
</ul>

<div id="archives">
{% for tag in site.tags %}
  <div class="archive-group">
    {% capture tag_name %}{{ tag | first }}{% endcapture %}
    <h3 id="#{{ tag_name | slugize }}">{{ tag_name }}</h3>
    <a name="{{ tag_name | slugize }}"></a>
    {% for post in site.tags[tag_name] %}
    <article class="archive-item">
      <h4><a href="{{ root_url }}{{ post.url }}">{{post.title}}</a></h4>
    </article>
    {% endfor %}
  </div>
{% endfor %}
</div>
{% endraw %}
{% endhighlight %}

创建之后可以,可用通过root_url/tags来访问，比如我的就是`http://huyongde.github.io/tags/` 来访问tags页面

##2. 为每个post文章添加相关的tag链接

新建一个文件`_include/post-tag.html`

内容如下:

{% highlight html %}
{% raw %}
<div class="post-tags">
  Tags: 
  {% if post %}
    {% assign tags = post.tags %}
  {% else %}
    {% assign tags = page.tags %}
  {% endif %}
  {% for tag in tags %}
  <a href="/tags/#{{tag|slugize}}">{{tag}}</a>{% unless forloop.last %},{% endunless %}
  {% endfor %}
</div>
{% endraw %}
{% endhighlight %}

在_layout/post.html中想要添加相关tag链接的地方加入代码
{% highlight html %}
{% raw %}
{% include post-tags.html %}
{% endraw %}
{% endhighlight %}

我的_layout/post.html修改的内容如下:

{% highlight html %}
{% raw %}
       <h1 class="post-title" itemprop="name headline">{{ page.title }}</h1>
       {% include post-tag.html %}
{% endraw %}
{% endhighlight %}

##3. 添加css配置

需要添加的内容如下:

{% highlight css linenos %}
// for tag cloud and archives
.tag-cloud {
  list-style: none;
  padding: 0;
  text-align: justify; 
  font-size: 16px;
  li {
    display: inline-block;
    margin: 0 12px 12px 0; 
  }
}
#archives {
  padding: 5px;
}
.archive-group {
  margin: 5px;
  border-top: 1px solid #ddd;
}
.archive-item {
  margin-left: 5px;
}
.post-tags {
  text-align: right;
}
{% endhighlight %}

##4. 效果

* tags页效果: ![tags](/image/tags.png)

* post页效果: ![post](/image/post.png)




