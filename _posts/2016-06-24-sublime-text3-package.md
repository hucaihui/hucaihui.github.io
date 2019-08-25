---
layout: post
title: sublime text 3  扩展包安装以及遇到的问题
tags: sublime package
---

### 简介
最近在用sublime text3, 通过package control 可以安装的扩展包真的太多了，很强大
但是在安装的时候遇到了一些问题

### VCS gutter

* 具体介绍和安装可以去[git官网](https://github.com/bradsokol/VcsGutter) , 
	这个sublime 3 的插件主要是来判断某一行代码是否被修改删除或者添加过， 支持的版本控制系统(vcs: version control system )有git, svn, hg等.
* VCS Gutter对于git来说就相当于git Gutter, 安装VCS Gutter之后，就可以remove 掉 Git Gutter了.
* 安装完成之后，需要修改用户配置文件，修改后的VCS Gutter 用户配置文件如下:

```

{
	"vcs_paths": {
	        "diff": "C:\\Users\\Administrator\\.babun\\cygwin\\bin\\diff.exe",
	        "git": "C:\\Users\\Administrator\\.babun\\cygwin\\bin\\git.exe",
	        "hg": "",
	        "svn": "C:\\Program Files\\TortoiseSVN\\bin\\svn.exe",
	},
	 "live_mode": false,
}

```

> 主要是配置各个版本控制系统的可执行命令的路径，以及diff路径，如上是我的配置文件，windows系统上面安装了babun(windows系统上的linux shell软件)， 可执行文件都配置的是babun相关的路径。

### Sublime Linter 

* 具体的安装参考[官网](http://www.sublimelinter.com/en/latest/installation.html)
* sublime linter 是sublime 用来做代码检查用的，可以发现代码存在的语法等的问题， **安装了Sublime Linter之后，需要为每一种语言单独安装语言特有的linter **
比如php语言需要安装[SublimeLinter-PHP](https://github.com/SublimeLinter/SublimeLinter-php), SublimeLinter-PHP这个插件是通过` php -l `来实现语法检查的。
* 安装完sublime linter 以及sublimeLinter-php之后，出现php语法错误后，sublime编辑器会给如下提示:
![错误提示](/image/sublimeLinter.png)

>其中，右上方提示了具体的错误信息，左下方红点表示错误发生的位置， 红点上方的绿色的加好是Vcs Gutter显示的代码基于当前版本所做的修改。


* sublime linter 安装完成之后，可以再安装，sublimeLinter-phpcs以及sublimeLinter-phpmd, 分别是php的code sniffer以及mess detector
    * phpcs 根据PHP代码标准(PSR: PHP Standards Recommendations )来检查代码是否符合标准, 详细的各种php代码标准参考[psr](http://www.php-fig.org/psr/).
    * phpmd 是根据某些规则来检查你的代码是否符合规则，比如说函数和变量的命名是否合理，if else 使用是否合理，定义的变量是否使用等的规则，详情请参考[phpmd.org](https://phpmd.org/rules/index.html).

* package control 安装了sublimeLinter-phpcs 以及sublimeLinter-phpmd之后，需要用pear来安装它们所以依赖的php相关的可执行文件，phpcs以及phpmd， 安装命令如下:
    * 安装phpmd: 
    
    ```
    pear channel-discover pear.phpmd.org
    pear channel-discover pear.pdepend.org
    pear install --alldeps phpmd/PHP_PMD
    ```
    
    * 安装phpcs： `pear install --alldeps PHP_CodeSniffer`

* phpcs和phpmd搞定之后，好多不符合规范的提示，如下图，闹心啊!!!
![](/image/phpcs-phpmd.png)

> 太多格式不符合要求了。闹心啊闹心，最后把phpcs直接禁止了，只留了phpmd的一些规则检查，相关的linter配置如下（是sublimeLinter的配置，phpcs和phpmd貌似没有单独的配置）:

```
  "linters": {
            "php": {
                "@disable": false,
                "args": [],
                "excludes": []
            },
            "phpcs": {
                "@disable": true,
                "args": [],
                "cmd": "C:\\pear\\phpcs.bat",
                "excludes": [],
                "standard": "PSR1"
            },
            "phpmd": {
                "@disable": false,
                "args": [],
                "cmd": "C:\\pear\\phpmd.bat",
                "excludes": [],
                "rulesets": "naming,unusedcode"
            }
        },
```

### SublimeCodeIntel

* 此插件是sublime 用来做代码补全的, codeIntel 全称code intelligence 代码智能的意思 
* 安装参考[SublimeCodeIntel](https://github.com/SublimeCodeIntel/SublimeCodeIntel), 安装完成之后，做了如下配置：

```
{
    "PHP": {
        "php": "/cygdrive/c/wamp64/bin/php/php7.0.0/php",
        "phpExtraPaths": [],
        "phpConfigFile": "/cygdrive/c/wamp64/bin/php/php7.0.0/php.ini"
    },
    "JavaScript": {
        "javascriptExtraPaths": []
    },
    "Python": {
        "python": "C:\\Users\\Administrator\\.babun\\cygwin\\bin\\python",
        "pythonExtraPaths": []
    },
}

``` 


### 问题
1. 安装完成SublimeCodeIntel后，使用时不成功，通过`C+~` 调出来命名窗口，发现 **OSError: [WinError 6] 句柄无效** 的错误。 这个问题google了下，stackoverflow上面有个相关的解决方案 [链接](http://stackoverflow.com/questions/3028786/how-can-i-fix-error-6-the-handle-is-invalid-with-pyserial)，说是python安装的版本不对.
我的系统是win7 64, 需要安装64位的python, 下载了[安装包](https://www.python.org/ftp/python/2.7.12/python-2.7.12rc1.amd64.msi)
重新安装后，重新设置了环境变量PATH， 再次进行js编程时就可以自动提示并且补全了。
2. 安装了多个插件之后，sublime经常性卡顿，尝试设置了下gitgutter的user配置， 添加配置

```
{
    "non_blocking" : "true",
    "live_mode" : "false"
}
```

修改之后稍微有些改观，可能还有其他的插件导致这个问题。

> 后续有问题继续更新

### 配置前端开发的扩展包

#### [参考](http://www.cnblogs.com/hykun/p/sublimeText3.html)

上篇博文中包括了emmet,SublimeCodeIntel, SideBar等的扩展插件。
