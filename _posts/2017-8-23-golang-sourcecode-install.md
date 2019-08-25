---
layout: post
title:  go 源码安装
tags: go 
---



#### 源码下载

* https://golang.org/dl/ 可以下载golang各个版本的源码
* https://github.com/golang/go 也可从github上clone源码

#### 安装

问题1： 

从源码src目录下运行`./all.bash`， 出现如下错误：

```
##### Building Go bootstrap tool.
cmd/dist
ERROR: Cannot find /home/campus/go1.4/bin/go.
Set $GOROOT_BOOTSTRAP to a working Go tree >= Go 1.4.
```

问题原因： 编译安装1.5以及以上版本的go时，需要依赖go1.4版本

解决方法： 下载1.4的源码，编译安装，并且设置GOROOT, GOBIN, PATH, 以及GOROOT_BOOTSTRAP环境变量。




```

export GOROOT="/home/campus/yongdehu/go"
export GOBIN=$GOROOT/bin
export PATH=$GOBIN:$PATH
export GOROOT_BOOTSTRAP=$GOROOT

```


问题2： 
解决问题1之后，再运行`./make.bash` 时， 提示

```
go tool dist: FAILED: not a Git repo; must put a VERSION file in $GOROOT
```
问题原因： 从github clone的go 源码目录下没有VERSION文件。

解决方法： 直接 从官网下载最新的golang源代码进行安装



安装完成之后， 运行`./go version `
输出如下：

```
go version go1.8.3 linux/amd64
```

把GOROOT和PATH更新为最新安装的目录

安装完成。
