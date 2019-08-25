---
layout: post
title: 检查当前svn路径下面修改的PHP文件是否有语法错误(以及其他小技巧)
tags: php svn syntax
---

#### 1. 检查修改的php代码是否有语法错误

一行`shell`代码搞定，代码如下：

```
cd $1;for i in `svn st | awk '$1=="M" || $1=="A"{print $2}'`; do php -l $i;done
```

> 使用说明:$1是要检查的文件夹路径，借助php -l参数，来完成检查 

#### 2. 批量添加文件下新添加的文件到svn

同样是一行代码:


```
svn add `svn st | grep -E "^\?.*.php" | awk '{print $2}' | xargs`
```


