---
layout: post
title: leetcode 24 两两交换链表中的节点
tags: mid_list leetcode
---

### 题目信息


给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。

示例:
```
给定 1->2->3->4, 你应该返回 2->1->4->3.
```
#### 要求

1. 你的算法只能使用常数的额外空间。
2. 你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

### 解法1
不考虑如上两点要求的话，可以直接两两交换节点的Val

#### 代码(go)

```go

/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func swapPairs(head *ListNode) *ListNode {
    
     直接替换节点val
     tmp := head
     for tmp != nil && tmp.Next != nil {
         val := tmp.Val
         tmp.Val = tmp.Next.Val
         tmp.Next.Val = val
         tmp = tmp.Next.Next
     }
     return head
    
}
```

### 解法2
考虑题目中的两点要求的话，稍微复杂点
除了需要两两交换节点之外，还需要保证整个链表依次顺起来，不成环

#### 代码(go)

```go
/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func swapPairs(head *ListNode) *ListNode {
    
    // 替换节点， 交换节点之后，节点的Next也需要做调整， 以便再次能串起来整个list
    res := &ListNode{}
    res.Next = head
    tmp := res
  
    for tmp.Next != nil && tmp.Next.Next != nil {
        n1 := tmp.Next
        n2 := tmp.Next.Next
        tmp.Next = n2
        n1.Next = n2.Next
        tmp.Next.Next = n1
        tmp = tmp.Next.Next
    }
    
    return res.Next
}

```
