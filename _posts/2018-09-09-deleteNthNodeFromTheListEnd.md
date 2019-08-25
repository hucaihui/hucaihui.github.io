---
layout: post
title: "leetcode 19. 删除链表的倒数第N个节点"
tags: mid_list leetcode
---


### 题目信息

给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。

示例：

```
给定一个链表: 1->2->3->4->5, 和 n = 2.

当删除了倒数第二个节点后，链表变为 1->2->3->5.
```

说明：

给定的 n 保证是有效的。

> 要求仅遍历一遍链表

### 分析
    
1. 快慢双指针实现只扫描一趟， 快指针先走n步，然后快慢指针同时走，当快指针到达尾部时，慢指针到第l-n个节点，倒数第n个节点即l-n节点的下一个节点
2. 需要处理删除头节点和尾节点的情况 

### 代码(go)

```go
/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func removeNthFromEnd(head *ListNode, n int) *ListNode {
    
    fast := head
    slow := head
    l := 0 
    for fast.Next != nil {
        if n <= 0 {
            slow = slow.Next
        }
        n --
        l ++
        fast = fast.Next 
    }
    if n == 1 { // 删除头节点
        return head.Next
    } else if n == -l {  // 删除尾节点
            slow.Next = nil
    } else {
        slow.Next = slow.Next.Next
    }
    
    return head
}
```

> 执行用时0毫秒，好吧， 看来用go提交代码的比较少，https://leetcode-cn.com/submissions/detail/6872966/
