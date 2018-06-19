<?php
	require "config.php";
	require "lib.php";

	$ID = $_GET["ID"];
	$STATUS = $_GET["STATUS"];
	$db = new mysqli($host_db,$user_db,$password_db,$db_name);
	if ($STATUS != NULL){
		if ($STATUS == "0") resetStatus($ID, $db);
		if ($STATUS == "1") setStatus($ID, $db);
	}
	else {
		$status = getStatus($ID, $db);
		if ($status == "0") setStatus($ID, $db);
		if ($status == "1") resetStatus($ID, $db);
	}
	$STATUS = getStatus($ID, $db);
	echo "STATUS: " . $STATUS;
?>

