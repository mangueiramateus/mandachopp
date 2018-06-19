<?php
	include "config.php";

	$db = new mysqli($host,$user_db,$password_db);
	if($db->connect_error){
		die("Connection error: ".$db->connect_eror);
	}
	$tag_id = $_GET["TAG"];
	$new_balance = $_GET["balance"];
	$sql = "use cervejaria;";
	$result = $db->query($sql);

	echo "<p>New balance: $new_balance </p>" ;
	echo "<p>Tag ID: $tag_id</p>";


?>
