<?php
	require "lib.php";
	require "config.php";
	
	$db = new mysqli($host_db,$user_db,$password_db,$db_name);

	$new_value = $_POST["value"];	
	$tag_number = $_POST["tag_number"];
	$old_value = getbalancebytagnumber($tag_number,$db);
	$description = $_POST["payment_method"];
	if(istagexist($tag_number,$db)){
		if(istagused($tag_number,$db)){
			if(updatebalancebytagnumber($tag_number,100*$new_value + $old_value,$db)){
				writelog($tag_number,$new_value,$description,$db);
				echo "Compra realizada com sucesso";				
			}
			else{
				echo "Erro";
			}			
		}
		else{
			echo "Tag não usada";
		}
	}
	else{
		echo "Tag não cadastrada";
	}
	$db->close();
?>
