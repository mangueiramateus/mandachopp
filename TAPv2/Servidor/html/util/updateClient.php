
<?php
	require "config.php";
	require "lib.php";

	$db = new mysqli($host_db,$user_db,$password_db,$db_name);

	$name=$_POST["name"];
	$cpf=$_POST["cpf"];
	$last_name=$_POST["last_name"];
	$phone = $_POST["phone"];
	$day = $_POST["day"];
	$month = $_POST["month"];
	$year = $_POST["year"];
	$new_card = $_POST["new_card"];
	$card = $_POST["card"];
	
	if(($day and $month and $year) != NULL){
        	$birth_date= $year."-".$month."-".$day;
        	$timeStampNow = strtotime(date('Y-m-d'));
        	$timeStampBirthDate = strtotime($birth_date);
        	$age = (int)floor(($timeStampNow-$timeStampBirthDate)/(60*60*24*365));
        	if($age < 18){
               		die("Cliente menor de 18 anos.");
        	}
	}

	if(getcpf($cpf,$db)){
		if($name != NULL){
			updatenamebycpf($cpf,$name,$db);
			echo "Operação realizada com sucesso";
		}
		if($last_name != NULL){
                        updatelastnamebycpf($cpf,$last_name,$db);
                        echo "Operação realizada com sucesso";
                }
		if($phone != NULL){
                        updatephonebycpf($cpf,$phone,$db);
                        echo "Operação realizada com sucesso";
                }
		if($birth_date != NULL){
			updatebirthdatebycpf($cpf,$birth_date,$db);
			echo "Operação realizada com sucesso";
		}
		if($new_card != NULL){
			if(istagexist($new_card,$db)){
				if(!istagused($new_card,$db)){
					$client_id = getclientidbycpf($cpf,$db);
					$sql = "insert into rfid_client(tag_number,client_id) values('$new_card','$client_id');";
					$result = $db->query($sql);
					echo $client_id;
					echo "Operação realizada com sucesso";
				}
				else{
					echo "Tag indisponível";
				}
			}
			else{
				echo "Tag não cadastrado no BD";
			}
		}
		if($card != NULL){
			if(istagexist($card,$db)){
				if(istagused($card,$db)){
					//$client_id = getclientidbycpf($cpf,$db);
					//echo $client_id;
					//$balanceNew = getBalanceByCPF($cpf,$db);
					//$sql = "update rfid_client set tag_number='$card' where client_id='$client_id';";
					//$result = $db->query($sql);
					//$sql = "update rfid set balance='$balanceNew' where tag_number='$card';";
					//$result = $db->query($sql);
					echo "Tag indisponível";
				}
				else{
                                        $client_id = getclientidbycpf($cpf,$db);
                                        //echo $client_id;
                                        $balanceNew = getBalanceByCPF($cpf,$db);
                                        $sql = "update rfid_client set tag_number='$card' where client_id='$client_id';";
                                        $result = $db->query($sql);
                                        $sql = "update rfid set balance='$balanceNew' where tag_number='$card';";
                                        $result = $db->query($sql);

                                }
			}
			else{
                                echo "Tag não cadastrado no BD";
                        }

		}
	}
	else{
		echo "CPF não cadastrado";
	}







?>
