<!DOCTYPE html>

<html>
	<head>
		<script type="text/javascript" src="lib.js"></script>
		<style id="style">
			.container {
				width:100%;
				margin-top: 5px;
				/*border: 1px solid grey;
				align-content: center;*/
			}
			table{
				margin: 0 auto;
			}			
		</style>
	</head>

	<body style="align: center">

	<div id="client" class="container">
		<script type="text/javascript">
			
			var msg = window.AppInventor.getWebViewString().split(",");	
			var clientPHP = new XMLHttpRequest();
			var tagPHP = new XMLHttpRequest();

			clientPHP.open("POST","getinfo.php",false);
			clientPHP.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
			tagPHP.open("POST","tagInfo.php",false);
			tagPHP.setRequestHeader("Content-type", "application/x-www-form-urlencoded");			

			switch(msg[1]){
				case "1":
					clientPHP.send("tag_number="+msg[0]);
					tagPHP.send("tag_number="+msg[0]);
					//alert(msg[0]);
					break;
				case "2":
					clientPHP.send("cpf="+msg[0]);
					tagPHP.send("cpf="+msg[0]);
					//alert(msg[0]);
					break;
				case "3":
					clientPHP.send("phone="+msg[0]);
					tagPHP.send("phone="+msg[0]);
					//alert(msg[0]);
					break;
				default:
					//alert();
			}

			var json = JSON.parse(clientPHP.responseText);	
			document.getElementById("client").appendChild(json2table(json,"Informações do Cliente"));
			
		</script>
	</div>	
	<div id="tag" class="container">
		<script type="text/javascript">
			json = JSON.parse(tagPHP.responseText);
			//document.write(tagPHP.responseText);
			document.getElementById("tag").appendChild(json2table(json,"Informações do Cartão"));
		</script>
	</div>	
	</body>
</html>
