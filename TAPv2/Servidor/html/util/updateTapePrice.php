<?php

        require "config.php";
        require "lib.php";

        $TAP = $_POST["taps_id"];
        $valor = $_POST["valor"];
        $db = new mysqli($host_db,$user_db,$password_db,$db_name);

        if($TAP and $valor !NULL){
		updateTapValor($TAP,$valor,$db);
	}
?> 
