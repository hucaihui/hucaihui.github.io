---
layout: post
title: "VIM 配置(一)--基础篇"
tags: vim php
---

### 0. 简介

vim配置弄过很多，关于编码的，缩进的，taglist, nerdtree， vundle插件管理器等的配置。假期有空重新整理学习学习

准备从如下几个方面去整理：

1. vim基础配置学习，如编码，缩进 
2. vim各项配置命令学习,如map, aotocmd, command等等
1. [vundle 安装使用](http://huyongde.github.io/2016/01/02/vim-plugin-bundler-vundle.html)
2. 自动代码格式化
3. 各语言代码语法自动检查
4. 代码补全


> 本篇主要介绍下vim相关的基础配置

### 1. 相关配置
####1.1 设置保存vimrc自动生效

* `autocmd! bufwritepost .vimrc source ~/.vimrc` 设置之后，
* 当你修改~./vimrc并执行:w保存时可能会报 `E174: Command already exists: add ! to replace it`

superuser有关于这个问题的解决方案，[解决source ~/.vimrc E174](http://superuser.com/questions/830132/sourcing-the-vimrc-gives-e174-error)
主要就是你需要在command后面加上!来做vim的相关配置。

**:help E174**的结果是

```
:com[mand][!] [{attr}...] {cmd} {rep}
定义一个用户命令。命令的名字是 {cmd}，而替换的文本是
{rep}。该命令的属性 (参考下面) 是 {attr}。如果该命令已
存在，报错，除非已经指定了一个 !，这种情况下命令被重定
义。
```

> 设置完成上面两步之后，就可以在修改了~/.vimrc并保存的时候，自动执行`source ~/.vimrc` 来使配置生效了。

#### 1.2 vim配置help的中文文档

* 首先下载vimdoc,[下载链接](http://jaist.dl.sourceforge.net/project/vimcdoc/vimcdoc/vimcdoc-1.9.0.tar.gz) ,vimdoc官网[主页](http://vimcdoc.sourceforge.net/), 
下载后直接把压缩包放入`~/.vim/doc` 目录，不存在的话进行创建`mkdir -p ~/.vim/doc`
* 执行`:helptags ~/.vim/doc`
* 在`~/.vimrc ` 中设置 `set helplang=cn`

> 上面三步一步不少的执行完后，就可以愉快的看到中文版的vim help了， 可以help autocmd验证下

#### 1.3 编码配置

vim 中有四个关于编码的选项，分别是encoding(enc), termencoding(tenc), fileencoding(fenc), fileencodings(fencs). 下面分别介绍这四种编码：

* encoding(enc) : encoding 是vim内部使用的字符编码方式，vim内部所有的buffer,寄存器， 脚本中的字符串都是使用此编码。 
vim工作时，遇到编码和内部编码不一致时， 会把编码转化为内部编码，无法转化的部分就会丢失。
* termencoding(tenc) : termencoding 是vim用于屏幕显示的编码, 在显示的时候vim会把内部编码转化为屏幕编码，再用于输出。
无法从内部编码转化为屏幕编码的字符，显示的时候将会变成问号。 若termencoding不设置，则屏幕编码直接使用encoding的设置。
* fileencoding(fenc) : 当vim从磁盘上读取文件的时候，会对文件的编码进行探测。如果文件的编码方式和 vim 的内部编码方式不同，vim 就会对编码进行转换。
转换完毕后，Vim 会将 fileencoding 选项设置为文件的编码。当 Vim 存盘的时候，如果 encoding 和 fileencoding 不一样，Vim 就会进行编码转换。
因此，通过打开文件后设置 fileencoding，我们可以将文件由一种编码转换为另一种编码。但是，由前面的介绍可以看出，fileencoding 是在打开文件的时候 ，
由 Vim 进行探测后自动设置的。因此，如果出现乱码，我们无法通过在打开文件后重新设置 fileencoding 来纠正乱码。 
* fileencodings(fencs) :  编码的自动识别是通过设置 fileencodings 实现的，注意是复数形式。
fileencodings 是一个用逗号分隔的列表，列表中的每一项是一种编码的名称。当我们打开文件的时候，
VIM 按顺序使用 fileencodings 中的编码进行尝试解码，如果成功的话，就使用该编码方式进行解码，
并将 fileencoding 设置为这个值，如果失败的话，就继续试验下一个编码。 因此，我们在设置 fileencodings 的时候，
一定要把要求严格的、当文件不是这个编码的时候更容易出现解码失败的编码方式放在前面，把宽松的编码方式放在后面。

参考学习

* [vim解决中文乱码问题](http://www.vimer.cn/2009/10/87.html) 
* [vim文件编码识别设置](http://edyfox.codecarver.org/html/vim_fileencodings_detection.html)
* [mbbill/fencview](https://github.com/mbbill/fencview) 文件编码自动检测插件


#### 1.4 缩进配置

参考学习

* [vim缩进配置](http://linux-wiki.cn/wiki/zh-hans/Vim%E4%BB%A3%E7%A0%81%E7%BC%A9%E8%BF%9B%E8%AE%BE%E7%BD%AE)


### 补充
#### 设置php文件保存的时候自动进行php -l的php语法检查
* 第一种方法，不借助插件的配置`autocmd! BufWritePost *.php :!php -l %` 
是通过php -l来执行，做了一次自动命令的来实现的,当写php文件的时候，自动执行`:!php -l %`
* [vim 各语言的语法检查插件](https://github.com/scrooloose/syntastic)  [相关wiki](https://github.com/scrooloose/syntastic/wiki/Syntax-Checkers) 
* phplint 进行` Bundle 'nrocco/vim-phplint'` 和 `autocmd! BufWritePost *.php :phplint` 两个配置，第一个配置是安装phplint插件，第二个配置是在文件写入时自动执行phplint插件
[Phplint github](https://github.com/nrocco/vim-phplint)

> 最终我选择的Phplint，显示的结果更友好些。

### php文件保存的时候自动进行代码格式化

* 不借助插件来实现 `autocmd! BufWrite *.php :exec 'normal ggVG==='`
* vim各类代码格式化的插件[Chiel92/vim-autoformat](https://github.com/Chiel92/vim-autoformat)


> 楼主目前用的非插件的antocmd配置方式， 后续研究下插件方式的

##### 接下来准备研究下vim的map类命令[vim的几种模式和按键映射](http://haoxiang.org/2011/09/vim-modes-and-mappin/)
##### 学习下[vim插件推荐](http://edyfox.codecarver.org/html/vimplugins.html) 文章中推荐的插件
##### 楼主现在用的[vim配置](https://github.com/huyongde/my.vimrc)
