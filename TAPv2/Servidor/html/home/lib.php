<?php

	function getStatus($id,$db){
		$row = array();
		$sql = "select status from pontos where id = $id;";
		$result = $db->query($sql);
		$result =  $result->fetch_assoc();
		return $result["status"];
	}
	function setStatus($id,$db){
		$sql = "update pontos set status = 1 where id = $id;";
		$result = $db->query($sql);
	}
	function resetStatus($id,$db){
		$sql = "update pontos set status = 0 where id = $id;";
                $result = $db->query($sql);
	}

?>
