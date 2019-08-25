---
layout: post
title: linux 设置输出内容的颜色
tags: shell
---

##**目录**
* [例子](#例子)
* [自己的使用](#my)
* [参考](#参考)


<a id="例子"></a>
先看下一个输出绿色字体的例子

`echo "colored:\e[32m\e[1mhello world\e[0m";echo "end_color"`

输出结果如下:

![例子](/image/color.png)

其中，

`\e[32m\e[1m` 用来设置输出字体的颜色

`\e[0m` 清楚开始的设置，否则之后所有的输出都是设置的字体颜色

<a id="my"></a>
##自己的使用

脚本代码如下:

```
#!/bin/zsh
set_color="\e[32m\e[1m"
clear_color="\e[0m"
git add . &&  echo -e "$set_color git add .     done"
echo -e "$clear_color"
git commit -m "$1" && echo "$set_color git commit -m \"$1\"  done"
echo -e "$clear_color"
git push origin master && echo "$set_color git push origin master done"
echo -e "$clear_color"
```

脚本是用来提交并push本地修改代码到github主干的,并把`add, commit push `三步的执行结果高亮打出来，

脚本运行的效果如下:

![res](/image/add_commit_push_res.png)

<a id="参考"></a>
##参考

[linux终端中输出彩色字体](http://basiccoder.com/output-colorful-words-in-terminal.html)



