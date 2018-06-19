<!DOCTYPE html>

<html>
	<head>
		<script type="text/javascript" src="lib.js"></script>
		<style id="style">			
		</style>
	</head>

	<body>

		<script type="text/javascript">
			
			var msg = window.AppInventor.getWebViewString();	
			var xhttp = new XMLHttpRequest();

			xhttp.open("POST","gettapinfo.php",false);
			xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");			
			xhttp.send("taps_id="+msg);
			//alert("taps_id="+msg);
			var json = JSON.parse(xhttp.responseText);
			//document.write(xhttp.responseText);	
			document.body.appendChild(json2table(json,"Informações da Torneira"));

		</script>		
	</body>
</html>
