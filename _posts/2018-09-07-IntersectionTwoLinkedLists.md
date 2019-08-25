---
layout: post
title:  "leetcode 160 两个链表相交，求交点"
tags: leetcode list 
---

#### 题目信息
编写一个程序，找到两个单链表相交的起始节点。

例如，下面的两个链表：

```
A:          a1 → a2
                   ↘
                     c1 → c2 → c3
                   ↗            
B:     b1 → b2 → b3

```
在节点 c1 开始相交。

 

注意：

* 如果两个链表没有交点，返回 null.
* 在返回结果后，两个链表仍须保持原有的结构。
* 可假定整个链表结构中没有循环。
* 程序尽量满足 O(n) 时间复杂度，且仅用 O(1) 内存。

#### 解法1
题目拆解为2步
1. 判断是否有交点
2. 有交点的话，计算出来长度差m，较长链表先走m, 然后一起走，第一个相同的节点即是交点

#### 代码(c++)

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int l1 = 0;
        int l2 = 0;
        ListNode *tmp1 = headA;
        ListNode *tmp2 = headB;
        while(tmp1 != NULL) {
            l1++;
            tmp1 = tmp1->next;
        }
        while(tmp2 !=NULL) {
            l2++;
            tmp2= tmp2->next;
        }
        //尾节点不一样，肯定不想交
        if (tmp1 != tmp2) {
            return NULL;
        }
        tmp1 = headA;
        tmp2 = headB;
        if (l1 > l2) {
            int n = l1-l2;
            while(n--) {
                tmp1=tmp1->next;
            }         
        } else {
            int n = l2-l1;
            while(n--) {
                tmp2=tmp2->next;
            }
        }
        while(tmp1 != NULL) {
            if (tmp1 == tmp2) return tmp1;
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
        }
        return NULL;
    }
};

```
#### 解法2
分四种情况来解析解法2(先看下代码，再来看分析)

1. A B链表长度相同，不想交，直接遍历到最后，p1==p2==NULL 返回NULL
2. A B链表长度相同，相交, 直接遍历到p1==p2!=NULL 返回
3. A B链表长度不同,长度分别为l1, l2，不想交，第一次遍历，比如A链表长，则B链表p2先==NULL, 
p2跳到A链表头开始遍历，此时p1,p2均在遍历A链表，再遍历l1-l2次, p1==NULL, p1跳到B链表头，
此时p1, p2 后面的链表长度相等，重回1，2两个case.

#### 代码(c++)

```cpp
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *p1 = headA;
        ListNode *p2 = headB;
        while(p1!=p2){
            p1 = (p1==NULL ? headB : p1->next);
            p2 = (p2==NULL ? headA : p2->next);
        }
        return p1;
    }
};
```
