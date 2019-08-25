---
layout: post
title: go 基础学习
tags: go program 
---

```
本文将介绍如何定义变量、常量、Go语言内置类型及Go语言程序设计中的一些技巧。
```

## 定义变量
Go语言里面定义变量有多种方式。

使用var关键字是Go语言最基本的定义变量方式，与C语言不同的是Go语言把变量类型放在变量名后面，如下所示。

#### 定义一个变量

//定义一个名称为“variableName”，类型为"type"的变量

```
var variableName type
```

#### 定义多个变量。

//定义三个类型都是“type”的三个变量

```
var vname1, vname2,vname3 type
```

#### 定义变量并初始化值。

//初始化“variableName”的变量为“value”值，类型是“type”

```
var variableName type= value
```

#### 同时初始化多个变量。

定义三个类型都是"type"的三个变量,并且它们分别初始化相应的值
vname1为v1，vname2为v2，vname3为v3

```
var vname1, vname2, vname3 type= v1, v2, v3

```

-------
**********

*你是不是觉得上面这样的定义有点繁琐？没关系，因为Go语言的设计者也发现了，有一种写法可以让它变得简单一点。我们可以直接忽略类型声明，那么上面的代码变成如下所示。*

#### 定义三个变量，它们分别初始化相应的值

vname1为v1，vname2为v2，vname3为v3

然后Go会根据其相应值的类型来帮你初始化它们

```
var vname1, vname2, vname3 = v1, v2, v3
```

#### 你觉得上面的还是有些繁琐？好吧，让我们继续简化。

定义三个变量，它们分别初始化相应的值

vname1为v1，vname2为v2，vname3为v3

编译器会根据初始化的值自动推导出相应的类型

```
vname1, vname2, vname3 := v1, v2, v3
```

现在是不是看上去非常简洁了

`:=` 这个符号直接取代了var和type，这种形式叫做简短声明。

不过它有一个限制，***那就是`:=`只能用在函数内部；在函数外部使用则会无法编译通过，所以一般用var方式来定义全局变量。***

##### _（下画线）是个特殊的变量名，任何赋予它的值都会被丢弃。在这个例子中，我们将值35赋予b，并同时丢弃34。

_, b := 34, 35
Go语言对于已声明但未使用的变量会在编译阶段报错，比如下面的代码就会产生一个错误：声明了i但未使用。

```
package main

func main() {
    var i int
}
```

## 常量

所谓常量，也就是在程序编译阶段就确定下来的值，而程序在运行时则无法改变该值。在Go语言程序中，常量可定义为数值、布尔值或字符串等类型。


它的语法如下。

```
const constantName =value

```

//如果需要，也可以明确指定常量的类型：

```
const Pi float32 =3.1415926
```

##### 以下是一些常量声明的例子。

```
const Pi = 3.1415926
const i = 10000
const MaxThread = 10
const prefix ="astaxie_"
```

## 内置基础类型
### Boolean
在Go语言中，布尔值的类型为bool，值是true或false，**默认为false**。

##### 示例代码

```
var isActivebool  // 全局变量声明
var enabled, disabled= true, false  // 忽略类型的声明

func test() {
    var available bool  // 一般声明
    valid := false      // 简短声明
    available = true    // 赋值操作
}
```

## 数值类型

整数类型有无符号和带符号两种。Go语言同时支持int和uint，这两种类型的长度相同，但具体长度取决于不同编译器的实现。

当前的gcc和gccgo编译器在32位和64位平台上都使用32位来表示int和uint，但未来在64位平台上可能增加到64位。

Go语言里面也有直接定义好位数的类型：`rune，int8，int16，int32，int64和byte，uint8，uint16，uint32，uint64`。
 
这就是全部吗？不止，Go语言还支持复数。它的默认类型是complex128（64位实数+64位虚数）。

如果需要小一些的，也有complex64（32位实数+32位虚数）。复数的形式为RE + IMi，其中RE是实数部分，IM是虚数部分，而最后的i是虚数单位。

下面是一个使用复数的例子。

```
var c complex64 = 5+5i
//output: (5+5i)
fmt.Printf("Value is: %v", c)
```

## 字符串

Go语言中的字符串都是采用UTF-8字符集编码。

字符串是用一对***双引号***（""）或***反引号***（` `）括起来定义，它的类型是string。

//示例代码

```
var frenchHello string  // 声明变量为字符串的一般方法
var emptyString string = "" // 声明了一个字符串变量，初始化为空字符串
func test() {
    no, yes, maybe :="no", "yes", "maybe"  // 简短声明，同时声明多个变量
    japaneseHello :="Ohaiou"  // 同上
    frenchHello ="Bonjour"  // 常规赋值
}
```

#### 在Go语言中字符串是不可变的，例如，以下代码编译时会报错。

```
var s string = "hello"
s[0] = 'c'
```

#### 但如果真的想要修改怎么办？下面的代码可以实现。

```
s := "hello"
c := []byte(s)  // 将字符串 s 转换为 []byte 类型
c[0] = 'c'
s2 := string(c)  // 再转换回 string 类型
fmt.Printf("%s\n", s2)
```

#### Go语言中可以使用“+”操作符来连接两个字符串。

```
s := "hello,"
m := " world"
a := s + m
fmt.Printf("%s\n", a)
```

#### 修改字符串也可写为

```
s := "hello"
s = "c" + s[1:] // 字符串虽不能更改，但可进行切片操作
fmt.Printf("%s\n", s)
```

#### 如果要声明一个多行的字符串怎么办？可以通过***反引号***“`”来声明。

```
m := `hello

    world`
```

注意： **反引号“`”括起的字符串为Raw字符串，即字符串在代码中的形式就是打印时的形式，它没有字符转义，换行也将原样输出**

## 错误类型

Go语言内置有一个error类型，专门用来处理错误信息，Go语言的package里面还专门有一个包errors来处理错误。

```
err :=errors.New("emit macho dwarf: elf header corrupted")
if err != nil {
    fmt.Print(err)
}
```

## 一些技巧

分组声明
在Go语言中，同时声明多个常量、变量，或者导入多个包时，可采用分组的方式进行声明。

例如下面的代码。

```
import"fmt"
import "os"

const i = 100
const pi = 3.1415
const prefix ="Go_"

var i int
var pi float32
var prefix string
```


#### 可以分组写成如下形式。

```
import(
    "fmt"
    "os"
)

const(
    i = 100
    pi = 3.1415
    prefix = "Go_"
)

var(
    i int
    pi float32
    prefix string
)
```

常量的几点： 

* 除非被显式设置为其他值或iota，每个const分组的第一个常量被默认设置为它的0值.
* 第二及后续的常量被默认设置为它前面那个常量的值，如果前面那个常量的值是iota，则它也被设置为iota.

##iota枚举
Go语言里面有一个关键字iota，这个关键字用来声明enum的时候采用，它默认开始值是0，每调用一次加1。

```
const(
    x = iota // x == 0
    y = iota // y == 1
    z = iota // z == 2
    w  //常量声明省略值时，默认和之前一个值的字面相同。这里隐式地说w = iota，因此w== 3。其实上面y和z可同样不用"= iota"
)
const v = iota // 每遇到一个const关键字，iota就会重置，此时v == 0 
```

## Go语言程序设计的一些规则

Go语言之所以简洁，是因为它有一些默认的行为。

* 大写字母开头的变量是可导出的，即其他包可以读取，是公用变量；小写字母开头的不可导出，是私有变量。

* 大写字母开头的函数也是一样，相当于class中带public关键词的公有函数；小写字母开头就是有private关键词的私有函数。

### 参考
* [**go语言基础**](http://blog.csdn.net/broadview2006/article/details/8919014)
