<?php
	require "config.php";
	$db = new mysqli($host_db,$user_db,$password_db,$db_name);
	if($db->connect_error){
		die("Falha de rede.");
	}
	$login = $_POST["login"];
	$password = $_POST["password"];
	//echo $login."	".$password;
	$sql = "select job from user where login='$login' and password='$password';";
	$result = $db->query($sql);
	if($result->num_rows > 0){
		$row = $result->fetch_assoc();
		echo $row["job"];
	}
	else{
		echo "Login ou Senha incorreto.";
	}
	$db->close();
?>
