---
layout: post
title: vim go 开发环境配置
tags: go vim plugin
---

## 参考
* [goweb 编程-go开发工具](https://github.com/astaxie/build-web-application-with-golang/blob/master/zh/01.4.md)
* [配置vim go 开发环境](http://blog.kissdata.com/2014/06/18/vim-golang.html)


## 简介
    搭建vim 开发golang的环境,作为一个初级vimer，慢慢向高级迈进。

#### 0.vim插件管理工具 vundle
vundle 安装和使用，参考[vundle 管理vim插件](http://huyongde.github.io/2016/01/02/vim-plugin-bundler-vundle.html)

#### 0.1 go相关tools安装


通过vim中`:GoInstallBinaries` 来安装go开发相关的tools, （GoInstallBinaries 依赖mercurial需要先命令行安装mercurial, mercurial是google开发的类似于svn，git的代码托管服务）
安装完成后，tools的bin文件在$GOPATH/bin下.
我安装完后$GOPATH/bin下二进制文件如下：


```
rwxr-xr-x  1 huyongde  staff   3.6M  1  8 10:27 gotags
-rwxr-xr-x  1 huyongde  staff   5.8M  1  8 10:27 errcheck
-rwxr-xr-x  1 huyongde  staff   6.0M  1  8 10:27 golint
-rwxr-xr-x  1 huyongde  staff   6.3M  1  8 10:27 gorename
-rwxr-xr-x  1 huyongde  staff   9.1M  1  8 10:27 oracle
-rwxr-xr-x  1 huyongde  staff   6.0M  1  8 10:19 godef
-rwxr-xr-x  1 huyongde  staff   6.2M  1  8 10:19 gometalinter
-rwxr-xr-x  1 huyongde  staff    10M  1  8 10:18 gocode
-rwxr-xr-x  1 huyongde  staff   5.0M  1  8 02:48 goimports
```
## 1.vim go 插件
* [vim-godef github 详细介绍](https://github.com/dgryski/vim-godef)  此插件依赖GoInstallBinaries安装的godef, vimrc需要加的配置 `Bundle 'dgryski/vim-godef'` ,之后可以打开go文件，把光标移动到指定函数就可以使用vim normal模式下的gd命令查看对应函数的定义了。
godef显示方式配置，在vimrc中加入:

```
"""set for godef
let g:godef_split=3 """打开新窗口的时候左右split
let g:godef_same_file_in_same_window=1 """函数在同一个文件中时不需要打开新窗口
```

* [vim-gocode github 详细介绍](https://github.com/nsf/gocode) 此插件依赖GoInstallBinaries安装的gocode, vimrc需要配置`Plugin 'nsf/gocode', {'rtp': 'vim/'}`, 做go代码的补全。

* [YouCompleteMe github 详细介绍](https://github.com/Valloric/YouCompleteMe) 配合gocode，做代码补全，简直棒棒的, 需要vimrc配置` Plugin 'Valloric/YouCompleteMe'` .

* [tagbar  github 详细介绍](https://github.com/majutsushi/tagbar) 此插件和taglist类似，用来显示go中相关func method variable 等的定义， 此插件需要依赖GoInstallBinaries安装的gotags, vimrc需要配置

```
Bundle 'majutsushi/tagbar'

""""set for tagbar start
let g:tagbar_type_go = {
    \ 'ctagstype' : 'go',
    \ 'kinds'     : [
        \ 'p:package',
        \ 'i:imports:1',
        \ 'c:constants',
        \ 'v:variables',
        \ 't:types',
        \ 'n:interfaces',
        \ 'w:fields',
        \ 'e:embedded',
        \ 'm:methods',
        \ 'r:constructor',
        \ 'f:functions'
    \ ],
    \ 'sro' : '.',
    \ 'kind2scope' : {
        \ 't' : 'ctype',
        \ 'n' : 'ntype'
    \ },
    \ 'scope2kind' : {
        \ 'ctype' : 't',
        \ 'ntype' : 'n'
    \ },
    \ 'ctagsbin'  : 'gotags',
    \ 'ctagsargs' : '-sort -silent'
    \ }
```

#### 目前我的vim为go的配置如下:

```
""""""set for go start
     Plugin 'fatih/vim-go'
     Bundle 'elgris/hint'
     Plugin 'Valloric/YouCompleteMe'
     Plugin 'majutsushi/tagbar'
     Bundle 'scrooloose/nerdtree'
     Bundle 'dgryski/vim-godef'
     Plugin 'nsf/gocode', {'rtp': 'vim/'}

""""set for godef
let g:godef_split=3 """打开新窗口的时候左右split
let g:godef_same_file_in_same_window=1 """函数在同一个文件中时不需要打开新窗口

""""set for tagbar start
let g:tagbar_type_go = {
    \ 'ctagstype' : 'go',
    \ 'kinds'     : [
        \ 'p:package',
        \ 'i:imports:1',
        \ 'c:constants',
        \ 'v:variables',
        \ 't:types',
        \ 'n:interfaces',
        \ 'w:fields',
        \ 'e:embedded',
        \ 'm:methods',
        \ 'r:constructor',
        \ 'f:functions'
    \ ],
    \ 'sro' : '.',
    \ 'kind2scope' : {
        \ 't' : 'ctype',
        \ 'n' : 'ntype'
    \ },
    \ 'scope2kind' : {
        \ 'ctype' : 't',
        \ 'ntype' : 'n'
    \ },
    \ 'ctagsbin'  : 'gotags',
    \ 'ctagsargs' : '-sort -silent'
    \ }
"""set for tagbar end 

"""set for goimports
"""end goimports

```

### godef遇到的问题

##### 问题内容：

```
Error detected while processing function GodefUnderCursor[10]..Godef:
line   21:
E926: Current location list was changed
```

##### 解决方法：

> 升级syntastic 到最新代码， 设置，let g:syntastic_check_on_open = 0 为0 可以解决vim中golang代码跳转的问题


**暂时这么多，后续再补充**


