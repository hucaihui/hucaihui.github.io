---
layout: post
title: 为blog添加归档页 archives
tags: blog archives 
---

##参考
[**Jekyll archives grouped by date**](http://mikerowecode.com/2010/08/jekyll_archives_grouped_by_year.html)


blog 根目录下创建文件， archives.html , 内容如下：

{% highlight html %}
{% raw %}

---
layout: page
permalink: /archives/
---

<h2>Archives</h2>
<ul>
  {% for post in site.posts %}

    {% unless post.next %}
      <h3>{{ post.date | date: '%Y' }}</h3>
    {% else %}
      {% capture year %}{{ post.date | date: '%Y' }}{% endcapture %}
      {% capture nyear %}{{ post.next.date | date: '%Y' }}{% endcapture %}
      {% if year != nyear %}
        <h3>{{ post.date | date: '%Y' }}</h3>
      {% endif %}
    {% endunless %}

    <li>{{ post.date | date:"%b" }} <a href="{{ post.url }}">{{ post.title }}</a></li>
  {% endfor %}
</ul>

{% endraw %}
{% endhighlight %}


**之后就可以通过huyongde.github.io/archives来访问 按照年份归档的页面了**
