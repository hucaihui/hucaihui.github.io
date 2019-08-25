---
layout: post
title: "leetcode 2 两数相加"
tags: leetcode mid_list
---

### 题目信息

给定两个非空链表来表示两个非负整数。位数按照逆序方式存储，它们的每个节点只存储单个数字。将两数相加返回一个新的链表。

你可以假设除了数字 0 之外，这两个数字都不会以零开头。

示例：

```
输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
输出：7 -> 0 -> 8
原因：342 + 465 = 807
```
### 解题思路

1. 每个链表存储一个数字，位数是逆序存储，从左到右分别是`个十百千万`
2. 两个指针从左到右依次遍历两个链表，需要处理链表长度不一致的问题，以及进位问题, 
3. 跳出循环的前提是没有进位并且两个链表均遍历到最后

### 第一版代码如下(go)

```go
/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func addTwoNumbers(l1 *ListNode, l2 *ListNode) *ListNode {
    start1 := l1
    start2 := l2
    res := &ListNode{}
    current := res
    addOne := 0
    for {
        if start1 != nil && start2 != nil {
            current.Val = start1.Val + start2.Val
        } else if start1 != nil {
            current.Val = start1.Val
        } else {
            current.Val = start2.Val
        }
        current.Val += addOne
        addOne = 0

        if current.Val > 9 {
            addOne = 1
            current.Val = current.Val - 10
        }
        
        // 处理start1 , start2
        if start1 != nil {
           start1 = start1.Next 
        }
        if start2 != nil {
             start2 = start2.Next
        }
       
        // 处理current ， 当start1, start2均为空时，跳出循环， 此时需要考虑最后的一次相加的进位问题
        if start1 != nil || start2 != nil {
            current.Next = &ListNode{}
            current = current.Next
        } else {
            if addOne > 0 {
                 current.Next = &ListNode{}
                 current.Next.Val = addOne
            }
            break
        }       
    }
    return res
}

```
> 第一版代码，执行效率不高， 梳理优化后代码如下：

### 第二版代码(go)

```go
/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func addTwoNumbers(l1 *ListNode, l2 *ListNode) *ListNode {
    start1 := l1
    start2 := l2
    res := &ListNode{}
    current := res
    addOne := 0
    for {
        if start1 != nil {
            current.Val += start1.Val
            start1 = start1.Next
        } 
        if start2 != nil {
            current.Val += start2.Val
            start2 = start2.Next
        } 
       
        current.Val += addOne
        addOne = 0
        if current.Val > 9 {
            addOne = 1
            current.Val = current.Val - 10
        }
        if start1 != nil || start2 != nil || addOne != 0 {
            current.Next = &ListNode{}
            current = current.Next
        } else {
            break
        }
    }
    return res
}
```

> 第二版代码，少了一些判断，执行效率稍高一些


