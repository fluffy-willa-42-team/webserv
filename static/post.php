<?php

var_dump($_POST);

$handle = fopen ("php://stdin","r");
while (!feof($handle)) {
    $buffer = fread($handle, 4096);
    echo $buffer;
}
fclose($handle);