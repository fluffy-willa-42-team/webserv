<?php

echo "Post\n";

$handle = fopen ("php://stdin","r");
while (!feof($handle)) {
    $buffer = fread($handle, 4096);
    echo $buffer;
}
fclose($handle);

var_dump($_POST);
