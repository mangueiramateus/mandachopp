<?php
	require "util/config.php";
	require "util/lib.php";

	$tag_id = $_GET["TAG"];
	$db = new mysqli($host_db,$user_db,$password_db,$db_name);

	$name = getnamebytagid($tag_id,$db);
	$saldo = getbalancebytagid($tag_id,$db);
	$rank = getrankbytagid($tag_id,$db);
	//$uso = getflag($tag_id, $db);
	//if ($uso == 0) setflag($tag_id, $db);
	$uso = 0; //mudar isso para impletar TAG EM USO
	if($name == NULL){
		echo "PI:FAIL";
	}
	else{
		echo "PI:FIND:". $name. "&" .$saldo. "&" .$rank . "&" . $uso . "&";
	}
	//PI:FIND:nome do clinte  & saldo em centavos & rank de posição & uso da torneira & 
	$db->close();

?>

