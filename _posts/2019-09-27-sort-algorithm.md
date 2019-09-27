---
title: 十大排序算法
tags: 排序
layout: post
---

# 排序算法的代码实现
## cpp 
[cpp实现代码](https://github.com/hucaihui/hucaihui.github.io/tree/master/src/cpp/sortAlgorithm)
- 冒泡排序
- 插入排序
- 简单选择排序
- 希尔排序
- 堆排序
- 归并排序
- 快速排序
- 计数排序（待写）
- 桶排序（待写）
- 基数排序（待写）

## 排序算法之间的关系
![](https://github.com/hucaihui/hucaihui.github.io/tree/master/img/mind-mapping-sort-algorithmalgrihtm.png)
## 排序算法的复杂度对比

|排序算法|排序方式|稳定性|平均情况|最好情况|最坏情况|辅助空间|
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|冒泡排序|in place|稳定  |<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(n^2)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(n)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(n^2)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(1)" />|
|选择排序|in place|稳定  |<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(n^2)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(n^2)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(n^2)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(1)" />|
|插入排序|in place|稳定  |<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(n^2)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(n)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(n^2)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(1)" />|
|希尔排序|in place|不稳定|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(nlogn-n^2)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(n^{1.3})" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(n^2)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(1)" />|
|堆排序  |in place|不稳定|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(nlogn)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(nlogn)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(nlogn)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(1)" />|
|归并排序|out place|稳定 |<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(nlogn)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(nlogn)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(nlogn)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(n)" />|
|快速排序|in place|不稳定|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(nlogn)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(nlogn)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(nlogn)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(logn-n)" />|
|计数排序|in place|稳定  |<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(n+k)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(n+k)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(n+k)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(k)" />|
|桶排序  |in place|稳定  |<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(n+k)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(n+k)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(n^2)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(n+k)" />|
|基数排序|in place|稳定  |<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(n{\times}k)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(n{\times}k)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(n{\times}k)" />|<img src="https://latex.codecogs.com/png.latex?\dpi{100}&space;O(n+k)" />|


