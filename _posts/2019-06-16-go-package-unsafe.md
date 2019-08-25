---
title: go unsafe 注释翻译和实践
layout: post
tags: go 翻译
---

### 背景
翻译go unsafe包中的部分注释，学习unsafe包的使用

https://golang.org/src/unsafe/unsafe.go


### 注释翻译

```
// Copyright 2009 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

/*
	Package unsafe contains operations that step around the type safety of Go programs.

	Packages that import unsafe may be non-portable and are not protected by the
	Go 1 compatibility guidelines.

*/
unsafe 包包含了可以绕开go语言类型安全的一些操作。
引用了unsafe包的包可能是不可移植的、并且不受go兼容性指南的保护。

package unsafe


// ArbitraryType is here for the purposes of documentation only and is not actually
// part of the unsafe package. It represents the type of an arbitrary Go expression.
这里的ArbitraryType 仅仅是为了文档目的，实际上它不是unsafe包的一部分。它可以表示任意go表达式的类型

type ArbitraryType int

// Pointer represents a pointer to an arbitrary type. There are four special operations
// available for type Pointer that are not available for other types:
Pointer 表示指向任意类型的指针。Pointer 有四种特殊操作，这四种特殊操作不适用于其他类型。
//	- A pointer value of any type can be converted to a Pointer.
//	- A Pointer can be converted to a pointer value of any type.
//	- A uintptr can be converted to a Pointer.
//	- A Pointer can be converted to a uintptr.
- 任何类型的指针都可以被转换为Pointer
- Pointer可以被转换为任何类型的指针
- uintptr可以被转换为Pointer
- Pointer可以被转换为uintptr

// Pointer therefore allows a program to defeat the type system and read and write
// arbitrary memory. It should be used with extreme care.
因此，Pointer允许程序打破类型系统并读写任意内存。应该特别小心的使用Pointer

//
// The following patterns involving Pointer are valid.

// Code not using these patterns is likely to be invalid today
// or to become invalid in the future.
// Even the valid patterns below come with important caveats.
以下涉及Pointer的模式是有效的
未使用这些模式的代码现在是无效的，或者未来会变为无效。
即使下面这些有效的模式也有重要的注意事项。

//
// Running "go vet" can help find uses of Pointer that do not conform to these patterns,
// but silence from "go vet" is not a guarantee that the code is valid.
运行go vet可以帮助找到不符合这些模式的Pointer的用法，但是go vet 的沉默并不能保证代码是有效的。
//
// (1) Conversion of a *T1 to Pointer to *T2.
(1) *T1 转换为Pointer至*T2
//
// Provided that T2 is no larger than T1 and that the two share an equivalent
// memory layout, this conversion allows reinterpreting data of one type as
// data of another type. An example is the implementation of
// math.Float64bits:
//
//	func Float64bits(f float64) uint64 {
//		return *(*uint64)(unsafe.Pointer(&f))
//	}
//
// (2) Conversion of a Pointer to a uintptr (but not back to Pointer).
(2) Pointer转换为uintptr, 但不转换回Pointer
//
// Converting a Pointer to a uintptr produces the memory address of the value
// pointed at, as an integer. The usual use for such a uintptr is to print it.
将Pointer转换为uintptr会产生指针所指向值得内存地址，作为整数。
uintptr的通常用处是打印它。
//
// Conversion of a uintptr back to Pointer is not valid in general.
通常情况下，uintptr转换回Pointer是无效的。
//
// A uintptr is an integer, not a reference.
uintptr是个整数，不是引用。
// Converting a Pointer to a uintptr creates an integer value
// with no pointer semantics.
把Pointer转换为uintptr会创建一个无指针语义的整数。
// Even if a uintptr holds the address of some object,
// the garbage collector will not update that uintptr's value
// if the object moves, nor will that uintptr keep the object
// from being reclaimed.
即使uintptr保存了某个对象的地址，如果对象移动了，垃圾回收器也不会更新
uintptr的值，uintptr也不会保持该对象不被回收。
//
// The remaining patterns enumerate the only valid conversions
// from uintptr to Pointer.
剩下的模式枚举了uintptr到Pointer的有效转换。

//
// (3) Conversion of a Pointer to a uintptr and back, with arithmetic.
(3) Pointer 转换为uintptr，计算之后再转换回来
//
// If p points into an allocated object, it can be advanced through the object
// by conversion to uintptr, addition of an offset, and conversion back to Pointer.
如果p是指向一个已分配的对象，p可以被推进访问这个对象，通过转换为uintptr，增加个偏移量后再转换为Pointer
//
//	p = unsafe.Pointer(uintptr(p) + offset)
//
// The most common use of this pattern is to access fields in a struct
// or elements of an array:
此模式最常见的用途是访问结构体中的某个字段或者数组的元素:
//
//	// equivalent to f := unsafe.Pointer(&s.f)
//	f := unsafe.Pointer(uintptr(unsafe.Pointer(&s)) + unsafe.Offsetof(s.f))
//
//	// equivalent to e := unsafe.Pointer(&x[i])
//	e := unsafe.Pointer(uintptr(unsafe.Pointer(&x[0])) + i*unsafe.Sizeof(x[0]))
//
// It is valid both to add and to subtract offsets from a pointer in this way.
// It is also valid to use &^ to round pointers, usually for alignment.
// In all cases, the result must continue to point into the original allocated object.
通过这种方式为指针增加或者减去偏移量都是有效的。
使用&^来四舍五入指针也是有效的，此操作通常用来做对齐。
在所有情况下，结果必须继续指向原始分配的对象。

//
// Unlike in C, it is not valid to advance a pointer just beyond the end of
// its original allocation:
//
//	// INVALID: end points outside allocated space.
//	var s thing
//	end = unsafe.Pointer(uintptr(unsafe.Pointer(&s)) + unsafe.Sizeof(s))
//
//	// INVALID: end points outside allocated space.
//	b := make([]byte, n)
//	end = unsafe.Pointer(uintptr(unsafe.Pointer(&b[0])) + uintptr(n))
//
// Note that both conversions must appear in the same expression, with only
// the intervening arithmetic between them:
请注意，两个转换必须出现在同一个表达式中，它们之间仅有介入的计算
//
//	// INVALID: uintptr cannot be stored in variable
//	// before conversion back to Pointer.
//	u := uintptr(p)
//	p = unsafe.Pointer(u + offset)
//
// (4) Conversion of a Pointer to a uintptr when calling syscall.Syscall.
调用syscall.Syscall时Pointer转换为uintptr
//
// The Syscall functions in package syscall pass their uintptr arguments directly
// to the operating system, which then may, depending on the details of the call,
// reinterpret some of them as pointers.
// That is, the system call implementation is implicitly converting certain arguments
// back from uintptr to pointer.
//
// If a pointer argument must be converted to uintptr for use as an argument,
// that conversion must appear in the call expression itself:
//
//	syscall.Syscall(SYS_READ, uintptr(fd), uintptr(unsafe.Pointer(p)), uintptr(n))
//
// The compiler handles a Pointer converted to a uintptr in the argument list of
// a call to a function implemented in assembly by arranging that the referenced
// allocated object, if any, is retained and not moved until the call completes,
// even though from the types alone it would appear that the object is no longer
// needed during the call.
//
// For the compiler to recognize this pattern,
// the conversion must appear in the argument list:
//
//	// INVALID: uintptr cannot be stored in variable
//	// before implicit conversion back to Pointer during system call.
//	u := uintptr(unsafe.Pointer(p))
//	syscall.Syscall(SYS_READ, uintptr(fd), u, uintptr(n))
//
// (5) Conversion of the result of reflect.Value.Pointer or reflect.Value.UnsafeAddr
// from uintptr to Pointer.
reflect.Value.Pointer和reflect.Value.UnsafeAddr的返回结果从uintptr转换为Pointer
//
// Package reflect's Value methods named Pointer and UnsafeAddr return type uintptr
// instead of unsafe.Pointer to keep callers from changing the result to an arbitrary
// type without first importing "unsafe". However, this means that the result is
// fragile and must be converted to Pointer immediately after making the call,
// in the same expression:
//
//	p := (*int)(unsafe.Pointer(reflect.ValueOf(new(int)).Pointer()))
//
// As in the cases above, it is invalid to store the result before the conversion:
//
//	// INVALID: uintptr cannot be stored in variable
//	// before conversion back to Pointer.
//	u := reflect.ValueOf(new(int)).Pointer()
//	p := (*int)(unsafe.Pointer(u))
//
// (6) Conversion of a reflect.SliceHeader or reflect.StringHeader Data field to or from Pointer.
reflect.SliceHeader或者reflect.StringHeader的Data字段转换到Pointer或者从Pointer转换
//
// As in the previous case, the reflect data structures SliceHeader and StringHeader
// declare the field Data as a uintptr to keep callers from changing the result to
// an arbitrary type without first importing "unsafe". However, this means that
// SliceHeader and StringHeader are only valid when interpreting the content
// of an actual slice or string value.
//
//	var s string
//	hdr := (*reflect.StringHeader)(unsafe.Pointer(&s)) // case 1
//	hdr.Data = uintptr(unsafe.Pointer(p))              // case 6 (this case)
//	hdr.Len = n
//
// In this usage hdr.Data is really an alternate way to refer to the underlying
// pointer in the slice header, not a uintptr variable itself.
//
// In general, reflect.SliceHeader and reflect.StringHeader should be used
// only as *reflect.SliceHeader and *reflect.StringHeader pointing at actual
// slices or strings, never as plain structs.
// A program should not declare or allocate variables of these struct types.
//
//	// INVALID: a directly-declared header will not hold Data as a reference.
//	var hdr reflect.StringHeader
//	hdr.Data = uintptr(unsafe.Pointer(p))
//	hdr.Len = n
//	s := *(*string)(unsafe.Pointer(&hdr)) // p possibly already lost
//
type Pointer *ArbitraryType
go的任意类型 Pointer

// Sizeof takes an expression x of any type and returns the size in bytes
// of a hypothetical variable v as if v was declared via var v = x.
// The size does not include any memory possibly referenced by x.
// For instance, if x is a slice, Sizeof returns the size of the slice
// descriptor, not the size of the memory referenced by the slice.
Sizeof 返回任意表达式x的大小，单位字节, 大小不包括表达式所指向的内存大小，
如果x是个切片，Sizeof返回的是切片描述符的大小，不是切片所指向内存的大小。

func Sizeof(x ArbitraryType) uintptr

// Offsetof returns the offset within the struct of the field represented by x,
// which must be of the form structValue.field. In other words, it returns the
// number of bytes between the start of the struct and the start of the field.
返回结构体内某个字段的偏移量，参数x必须是structValue.field这中格式。也就是说，
Offsetof返回了结构体开始位置和某个字段开始位置的偏移量， 单位字节
func Offsetof(x ArbitraryType) uintptr

// Alignof takes an expression x of any type and returns the required alignment
// of a hypothetical variable v as if v was declared via var v = x.
// It is the largest value m such that the address of v is always zero mod m.
// It is the same as the value returned by reflect.TypeOf(x).Align().
// As a special case, if a variable s is of struct type and f is a field
// within that struct, then Alignof(s.f) will return the required alignment
// of a field of that type within a struct. This case is the same as the
// value returned by reflect.TypeOf(s.f).FieldAlign().
返回表达式x需要的对齐大小，单位字节
func Alignof(x ArbitraryType) uintptr
```

> 如上是基于源码中的注释进行的部分理解和翻译

### 示例
Sizeof, Offsetof, Alignof 示例
> 64位系统，注释部分为对应语句的输出结果

```
type X struct {
        a bool
        b int16
        c []int
}
x := X{}
fmt.Println(unsafe.Sizeof(x), unsafe.Alignof(x))
// 32 8
fmt.Println(unsafe.Sizeof(x.a), unsafe.Alignof(x.a), unsafe.Offsetof(x.a))
//  1, 1, 0
fmt.Println(unsafe.Sizeof(x.b), unsafe.Alignof(x.b), unsafe.Offsetof(x.b))
// 2, 2, 2
fmt.Println(unsafe.Sizeof(x.c), unsafe.Alignof(x.c), unsafe.Offsetof(x.c))
// 24, 8, 8
```


### 说明
水平有限，翻译仅供参考，有问题欢迎交流。

### 参考
* [unsafe source code ](https://golang.org/src/unsafe/unsafe.go)
* [go 语言圣经](https://www.kancloud.cn/hartnett/gopl-zh/126066)
