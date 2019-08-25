---
layout: post
title: go语言 array, slice , map 简单介绍
tags: program go 
---


[***参考***](http://www.cnblogs.com/yjf512/archive/2012/06/14/2549929.html)

### 1. 数组 array

array是固定长度的数组，这个和C语言中的数组是一样的，使用前必须确定数组长度。

但是和C中的数组相比，又是有一些不同的：

1. Go中的数组是值传递类型，换句话说，如果你将一个数组赋值给另外一个数组，那么，实际上就是将整个数组拷贝一份。

2. 如果Go中的数组作为函数的参数，那么实际传递的参数是一份数组的拷贝，而不是数组的指针, 是值传递而不是引用传递。
    这个和C要区分开。因此，在Go中如果将数组作为函数的参数传递的话，那效率就肯定没有传递指针高了。好坑的感觉!

3. array的长度也是Type的一部分，这样就说明[10]int和[20]int是不一样的。

 

##### array的结构如下:

len|int|int|
----| ---| ---|
2| 1|2|

**len表示数组的长度，后面是存储的实际数据**

### 2. 切片 slice

可以参考本站另一个博文  [*slice 学习*](http://huyongde.github.io/2015/12/25/go-slice.html).

这里再介绍两点：

#### 2.1 slice长度可变

定义完一个slice变量之后，不需要为它的容量而担心，你随时可以往slice里面加数据

比如：

```
v:=[]int{}
v=append(v,  10)
//这里附带说一下，slice和array的写法很容易混
v:=[2]string{"arr", "arr"} //这个是array
m:=[]string{"s","s"} //这个是slice
```

要记住：array 定长slice不定长,array 定长slice不定长,array 定长slice不定长....  ，重要的事情说多变。

#### 2.2slice是引用传递, 是指针

指针比值可就小多了，因此，我们将slice作为函数参数传递比将array作为函数参数传递会更有性能。
slice是一个指针，它指向的是一个array结构，它有两个基本函数len和cap。

slice是一个带有point（指向数组的指针），Len（数组中实际有值的个数），Cap（数组的容量）

append函数就理解为往slice中加入一个值，如果未达到容量（len<cap）那么就直接往数组中加值，
如果达到容量（len = cap）那么就新增一倍的新元素空间，再赋值。

### 3. map 结构

map结构也经常常用，它和php中的`array（）`几乎一模一样，是一个`key-value`的hash结构。

key可以是除了func类型，array,slice,map类型之外的类型。

使用例子如下:

```
fmt.Println("learn map")
m := map[string]string{}
var m1 = map[int]string{}
m["key1"] = "value1"
fmt.Println(m)
m1[1] = "int key , string value"
fmt.Println(m1)
var m2 = map[int]int{}
m2[1] = 2
fmt.Println(m2)
```
输出结果:

```
learn map
map[key1:value1]
map[1:int key , string value]
map[1:2]
```

