<?php
	require "config.php";
	require "lib.php";
	
	$db = new mysqli($host_db,$user_db,$password_db,$db_name);
	$tap = $_POST["taps_id"];
	if(tapexist($tap,$db)){
		echo json_encode(getTap($tap,$db));
	}
	else{
		echo "Torneira não cadastrada";
	}

?>
