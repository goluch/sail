<?php
// phpinfo();

$file = 'sail.exe ';


// get actual date
date_default_timezone_set('Europe/Warsaw');
$timezone = date_default_timezone_get();
//echo "The current server timezone is: " . $timezone;
$today = getdate();

// get weather maps
$ufile = fopen('u.csv', 'w');
$vfile = fopen('v.csv', 'w');
$ulink = "http://91.221.26.72/accusWebApi.php?request=getMap&varid=20&year=$today[year]&month=$today[mon]&day=$today[mday]&hour=$today[hours]";
$vlink = "http://91.221.26.72/accusWebApi.php?request=getMap&varid=21&year=$today[year]&month=$today[mon]&day=$today[mday]&hour=$today[hours]";
//echo $ulink;
//echo $vlink;
$u = file_get_contents($ulink);
$v = file_get_contents($vlink);
fwrite($ufile, $u);
fwrite($vfile, $v);
fclose($ufile);
fclose($vfile);

$file .= $_GET["string"];
echo(exec($file));

//$respParams = explode(",", $_GET["string"]);
//echo($respParams[0] . "," . $respParams[1] . ",WNW," . $respParams[2] . "," . $respParams[3] . ",SSE");
//echo("18.7152,54.4227,WNW,18.8152,54.5227,E,18.8134,54.4945,SSE");
?> 