<?php
	function gettagnumber($tag_id,$db){
		$sql = "select tag_number from rfid where tag_id='$tag_id';";
		$result = $db->query($sql);
                if($result->num_rows > 0){
                        $row = $result->fetch_assoc();
                        return $row["tag_number"];
                }

	}
   	function getTags($client_id,$db){
		$row = array();
		$sql = "select rfid.tag_number,rfid.balance from (rfid inner join rfid_client on rfid.tag_number = rfid_client.tag_number and rfid_client.client_id = '$client_id');";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			while($r = $result->fetch_assoc()){
				$row[] = $r;
			}
			return $row;
		}
   	}
	function resetflagbytagnumber($tag_number,$db){
                $sql = "update rfid set flag=0 where tag_number = '$tag_number';";
                $result = $db->query($sql);
        }
	function getTap($tap,$db){
		$row = array();
		$sql = "select * from taps where taps_id = '$tap';";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			while($r = $result->fetch_assoc()){
				$row[] = $r;
			}
			return $row;
		}
	}
	
	function getClient($client_id,$db){
		$sql = "select * from client where client_id = '$client_id';";
		$result = $db->query($sql);
		$row = array();

		if($result->num_rows > 0){
			while($r = $result->fetch_assoc()){
				$row[] = $r;
			}
			return $row;			
		}
	}
	
	function getUser($userID,$db){
		$sql = "select * from client;";// where client_id = '$userID';";
		$result = $db->query($sql);
		return $result;
	}
	
	function getnamebyphone($phone,$db){
		$sql = "select name from client where phone = '$phone';";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			$row = $result->fetch_assoc();
			return $row["name"];
		}
	}
	
	function tapexist($tap,$db){
		$sql = "select taps_id from taps where taps_id = '$tap';";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			return TRUE;
		}
		else{
			return FALSE;
		}
	}
	
	function getlastnamephone($phone,$db){
		$sql = "select last_name from client where phone = '$phone';";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			$row = $result->fetch_assoc();
			return $row["last_name"];
		}
	}

	function getbirthdatephone($phone,$db){
		$sql = "select birth_date from client where phone = '$phone';";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			$row = $result->fetch_assoc();
			return $row["birth_date"];
		}
	}

	function getcpfbyphone($phone,$db){
		$sql = "select cpf from client where phone = '$phone';";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			$row = $result->fetch_assoc();
			return $row["cpf"];
		}
	}

	function gettagnumberphone($phone,$db){
		$sql = "select rfid_client.tag_number from (client inner join rfid_client on client.client_id = rfid_client.client_id and phone = '$phone');";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			$row = $result->fetch_assoc();
			return $row["tag_number"];
		}
	}

	function getbalancephone($phone,$db){
		$sql = "select rfid.balance from (client inner join rfid_client on client.client_id = rfid_client.client_id) inner join rfid on rfid_client.tag_number = rfid.tag_number and phone = '$phone';";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			$row = $result->fetch_assoc();
			return $row["balance"];
		}
	}

	function getphone($tag_number,$db){
		$sql = "select phone from (client inner join rfid_client on client.client_id = rfid_client.client_id and rfid_client.tag_number = '$tag_number');";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			$row = $result->fetch_assoc();
			return $row["phone"];
		}
	}
	
	function getlastname($tag_number,$db){
		$sql = "select last_name from (client inner join rfid_client on client.client_id = rfid_client.client_id and rfid_client.tag_number = '$tag_number');";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			$row = $result->fetch_assoc();
			return $row["last_name"];
		}
	}

	function getlastnamecpf($cpf,$db){
		$sql = "select last_name from client where cpf = '$cpf';";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			$row = $result->fetch_assoc();
			return $row["last_name"];
		}
	}
	
	function getbirthdatecpf($cpf,$db){
		$sql = "select birth_date from client where cpf = '$cpf';";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			$row = $result->fetch_assoc();
			return $row["birth_date"];
		}
	}
	
	function getphonecpf($cpf,$db){
		$sql = "select phone from client where cpf = '$cpf';";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			$row = $result->fetch_assoc();
			return $row["phone"];
		}
	}

	function gettagnumbercpf($cpf,$db){
		$client_id = getclientidbycpf($cpf,$db);
		$sql = "select tag_number from rfid_client where client_id = '$client_id';";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			$row = $result->fetch_assoc();
			return $row["tag_number"];
		}
	}

	function getbirthdate($tag_number,$db){
		$sql = "select birth_date from (client inner join rfid_client on client.client_id = rfid_client.client_id and rfid_client.tag_number = '$tag_number');";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			$row = $result->fetch_assoc();
			return $row["birth_date"];
		}
	}

	function setflag($tag_id,$db){
		$sql = "update rfid set flag= 1 where tag_id = '$tag_id';";
		$result = $db->query($sql);
	}
	
	function resetflag($tag_id,$db){
		$sql = "update rfid set flag= 0 where tag_id = '$tag_id';";
		$result = $db->query($sql);
	}
	
	function getflag($tag_id,$db){
		$sql = "select flag from rfid where tag_id = '$tag_id';";
		$result = $db->query($sql);
		if($result->num_rows){
			$row = $result->fetch_assoc();
			return $row["flag"];
		}
	}

	function getvolume($tap,$db){
		$sql = "select volume from taps where taps_id = '$tap';";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			$row = $result->fetch_assoc();
			return $row["volume"];
		}
	}
	
	function updatetitle($tap,$title,$db){
		$sql = "update taps set title = '$title' where taps_id = '$tap';";
		$result = $db->query($sql);
	}
	
	function updatevolume($tap,$valor,$db){
                $sql = "update taps set volume = '$valor' where taps_id = '$tap';";
                $result = $db->query($sql);
	}
	
	function getTapMode($tap, $db){
		$sql = "select mode from taps where taps_id = '$tap';";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			$row = $result->fetch_assoc();
			return $row["mode"];
		}
	}
	
	function updateTapMode($tap, $mode, $db){
		$sql = "update taps set mode = $mode where taps_id = $tap;";
		$result = $db->query($sql);
		return $result;
	}
	
	function gettaptitle($tap,$db){
		$sql = "select title from taps where taps_id = '$tap';";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			$row = $result->fetch_assoc();
			return $row["title"];
		}
	}
	
	function getTapValor($tap, $db){
		$sql = "select valor from taps where taps_id = '$tap';";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			$row = $result->fetch_assoc();
			return $row["valor"];
		}
	}
	
	function updateTapValor($tap, $valor, $db){
		$sql = "update taps set valor = $valor where taps_id = $tap;";
		$result = $db->query($sql);
		return $result;
	}
	
	function getNameByCPF($cpf,$db){
		$sql = "select client.name from client where client.cpf = '$cpf';";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			$row = $result->fetch_assoc();
			return $row["name"];
		}
	}
	
	function getBalanceByCPF($cpf,$db){
		$sql = "select rfid.balance from ((client inner join rfid_client on client.client_id = rfid_client.client_id) inner join rfid on rfid_client.tag_number = rfid.tag_number and client.cpf ='$cpf');";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			$row = $result->fetch_assoc();
			return  $row["balance"];
		}
	}
	
	function getRankByCPF($cpf,$db){
		$sql = "select rfid.rank from ((client inner join rfid_client on client.client_id = rfid_client.client_id) inner join rfid on rfid_client.tag_number = rfid.tag_number and client.cpf ='$cpf');";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			$row = $result->fetch_assoc();
			return $row["rank"];
		}
	}
	
	function getNameByTagNumber($tag_number,$db){
		$sql = "select client.name from (client inner join rfid_client on rfid_client.client_id = client.client_id and rfid_client.tag_number = '$tag_number');";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			$row = $result->fetch_assoc();
			return $row["name"];
		}
	}
	
	function getbalancebytagnumber($tag_number,$db){
		$sql = "select balance from rfid where tag_number = '$tag_number'";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			$row = $result->fetch_assoc();
			return $row["balance"];
		}
	}
	
	function getcpfbytagnumber($tag_number,$db){
		$sql = "select client.cpf from ((client inner join rfid_client on rfid_client.client_id = client.client_id) inner join rfid on rfid_client.tag_number = rfid.tag_number and rfid.tag_number = '$tag_number');";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			$row = $result->fetch_assoc();
			return $row["cpf"];
		}
	}
	
	function getrankbytagnumber($tag_number,$db){
		$sql = "select rank from rfid where tag_number = '$tag_number';";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			$row = $result->fetch_assoc();
			return $row["rank"];
		}
	}
    	
	function getnamebytagid($tag_id,$db){
		$sql = "select client.name from ((client inner join rfid_client on rfid_client.client_id = client.client_id) inner join rfid on rfid_client.tag_number = rfid.tag_number and rfid.tag_id = '$tag_id');";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			$row = $result->fetch_assoc();
			return $row["name"];
		}
	}

	function getbalancebytagid($tag_id,$db){
		$sql = "select balance from rfid where tag_id = '$tag_id';";
		$result = $db->query($sql);
        if($result->num_rows > 0){
            $row = $result->fetch_assoc();
            return $row["balance"];
        }
	}
	
	function getrankbytagid($tag_id,$db){
		$sql = "select rank from rfid where tag_id = '$tag_id';";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			$row = $result->fetch_assoc();
			return $row["rank"];
		}
	}

	function updatebirthdatebycpf($cpf,$birth_date,$db){
		$sql = "update client set birth_date='$birth_date' where cpf = '$cpf';";
		$result = $db->query($sql);
	}

	function updatenamebycpf($cpf,$name,$db){
		$sql = "update client set name='$name' where cpf = '$cpf';";
		$result = $db->query($sql);
	}
	
	function updatelastnamebycpf($cpf,$last_name,$db){
		$sql = "update client set last_name='$last_name' where cpf = '$cpf';";
		$result = $db->query($sql);
	}
	
	function updatephonebycpf($cpf,$phone,$db){
		$sql = "update client set phone='$phone' where cpf = '$cpf';";
		$result = $db->query($sql);
	}

	function updatebalancebytagnumber($tag_number,$value,$db){
		$sql = "update rfid set balance ='$value' where tag_number = '$tag_number';";
		$result = $db->query($sql);
		$new_value = getbalancebytagnumber($tag_number,$db);
		if($new_value == $value){
			return TRUE;
		}
		else{
			return FALSE;
		}
	}
	
	function updatebalancebytagid($tag_id,$value,$db){
		$sql = "update rfid set balance ='$value' where tag_id = '$tag_id';";
		$result = $db->query($sql);
		$new_value = getbalancebytagid($tag_id,$db);
		if($new_value == $value){
			return TRUE;
		}
		else{
			return FALSE;
		}
	}
	
	function updaterankbytagnumber($tag_number,$value,$db){
	}
	
	function updaterankbytagid($tag_id,$value,$db){
	}
	
	function isloginused($login,$db){
		$sql = "select login from user where login = '$login';";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			return TRUE;
		}
		else{
			return FALSE;
		}
	}
	
	function addUser($name,$cpf,$login,$password,$db){
		$sql = "insert into user(name,login,password,cpf,job) values ('$name','$login','$password','$cpf','func');";
		$result = $db->query($sql);
	}
	
	function getcpf($cpf,$db){
		$sql = "select cpf from client where cpf='$cpf';";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			return TRUE;
		}
		else{
			return FALSE;
		}
	}
	
	function getclientidbycpf($cpf,$db){
		$sql = "select client_id from client where cpf='$cpf';";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			$row = $result->fetch_assoc();
			return $row["client_id"];
		}
		else{
			return FALSE;
		}
	}
	
	function insertclient($name,$last_name,$cpf,$phone,$birth_date,$tag_number,$db){
		$client_id = getclientidbycpf($cpf,$db);
		if($client_id == FALSE){
			$sql = "insert into client(name,last_name,cpf,phone,birth_date) values ('$name','$last_name','$cpf','$phone','$birth_date');";
			$result = $db->query($sql);
			$client_id = getclientidbycpf($cpf,$db);
			$sql = "insert into rfid_client(tag_number,client_id) values ('$tag_number','$client_id');";
			$result = $db->query($sql);
			return TRUE;
		}
		else{
			return FALSE;
		}
	}
	
	function istagexist($tag_number,$db){
		$sql = "select tag_number from rfid where tag_number = '$tag_number';";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			return TRUE;
		}
		else{
			return FALSE;
		}
	}
	
	function istagidexist($tag_id,$db){
		$sql = "select tag_id from rfid where tag_id = '$tag_id';";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			return TRUE;
		}
		else{
			return FALSE;
		}
	}
	
	function istagused($tag_number,$db){
		$sql = "select client_id from rfid_client where tag_number='$tag_number';";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			return TRUE;
		}
		else{
			return FALSE;
		}
	}
	
	function writelog($tag_number,$new_value,$description,$db){
		$current_balance = getbalancebytagnumber($tag_number,$db);
		$client_id = getclientidbytagnumber($tag_number,$db);
		//echo $current_balance."  ".$client_id;
		$date = date('Y-m-d');
		$time = date('H:i:s');
		//echo "  ".$date."  ".$time;
		$sql = "insert into orderLog(order_date,client_id,description,new_value,current_value,order_time) values('$date','$client_id','$description','$new_value','$current_balance','$time');";
		$result=$db->query($sql);
	}
	
	function getclientidbytagnumber($tag_number,$db){
		$sql = "select client_id from rfid_client where tag_number = '$tag_number';";
		$result = $db->query($sql);
		if($result->num_rows > 0){
			$row = $result->fetch_assoc();
			return $row["client_id"];
		}
	}

?>
