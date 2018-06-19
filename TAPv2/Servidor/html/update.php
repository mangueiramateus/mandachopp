<?php
	require "util/config.php";
	require "util/lib.php";
	$tag_id = $_GET["TAG"];
	$saldo = $_GET["SALDO"];
	$tap = $_GET["TAP"];
	$volume = $_GET["VOLUME"];
	$db = new mysqli($host_db,$user_db,$password_db,$db_name);
	$consumo = getbalancebytagid($tag_id,$db) - $saldo;
	//$tag_number = gettagnumber($tag_id, $db);
        //writelog($tag_number, $saldo, "CONSUMO", $db);	
	$state = updatebalancebytagid($tag_id, $saldo, $db);
	resetflag($tag_id, $db);
	if ($tap != NULL && $volume != NULL) {
		updatevolume($tap, $volume, $db);

	}
	if($state){
		$saldo = getbalancebytagid($tag_id,$db);
		$tag_number =  gettagnumber($tag_id, $db);
		writelog($tag_number, $consumo, "CONSUMO", $db);
		echo "PI:UPDATE:" . $saldo . "&" . $tag_number;
	}
	else{
		echo "PI:FAIL";
	}
	$db->close();

?>

