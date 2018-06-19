<?php
	require "lib.php";
	require "config.php";
	
	$db = new mysqli($host_db,$user_db,$password_db,$db_name);

	$name = $_POST["name"];
	$last_name = $_POST["last_name"];
	$cpf = $_POST["cpf"];
	$phone = $_POST["phone"];
	$year=$_POST["year"];
	$month=$_POST["month"];
	$day=$_POST["day"];
	$tag_number = $_POST["tag_number"];
	$birth_date= $year."-".$month."-".$day;
	$timeStampNow = strtotime(date('Y-m-d'));
	$timeStampBirthDate = strtotime($birth_date);
	$age = (int)floor(($timeStampNow-$timeStampBirthDate)/(60*60*24*365));
	if($age < 18){
		die("Cliente menor de 18 anos.");
	}
	if(istagexist($tag_number,$db)){
		if(istagused($tag_number,$db)){
			echo "Tag em uso.";
		}
		else{
		
			if(insertclient($name,$last_name,$cpf,$phone,$birth_date,$tag_number,$db)){
				echo "Cliente cadastrado com sucesso";
			}
			else{
				echo "Cliente ja esta cadastrado.";
			}
		}
	}
	else{
		echo "Tag não cadastrada no BD.";
	}
	$db->close();
?>
