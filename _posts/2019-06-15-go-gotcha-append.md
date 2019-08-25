---
layout: post
title: go append 使用陷阱
tags: go gotcha
---

### 问题
请大家思考下如下代码的输出结果,

```
package main

import "fmt"

func main() {
	a := []byte("aa")
	b := append(a, 'b')
	c := append(a, 'c')
	fmt.Println(string(a), len(a), cap(a), &a, &a[0])
	fmt.Println(string(b), len(b), cap(b), &b, &b[0])
	fmt.Println(string(c), len(c), cap(c), &c, &c[0])
}
```
实际输出结果为:

```
aa 2 8 &[97 97] 0xc000016090
aac 3 8 &[97 97 99] 0xc000016090
aac 3 8 &[97 97 99] 0xc000016090
```
### 原因

b,c 通过a append后， a,b,c三个slice共用底层的数组，也就是说,
a,b,c三个slice的data字段指向同一个底层数组,
所以对任意一个slice的修改， 都会影响其他的slice的值。

go中切片对应一个数据结构，如下:

```
type slice struct {
    array unsafe.Pointer
    len   int
    cap   int
}
```
### 示例
如下代码Println和Printf输出是否一致呢？
```
package main

import "fmt"

func main() {
	a := []byte("aa")
	b := append(a, 'b')
	c := append(a, 'c')
	fmt.Println(&a[0], &b[0], &c[0])
	fmt.Printf("%p %p %p\n", a, b, c)
}
```

答案是一致的， 输出如下:

```
0xc000016090 0xc000016090 0xc000016090
0xc000016090 0xc000016090 0xc000016090
```

这是因为`%p` 对应slice时输出的是slice第一个元素的地址
```
Slice:
%p	address of 0th element in base 16 notation, with leading 0x
```
详见: [fmt](https://golang.org/pkg/fmt/)



### 参考
* [深度解密Go语言之Slice](https://studygolang.com/articles/19469)
* [Why doesn’t append work every time?](https://yourbasic.org/golang/gotcha-append/)



