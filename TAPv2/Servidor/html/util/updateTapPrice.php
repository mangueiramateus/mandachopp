<?php

        require "config.php";
        require "lib.php";

        $TAP = $_POST["taps_id"];
        $valor = $_POST["valor"];
	$volume = $_POST["volume"];
	$title = $_POST["title"];
        $db = new mysqli($host_db,$user_db,$password_db,$db_name);

        if($TAP and $valor != NULL){
		updateTapValor($TAP,$valor*100,$db);
	}
	if($TAP and $volume != NULL){
		updatevolume($TAP,$volume,$db);
	}
	if($TAP and $title != NULL){
		updatetitle($TAP,$title,$db);
	}
	$db->close();
?>
