<?php 
$serv = new swoole_http_server('127.0.0.1', 8080);
$serv->on('request', function($request, $response) {
    var_dump($request->get);
    var_dump($request->header);
    $response->cookie('User', 'Swoole');
    $response->header('x-server', 'Swoole');
    $respose->end("Hello Swoole");
});

$serv->start();
