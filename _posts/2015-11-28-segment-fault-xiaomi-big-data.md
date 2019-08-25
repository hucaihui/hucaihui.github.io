---
layout: post
title: sf 小米大数据-技术小实践
tags: data
---

**介绍小米大数据**

##为么青睐hbase

* 天生为了大数据
* 改变schema很平滑
* 扩容方便
* 成本考虑
* facebook 等公司做了很好的示范

##小米对hbase的改进

##mysql迁移hbase

1. 双写
2. 异步同步mysql老的数据到hbase
3. 双读，并做数据校验
4. 灰度返回hbase的结果
5. 只写hbase

##[kafka](http://kafka.apache.org/) && [druid](http://huyongde.github.io/2015/11/28/segment-fault-big-data.html)


