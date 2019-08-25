---
layout: post
title: vim 插件管理 vundle
tags: shell vim
---


##参考
[***vundle配置vim使用的基本插件needtree, taglist等***](http://jasonding1354.github.io/2015/04/29/Developer%20Kits/%E3%80%90Vim%E3%80%91%E4%BD%BF%E7%94%A8Vundle%E7%AE%A1%E7%90%86%E9%85%8D%E7%BD%AEVim%E5%9F%BA%E6%9C%AC%E6%8F%92%E4%BB%B6/)
##1. 简介

    vim 是程序员最受欢迎的coding神器，没有之一。 合理使用插件可以做到事半功倍的效果。 
vundle 把git整合到插件管理中，用户需要做的只是去Github上找到自己想要的插件的名字，安装，更新和卸载都可有vundle来完成了。
虽然去发现一个好的插件仍然是一个上下求索的过程，但是用户已经可以从安装配置的繁琐过程解脱了。 

* [Vundle git repo](https://github.com/VundleVim/Vundle.vim) 介绍了如何安装vundle和通过vundle来安装vim插件
* [vundle.txt](https://github.com/VundleVim/Vundle.vim/blob/master/doc/vundle.txt)

##2. 安装&&使用

* 下载vundle：

```
git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim
```
* 下载完成之后，在vimrc中添加配置：

```
set nocompatible               " be iMproved
 filetype off                   " required!

 set rtp+=~/.vim/bundle/vundle/
 call vundle#rc()

 " let Vundle manage Vundle
 " required! 
 Bundle 'gmarik/vundle'

 " My Bundles here:
 #以后你想安装什么插件可以写在下面
 "
 " original repos on github 
#如果你的插件来自github，写在下方，只要作者名/项目名就行了
 Bundle 'tpope/vim-fugitive' #如这里就安装了vim-fugitive这个插件
 Bundle 'Lokaltog/vim-easymotion'
 Bundle 'rstacruz/sparkup', {'rtp': 'vim/'}
 Bundle 'tpope/vim-rails.git'
 " vim-scripts repos
#如果插件来自 vim-scripts，你直接写插件名就行了
 Bundle 'L9'
 Bundle 'FuzzyFinder'
 " non github repos
#如使用自己的git库的插件，像下面这样做
 Bundle 'git://git.wincent.com/command-t.git'
 " git repos on your local machine (ie. when working on your own plugin)
 Bundle 'file:///Users/gmarik/path/to/plugin'
 " ...

 filetype plugin indent on     " required!
#下面是 vundle的一些命令代会会用到
 "
 " Brief help
 " :BundleList          - list configured bundles
 " :BundleInstall(!)    - install(update) bundles
 " :BundleSearch(!) foo - search(or refresh cache first) for foo
 " :BundleClean(!)      - confirm(or auto-approve) removal of unused bundles
 "
 " see :h vundle for more details or wiki for FAQ
 " NOTE: comments after Bundle command are not allowed..
```  

* vim 任意打开文件， 运行 `:PluginInstall` 就会安装vimrc中Plugin配置的需要安装的插件
    * Plugin 'VundleVim/Vundle.vim' 配置vundle
    * 另外配置了其他一些vim 插件， 如L9等。








