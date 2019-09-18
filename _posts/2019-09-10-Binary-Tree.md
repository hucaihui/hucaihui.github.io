---
title: 二叉树
tag: binary-tree c++ 
layout: post
---


## 二叉树的性质
性质1：在二叉树的第$i$层上至多有$2^{i-1}$个结点($i>=1$)；

性质2：深度为$k$的二叉树至多有$2^{k}-1$个结点($k>=1$)；

性质3：对任何一棵二叉树T，如果其终端结点数（叶子结点）为$n_0$，度为2的结点数为$n_2$，则$n_0=n_2+1$；

性质4：具有$n$个结点的完全二叉树的深度为$\lfloor{log_2n}\rfloor+1$；

性质5：具有$n$个结点的完全二叉树按层序编号，对任一结点$i$:
1、如果$i=1$，则结点$i$是二叉树的概，无双亲；
2、如果$i>1$，则其双亲是结点$\lfloor{i/2}\rfloor$；
3，对结点$i$，满足$2i  \le n |2i+1 \le n$，$i$的左孩子是$2i$，右孩子是$2i+1$。

## 二叉树的遍历 
### 前序遍历
### 中序遍历 
### 后序遍历
### 层序遍历

## 重建二叉树
### 前序+中序$or$中序+后序遍历二叉树
`注`：已经前序和后序遍历，不能确定一棵二叉树
### 层序遍历复原完全二叉树
### 符号表示法复原二叉树


<head>
    <script src="https://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML" type="text/javascript"></script>
    <script type="text/x-mathjax-config">
        MathJax.Hub.Config({
            tex2jax: {
            skipTags: ['script', 'noscript', 'style', 'textarea', 'pre'],
            inlineMath: [['$','$']]
            }
        });
    </script>
</head>