<?php
function a($a, $b = 1) {
    echo "in function " . $a . $b;
}
class RE_Detail {

}
//var_dump(ReflectionClass::export('ReflectionClass'));exit; // 查看异常类exception的相关信息

$class_name = 'RE_Detail';
$rc = new ReflectionClass($class_name);
//var_dump($rc->getMethods());exit; // 查看类的成员函数列表
//var_dump($rc->getDocComment()); exit; // 获取类的文档注释

// 获取类开始行号和结束行号
//var_dump($rc->getStartLine()); var_dump($rc->getEndLine());exit; 

// ReflectionFunction::export 第二个参数设置为true时， 
// 会把函数对应的描述信息当做函数返回值进行返回
//var_dump(ReflectionFunction::export('explode', true));exit; 
$function_name = 'a';
$rf = new ReflectionFunction('a');
$rf->invoke(100, 200);
$params = array(100, 300);
echo "\n";
$rf->invokeArgs($params);
echo $rf;
exit;

$extension_name = "swoole";
$re = new ReflectionExtension($extension_name);
// var_dump($re->getClasses()); // 获取扩展中的类列表

// var_dump($re->getClassNames()); // 获取扩展中的类信息
foreach($re->getClassNames() as $class_name) {
    $rc = ReflectionClass::export($class_name);
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


