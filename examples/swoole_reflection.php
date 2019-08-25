<?php

$extension_name = "swoole";
$re = new ReflectionExtension($extension_name);
// var_dump($re->getClasses()); // 获取扩展中的类列表

// var_dump($re->getClassNames()); // 获取扩展中的类信息
/*
$class_name = 'Swoole\Server';
$class_name = 'swoole_server';
$rc = new ReflectionClass($class_name);
$methods = $rc->getMethods();
print_r($methods);exit;
*/

foreach($re->getClassNames() as $class_name) {
    $rc = new ReflectionClass($class_name);
    echo $rc->getShortName() . ' ';
    echo $class_name . "\n"; continue;
    echo "$class_name info: \n";
    var_dump($rc);
}
exit;
var_dump($re->getConstants()); // 获取扩展中的常量
var_dump($re->getDependencies()); // 获取扩展依赖
var_dump($re->getDependencies()); // 获取扩展中的常量
var_dump($re->getFunctions()); // 获取扩展中的函数
var_dump($re->getName()); // 获取扩展的名字
var_dump($re->getINIEntries()); // 获取扩展的配置信息

var_dump($re->Info()); // 获取扩展的基本信息
var_dump($re->IsPersistent()); // 获取扩展是否持久加载
var_dump($re->__toString()); // 获取扩展是否持久加载


