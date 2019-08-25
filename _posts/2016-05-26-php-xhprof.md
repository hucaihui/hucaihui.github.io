---
layout: post
title: xhprof 分析php应用程序的性能
tags: php xhprof
---

主要是四个步骤 

1. 安装php xhprof扩展

2. 代码入口加上xhprof的启用和分析数据收集的代码

3. 分析数据可视化， xhprof_data目录需要修改权限，否则可能存在写分析数据和读分析数据失败的问题

4. 安装graphviz 之前需要确定是否安装了libpng,最好自己安装一遍libpng, [参考](https://www.cnxct.com/you-do-not-have-dot-image-generation-utility-installed/)


