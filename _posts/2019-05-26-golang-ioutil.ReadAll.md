---
layout: post
title: "[golang踩的坑] ioutil.ReadAll 会清空对应Reader"
tags: go
---
### 问题
在golang web后台开发中，为了能够随机采集小部分请求case, 在框架里统一加了部分请求详细信息上报的逻辑，其中用到了，`body, err := ioutil.ReadAll(ctx.Request.Body) `来读取请求body里的内容，
后面业务逻辑中再取body内容时取出来的是空。

### 解决方案

google了下，如下应该能解决这个问题
```
body, err := ioutil.ReadAll(ctx.Request.Body)
rdr := ioutil.NopCloser(bytes.NewBuffer(body))
ctx.Request.Body = rdr

```

### 参考
[reading-body-of-http-request-without-modifying-request-state](https://stackoverflow.com/questions/23070876/reading-body-of-http-request-without-modifying-request-state)

[httputil](https://golang.org/src/net/http/httputil/dump.go#L26)
