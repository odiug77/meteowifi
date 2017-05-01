# meteowifi

esmpio php per ricevere i dati e scrivere su un file

```
<?php
    $txt = "temp=".$_POST['temp']." pres =".$_POST['pres']." umid=".$_POST['umid']." temp2=".$_POST['temp2'];
    file_put_contents('data.txt', $txt.PHP_EOL , FILE_APPEND | LOCK_EX);
?>
```
