<?php

	require "config.php";
	require "lib.php";

	$db = new mysqli($host_db,$user_db,$password_db,$db_name);
	if($db->connect_error){
		die("Falha de conexão: ".$db->connect_error);
	}
	$tag_number = $_POST["tag_number"];
	$cpf = $_POST["cpf"];
	$phone_var = $_POST["phone"];

	if($tag_number != NULL){
		if(istagexist($tag_number,$db)){
			if(istagused($tag_number,$db)){				
				$varCPF = getcpfbytagnumber($tag_number,$db);
				$client_id = getclientidbycpf($varCPF,$db);
				echo json_encode(getTags($client_id,$db));
			}
			else{
				echo "Tag não usada.";
			}
		}
		else{
			echo "Tag não cadastrada.";
		}
	}

	if($cpf != NULL ){
		$name = getnamebycpf($cpf,$db);	
		if($name == NULL){
			echo "CPF não cadastrado.";
		}
		else{
			$client_id = getclientidbycpf($cpf,$db);
			echo json_encode(getTags($client_id,$db));
			
		}
	}

        if($phone_var != NULL ){
                $name = getnamebyphone($phone_var,$db); 
                if($name == NULL){
                        echo "Telefone não cadastrado.";
                }
                else{
                    $varCPF = getcpfbyphone($phone_var,$db);
                    $client_id = getclientidbycpf($varCPF,$db);
					echo json_encode(getTags($client_id,$db));
                }
        }

?>