<?php
        include "config.php";
        
	$tag_id = $_GET["TAG"];
        $db = new mysqli($host_db,$user_db,$password_db);
        if($db->connect_error){
                die(/*"Connection failed: " . $db->connect_error*/);
        }
	else{
		//echo "Connected successfully.";
	}
        $sql = "use $db_name;";
	$result = $db->query($sql);
	$sql = "select client.name,rfid.balance,rfid.rank from ((client inner join rfid_client on client.client_id = rfid_client.client_id) inner join rfid on rfid_client.tag_number = rfid.tag_number and rfid.tag_id ='$tag_id');";
	$result = $db->query($sql);
	if($result->num_rows > 0){
		while($row = $result->fetch_assoc()){
			echo "PI:UPDATE";
		}
	}
	else{
		echo "PI:FAIL";
	}
	$db->close();

?>

