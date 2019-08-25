---
layout: post
title: vim markdown语法高亮插件
tags: vim markdown highlight
---


[插件vim-markdown  github 主页](https://github.com/plasticboy/vim-markdown)

## 安装插件

安装直接添加如下plugin配置, 然后执行PluginInstall(前提是你已经安装了vim-Plugin)

```
Plugin 'godlygeek/tabular'
Plugin 'plasticboy/vim-markdown'
```

## 其他配置

```
let g:vim_markdown_folding_disabled = 1 """"设置不做代码折叠
let g:vim_markdown_frontmatter=1 "" 设置支持yaml语法
```


设置完后就可以愉快的在vim下写jekyll搭建的博客的文章了。
