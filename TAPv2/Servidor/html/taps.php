<?php
	require "util/config.php";
    require "util/lib.php";
    
	$TAP = $_GET["TAP"];
	$MODO = $_GET["MODO"];
	$db = new mysqli($host_db,$user_db,$password_db,$db_name);
	
	updateTapMode($TAP, $MODO, $db);
	
	$MODO = getTapMode($TAP, $db);
	echo "TAP: " . $TAP . " | MODO: " . $MODO;
	$db->close();
?>

