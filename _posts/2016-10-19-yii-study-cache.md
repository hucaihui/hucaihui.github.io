---
layout: post
title: yii table schema cache and query result cache
tags: schema cache query 
---
### 简介

本文主要介绍YII框架性能优化相关的两个方法：数据库表元信息cache以及数据库查询结果cache。

### Yii db schema cache 相关： 
* Yii框架可能比较慢的原因: 
 It will do a show columns query, then a show create tablequery, then finally it will query the database for the actual data. Those first two queries are so Yii knows the schema of your user table. If the round trip time from your application server to your database server is 100ms (if it's really this slow, you should do something about it), then those two queries to get the schema will add a minimum of 200ms to your application response time. It will do this for every single request that populates your User model. Depending on how your application is written, it might even do that multiple times in a single request.

* 翻译过来大概意思是：Yii框架在真正执行sql之前需要执行`show columns from xxx;show create table xxx`, 相当于额外增加了两次数据库操作，为了节省这两次数据库操作的时间，引入了数据库表schema的cache, 常用cache有memcache,redis等

* cache key 的构成：类CDbSchema(framework/db/schema/CDbSchema.php)中的getTable方法中会利用到schema cache来获取数据库表的metadata即schema， 其中包括了如何生成缓存table metadata 的key等代码。[源码链接]( https://github.com/yiisoft/yii/blob/1.1.17/framework/db/schema/CDbSchema.php#L72)       关键代码：`$key='yii:dbschema'.$this->_connection->connectionString.':'.$this->_connection->username.':'.$name;`, 以字符串的形式把表的schema信息存储在cache中。


### Yii db query result cache  相关
* 缓存数据库查询结果到cache的方法的[源码](https://github.com/yiisoft/yii/blob/1.1.17/framework/caching/CCache.php#L173)， 是CCache类的set成员函数，其中有处理dependency的逻辑，函数代码如下：

```
 public function set($id,$value,$expire=0,$dependency=null)
    {
        Yii::trace('Saving "'.$id.'" to cache','system.caching.'.get_class($this));
        if ($dependency !== null && $this->serializer !== false)
            $dependency->evaluateDependency();
        if ($this->serializer === null)
            $value = serialize(array($value,$dependency));
        elseif ($this->serializer !== false)
            $value = call_user_func($this->serializer[0], array($value,$dependency));
        return $this->setValue($this->generateUniqueKey($id), $value, $expire);
    }

```

从代码可以看到cache下来的数据包括了dependency的信息，

* 从cache中获取query result时的[源码](https://github.com/yiisoft/yii/blob/1.1.17/framework/caching/CCache.php#L102), 其中会把cache中的dependency的内容去掉，再返回给调用者，详细代码如下:

```
public function get($id)
    {
        $value = $this->getValue($this->generateUniqueKey($id));
        if($value===false || $this->serializer===false)
            return $value;
        if($this->serializer===null)
            $value=unserialize($value);
        else
            $value=call_user_func($this->serializer[1], $value);
        if(is_array($value) && (!$value[1] instanceof ICacheDependency || !$value[1]->getHasChanged()))
        {
            Yii::trace('Serving "'.$id.'" from cache','system.caching.'.get_class($this));
            return $value[0];
        }
        else
            return false;
    }
```

* query result cache 查询和写入的入口在CDbCommand的queryInternal函数，[源码](https://github.com/yiisoft/yii/blob/1.1.17/framework/db/CDbCommand.php#L470),

其中调用`cache->get`的部分核心代码如下:

```
$cacheKey='yii:dbquery'.':'.$method.':'.$this->_connection->connectionString.':'.$this->_connection->username;
            $cacheKey.=':'.$this->getText().':'.serialize(array_merge($this->_paramLog,$params));
            if(($result=$cache->get($cacheKey))!==false)
            {
                Yii::trace('Query result found in cache','system.db.CDbCommand');
                return $result[0];
            }
```

其中调用`cache->set`的核心代码如下:

```
if(isset($cache,$cacheKey))
    $cache->set($cacheKey,array($result),$this->_connection->queryCachingDuration, $this->_connection->queryCachingDependency);
```

* 对于query result cache依赖的dependency, 相关的类有：CCacheDependency类，类中有计算dependency是否变化的函数getHasChanged此函数需要依赖函数generateDependentData(), **当新生成的dependency的属性值于cache中缓存下来的值发生变化时**，则认为此query result cache已经失效， 需要重新从数据库获取最新数据. [CCacheDependency的源码](https://github.com/yiisoft/yii/blob/1.1.17/framework/caching/dependencies/CCacheDependency.php#L67)

* query result cache 其实是把一个复杂的sql查询，依赖于一个相对简单的sql查询，缓存到cache中，每次都去检查简单的sql结果是否发生变化，没发生变化的话就认为复杂的sql查询结果也没发生变化。




### 数据库表schema cache以及query result cache 的相关配置如下:

```
    'components' => array(
        'db' => array(       
            'schemaCachingDuration'=>3600, // 缓存有效期 3600秒
            'queryCachingDuration'=>3600,
            //默认使用cache组件，显示的申明使用redis组件来缓存schemaData和query result
            'schemaCacheID'=>'redis',
            'queryCacheID'=>'redis', // redis组件也需要在components中单独配置
        ),
    )
```

### query result cache 示例

```
    $sql = '执行比较耗时的sql';
    $dependency = new CDbCacheDependency('比较简单的会影响到比较耗时sql的sql');
    $rows = Yii::app()->db->cache(1000, $dependency)->createCommand($sql)->queryAll();
```



### 参考
* [Yii 官网文档](http://www.yiiframework.com/doc/api/1.1/)
* [stack overflow ](http://stackoverflow.com/questions/23466159/the-schema-caching-in-yii)