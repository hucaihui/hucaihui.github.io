---
title: php output buffering 配置和相关函数学习
layout: post
tags: ob php buffering
---

### 简介
`output buffering` 简称ob, 是输出缓冲区， 通过php配置以及output control （输出控制函数）来控制php的输出， 输出控制函数不会作用于setcookie以及header两个输出标头的函数， 只
会作用于类似与echo类的函数.

### php 缓冲区分类

1. 用户缓冲区 通过ob_xxx函数来操作， ob_start创建一个用户缓冲区
2. php默认缓冲区
3. sapi缓冲区

### output buffering 相关的php 配置
* output_buffering boolean/integer 该选项设置为 On 时，将在所有的脚本中使用输出控制。如果要限制输出缓冲区的最大值，可将该选项设定为指定的最大字节数（例如 output_buffering=4096）。从PHP 4.3.5 版开始，该选项在 PHP-CLI 下总是为 Off。 设置为On时，相当于每次执行完echo类的输出后，自动执行`ob_flush()`函数.

* implicit_flush boolean 默认为 FALSE。如将该选项改为 TRUE，PHP 将使输出层，在每段信息块输出后，自动刷新。这等同于在每次使用 print、echo 等函数或每个 HTML 块之后，调用 PHP 中的 flush() 函数。 不在web环境中使用 PHP 时，打开这个选项对程序执行的性能有严重的影响，通常只推荐在调试时使用。在 CLI SAPI 的执行模式下，该标记默认为 TRUE。

* output_handler string 该选项可将脚本所有的输出，重定向到一个函数。例如，将 output_handler 设置为 mb_output_handler() 时，字符的编码将被修改为指定的编码。设置的任何处理函数，将自动的处理输出缓冲。

**不能同时使用 mb_output_handler() 和 ob_iconv_handler()，也不能同时使用 ob_gzhandler() 和 zlib.output_compression**
**只有内置函数可以使用此指令。对于用户定义的函数，使用 ob_start()**

### output buffering 相关的函数

* flush — 刷新输出缓冲
* ob_clean — 清空（擦掉）输出缓冲区
* ob_end_clean — 清空（擦除）缓冲区并关闭输出缓冲
* ob_end_flush — 冲刷出（送出）输出缓冲区内容并关闭缓冲
* ob_flush — 冲刷出（送出）输出缓冲区中的内容
* ob_get_clean — 得到当前缓冲区的内容并删除当前输出缓。
* ob_get_contents — 返回输出缓冲区的内容
* ob_get_flush — 刷出（送出）缓冲区内容，以字符串形式返回内容，并关闭输出缓冲区。
* ob_get_length — 返回输出缓冲区内容的长度
* ob_get_level — 返回输出缓冲机制的嵌套级别
* ob_get_status — 得到所有输出缓冲区的状态
* ob_gzhandler — 在ob_start中使用的用来压缩输出缓冲区中内容的回调函数。ob_start callback function to gzip output buffer
* ob_implicit_flush — 打开/关闭绝对刷送
* ob_list_handlers — 列出所有使用中的输出处理程序。
* ob_start — 打开输出控制缓冲
* output_add_rewrite_var — 添加URL重写器的值（Add URL rewriter values）
* output_reset_rewrite_vars — 重设URL重写器的值（Reset URL rewriter values）


### 实例

```
for($i=0; $i<10; $i++) {
    echo "$i sleeping .... <br>";
    echo "<script type='text/javascript'> window.scrollTo(0, document.body.scrollHeight);</script>"
    ob_flush();
    flush();
    sleep(1);

}
echo "<script type='text/javascript'> window.scrollTo(0, document.body.scrollHeight);</script>"

```

如上例子将会 每秒输出一个sleeping，挨个输出，而不是一次性输出, 此处ob_flush() 是把php的缓冲区内容送出到sapi缓冲区， flush()是把SAPI的缓冲区内容送出
两个函数共同实现了把echo的信息实时输出到浏览器，而不是一次性输出所有的echo信息。 js是用来控制浏览器滚动条一直在浏览器最底端， 也就是一直显示最新输出的内容.


### 参考
* [深入理解php输出缓存](http://gywbd.github.io/posts/2015/1/php-output-buffer-in-deep.html)
* [输出控制函数](http://php.net/manual/zh/ref.outcontrol.php)
* [输出控制运行时配置](http://php.net/manual/zh/outcontrol.configuration.php)
