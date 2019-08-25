---
layout: post
title: golang 解析toml配置文件
tags: golang toml
---

#####golang代码如下：
```
package main

import (
    "fmt"

    "github.com/BurntSushi/toml"
)

func main() {
    str_toml := `[[conf]]
        [[conf.a1]]
        min = 10
        max = 10240
        [[conf.a2]]
        min = 5000
        max = 10240
        [[conf.a3]]
        "xxxx.yyyy.com"=[0 ,100]
        `
    type MinMax struct {
        Min int
        Max int
    }
    type OneLevelConf struct {
        A1 []MinMax
        A2 []MinMax
        A3 []map[string]([]int64)
    }

    type CONF struct {
        Conf []OneLevelConf
    }
    var Conf CONF
    _, err2 := toml.Decode(str_toml, &Conf)
    if err2 != nil {
        fmt.Println("decode failed, error: ", err2)
    }
    fmt.Printf("decoded: %+v\n", Conf)
}
```

代码输出结果：
```
decoded: {Conf:[{A1:[{Min:10 Max:10240}] A2:[{Min:5000 Max:10240}] A3:[map[xxxx.yyyy.com:[0 100]]]}]} 
```

golang toml解析的package 可以通过：`go get github.com/BurntSushi/toml` 来安装

>解析起来最大的问题就是在结构体的定义。

未完待续

####参考
[toml github](https://github.com/mojombo/toml)

[toml sf ](https://segmentfault.com/a/1190000000477752)

