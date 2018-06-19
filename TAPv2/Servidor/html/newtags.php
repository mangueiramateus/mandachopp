<?php
	/* SCRIPT PARA INSERIR NOVAS TAGS NO BANCO DE DADOS OU 
	 * SOBRESCREVER EM UM ID EXISTENTE
	 */
	require "util/config.php";
    require "util/lib.php";
    
	$TAG = $_GET["TAG"];
	$ID = $_GET["ID"];
	
	$db = new mysqli($host_db,$user_db,$password_db,$db_name);
		
	$name = getnamebytagid($TAG,$db);
	$sql = "select tag_number from rfid where tag_id = '$TAG';";
	$result = $db->query($sql);
	$row = $result->fetch_assoc();
	$id = $row["tag_number"];
	
	if ($name != NULL) {
		echo "USUARIO: " . $name . " | ID: " . $id;
		if ($ID != NULL) echo " | NAO ALTERADO";
	}
	else {
		if ($id != NULL) {
			echo "SEM USUARIO | ID: " . $id;
			if ($ID != NULL) echo " | NAO ALTERADO";
		}
		else{
			echo "NAO EXISTE NO BANCO DE DADOS";
			if ($ID != NULL){
				$sql = "insert into rfid(tag_number,tag_id,balance,rank,flag) values ('$ID','$TAG','0','0','0');";
				$result = $db->query($sql);
				echo " | TAG: $TAG | ID: $ID";
			}
		}
	}
	
	
	
?>
