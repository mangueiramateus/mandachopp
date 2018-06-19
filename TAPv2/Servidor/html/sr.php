<?php
	require "config.php";
	require "util/lib.php";
	$db = new mysqli($host_db, $user_db, $password_db, $db_name);
	$cpf = $_GET["cpf"];
	$name = $_GET["name"];
	$tag_id = $_GET["tag_id"];
	$tag_number = $_GET["tag_number"];
	updatenamebycpf($cpf,$name,$db);
	$name = getnamebytagnumber($tag_number,$db);
	$balance = getbalancebytagid($tag_id,$db);
	$rank = getrankbytagid($tag_id,$db);
	echo $name ."&".$balance."&".$rank;
	$db->close();
?>
