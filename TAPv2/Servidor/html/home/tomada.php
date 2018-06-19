<?php
	require "config.php";
	require "lib.php";

	$ID = $_GET["ID"];

	$db = new mysqli($host_db,$user_db,$password_db,$db_name);
	$status = getStatus($ID, $db);
	echo "STATUS=" . $status;
?>

