<?php

function myconnect($req, $resp) {
    echo "connect \n";
}
function myreceive($req, $resp) {
    echo "received \n";
}
$s = new swoole_server('127.0.0.1', 8000);
$s->on('connect', 'myconnect');
$s->on('receive', 'myreceive');
$s->start();
