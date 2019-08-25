---
layout: post
title: 显示post的相关文章(有相同的tag) related_posts
tags: blog jekyll related_posts
---

##参考

* [jekyll related_posts](http://zhangwenli.com/blog/2014/07/15/jekyll-related-posts-without-plugin/)


##不用插件,显示文章相类似文章

直接把显示相似文章的代码放到了_layout/post.html中了，为每个post显示相关的posts。

代码如下

{% highlight html %}
{% raw %}
<div style="float:right;">
    {% assign hasSimilar = '' %}
    {% for post in site.related_posts %}
        {% assign postHasSimilar = false %}
        {% for tag in post.tags %}
            {% if postHasSimilar == false %}
                {% for thisTag in page.tags %}
                    {% if postHasSimilar == false and hasSimilar.size < 5 and post != page and tag == thisTag %}
                        {% if hasSimilar.size == 0 %}
                            <h3 class="page-heading">相关文章:</h3>
                            <ul>
                        {% endif %}
                        <li> <span class="post-meta">{{ post.date | date: "%b %-d, %Y" }}</span>

                        <h5> <a href="{{ post.url | prepend: site.baseurl }}">{{ post.title }}</a> </h5>
                        {% assign postHasSimilar = true %}
                    {% endif %}
                {% endfor %}
            {% endif %}
        {% endfor %}

        {% if postHasSimilar == true %}
            {% capture hasSimilar %}{{ hasSimilar }}*{% endcapture %}
        {% endif %}
    {% endfor %}

    {% if hasSimilar.size > 0 %}
    </ul>
    {% endif %}
</div>
{% endraw %}
{% endhighlight %}

我的blog就是左边显示相关的posts，右边显示最新更新的文章。

####自己主要修改的地方：
* 支持正确的显示5个相关文章, 使用的是site.posts，而不是site.related_posts.
 related_posts是一个不包括当前post的，本站的最新的10个post,再久远的就不包括在related_post中了, [jekyll variables](http://jekyllrb.com/docs/variables/) 中有介绍。
* 使用site.posts之后,通过post.id的比较来过滤当前post. 


效果见本博客。
