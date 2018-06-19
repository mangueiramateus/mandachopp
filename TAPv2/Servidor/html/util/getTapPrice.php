<?php

	require "config.php";
	require "lib.php";

	$TAP = $_POST["taps_id"];
	$valor = $_POST["VALOR"];
	$db = new mysqli($host_db,$user_db,$password_db,$db_name);

	$valor = getTapValor($TAP, $db);
	if ($valor == NULL) echo "FAIL";
	else echo "PI:" . $valor . ":" . $TAP . ":";

?>
