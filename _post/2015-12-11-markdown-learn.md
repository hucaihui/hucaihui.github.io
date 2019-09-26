---
layout: post
title: markdown语法再学习
tags: markdown blog 
---

# 引用
>这是一个引用
> >这是个嵌套引用
> 1. one
> 2. two
> 


# 列表

## 无序列表
### eg1
* one
* two 
* three

### eg2
- one
- two
- three
- four

### eg3
+ one
+ three
+ two
+ four

## 有序列表
### eg1
1. onexxxxxxxxxxxxx
    
    xxxxxx
    
2.   two
3.   three

### eg2
8. one
10. two
1. three
2. xxxx


## 代码块

### eg1
    //this is a code block
    //line two 
    local a = 'xxxx'
    ngx.say(a)
     
    
### eg2
    ```
    #python block
    def func1():
        return 0
    
    ```
     

## 分割线

### eg1
---

### eg2

******


## 链接
###inline link
####eg1，inline link 带title的link

[百度](www.baidu.com "百度")

#### eg2, inline link 不带title的link

[胡永德的github pages](huyongde.github.io)

### reference link
#### eg1
[百度] [1]
[1]: www.baidu.com "百度"

#### eg2
[baidu link][]
[baidu link]: www.baidu.com



## 重点emphasis/'emfəsɪs/标注

### 简介

```
Markdown treats asterisks (*)/'æstərɪsks/  and underscores (_)  /ˌʌndər'skɔːr, ˌʌndə'skɔː(r)/  as indicators/'ɪndɪkeɪtə/ of emphasis. Text wrapped with one * or _ will be wrapped with an HTML <em> tag; double *’s or _’s will be wrapped with an HTML <strong> tag. E.g., 
```
翻译过来是：

```
md认为星号asterisk 和下划线 underscore 都是重点标注的指标`indicator`.被星号和下划线包裹起来的文本会被分辨翻译成html的<em>标签和<strong>标签


```

### eg1: one indicator presents italic text
*我是个斜体* 

-this is a italic[i'tælik] text-

### eg2: double indicators present strong text

__我是个粗体__

**this is a strong text**

### eg3: 反斜线backslash转义星号antirisk和下滑线underscore， 

/* this is not emphasis /*


### eg 4 strong italic text


***this is a strong italic text***


## 代码
下面是一小段代码`$redis = new redis($redis_conf);`,用来创建和redis交互的实例


## 图片
###eg1
![this is a image](http://www.laruence.com/images/gavatar.png?orig=http://tp2.sinaimg.cn/1170999921/50/5606703689/1)


## 表格
```
You can create tables by assembling a list of words and dividing /də`vaɪd/ them
 with hyphensi /`haɪfn/  - (for the first row), and then separating each column with a pipe |:
```

通过连字符-区分行，通过管道符|区分列

### eg

第一行/列|第二行|three
--------|-------|-----|
第二行|xxxxx|xx|
第三行|yyy|yyyyy|

## 补充


```
Markdown provides backslash escapes for the following characters:

\   backslash
`   backtick
*   asterisk
_   underscore
{}  curly braces
[]  square brackets
()  parentheses
#   hash mark
+   plus sign
-   minus sign (hyphen)
.   dot
!   exclamation mark

```

