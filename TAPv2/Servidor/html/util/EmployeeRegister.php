<?php
	require "lib.php";
	require "config.php";
	
	$db = new mysqli($host_db,$user_db,$password_db,$db_name);
	// if($db->connect_error){
	// 	die("Falha de conexão");
	// }
	// else{
	// 	echo "Conectado";
	// }
	$name = $_POST["name"];
	$cpf = $_POST["cpf"];
	$login = $_POST["login"];
	$password = $_POST["password"];

	if($name == NULL){
		die("Digite o nome do Funcionário");
	}
	if($cpf == NULL){
		die("Digite o CPF do Funcionário");
	}
	if($login == NULL){
		die("Digite o login do Funcionário");
	}
	if($password == NULL){
		die("Digite o senha do Funcionário");
	}
	if(getcpf($cpf,$db)){
		die("CPF cadastrado");
	}
	if(isloginused($login,$db)){
		die("Escolha outro login");
	}
	else{
		addUser($name,$cpf,$login,$password,$db);
		echo "Cadastrado com sucesso";
	}
	$db->close();
?>
