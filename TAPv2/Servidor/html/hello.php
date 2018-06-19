<?php
	require "util/config.php";
    require "util/lib.php";
    
	$TAP = $_GET["TAP"];
	$valor = $_GET["VALOR"];
	$volume = $_GET["VOLUME"];
	$db = new mysqli($host_db,$user_db,$password_db,$db_name);
	if ($valor != NULL) updateTapValor($TAP, $valor, $db);
	if ($volume != NULL) updatevolume($TAP, $volume, $db);

	$valor = getTapValor($TAP, $db);
	$mode = getTapMode($TAP, $db);
	$volume = getvolume($TAP, $db);
	$tipo = gettaptitle($TAP, $db);//"PILSSEN";
	if ($valor == NULL) echo "FAIL";
	else echo "PI&" . $valor . "&" . $mode . "&" . $volume . "&" . $tipo . "&" . $TAP . "&";
	//PI:valor_torneira:modo_operacao:volume_torneira:
	$db->close();
?>

