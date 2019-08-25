---
layout: post
title:  Yii 框架missingAction函数xss漏洞分析解决
tags: php yii xss
---
### Yii missingAction xss漏洞
missingAction 是Yii框架controller层用来处理用户请求的action不存在的情况的方法， 在CController.php中实现。

core/web/CController.php中，missingAction代码如下， [CController.php全部代码]( https://github.com/yiisoft/yii/blob/1.1.17/framework/web/CController.php)

```php
/**
 * Handles the request whose action is not recognized.
 * This method is invoked when the controller cannot find the requested action.
 * The default implementation simply throws an exception.
 * @param string $actionID the missing action name
 * @throws CHttpException whenever this method is invoked
 */
public function missingAction($actionID)
{
    throw new CHttpException(404,Yii::t('yii','The system is unable to find the requested action "{action}".',
        array('{action}'=>$actionID==''?$this->defaultAction:$actionID)));  }

```


actionID 变量直接返回可能会导致xss攻击
比如下列请求， 

```
http://yourhost/api/albumPic/getClassPhotoList<a hREF=feed:javascript&colon;prompt(972840)>
```

直接用actionID变量组成异常信息抛出到前端的话，可能会带来xss攻击， 可以对actionid做一下处理，会避免xss攻击
 代码修改为：

```php
throw new CHttpException(404,Yii::t('yii','The system is unable to find the requested action "{action}".',
        array('{action}'=>htmlspecialchars($actionID==''?$this->defaultAction:$actionID))));    }
```





### php web 安全总结
可能存在的攻击类型
#### 1. xss (cross site script ) 跨站脚本攻击
预防策略： 对用户输入使用函数strip_tags(), htmlspecialchars()以及htmlentities()进行过滤。

#### 2. mysql数据注入
预防策略：

* addslashes() 对字符串进行特殊字符的处理，
* mysql_escape_string(), mysql_real_escape_string()对sql语句进行特殊字符转义处理， mysql_real_escape_string转义sql字符串中特殊字符时还会考虑到当前链接的字符集， php 4.3版本以后引入的。

#### 3. csrf (cross site request forgery ) 跨站请求伪造
#### 4. 拒绝服务攻击(dos)以及分布式拒绝服务攻击(ddos)
* dos: denial of service  拒绝服务攻击
* ddos distributed denial-of-service 分布式拒绝服务攻击