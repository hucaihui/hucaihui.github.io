---
title: 2019数模A题简单的demo
tag: py demo
layout: post
---

# 注：
运行文件会在`./model/`下生成.pb文件

提交modelArt测试时和baseLine一样。无需修改config.json，customize_service.py


```
import tensorflow as tf

if __name__=='__main__':

    n = 17

    X = tf.placeholder(tf.float32, shape=[None,n], name='input')  # input
    W1 = tf.get_variable("W1", [n,1], initializer=tf.zeros_initializer())
    b1 = tf.constant(65.245615,tf.float32)
    Z = tf.matmul(X,W1) + b1     # outputs

    init = tf.global_variables_initializer()
    with tf.Session() as sess:
        sess.run(init)
        # sess.run(Z,feed_dict={X:})

        # 保存模型
        tf.saved_model.simple_save(sess, './model/', inputs={"myInput": X}, outputs={"myOutput": Z})

```
