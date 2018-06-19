
function json2table(jsonObject,tableTitle){

	var table = document.createElement("TABLE");
	var header = table.createTHead();
	var rowHeader = header.insertRow(0);
	var tbody = document.createElement("TBODY");
	var rowTbody = [];
	var cellTbody = [];
	var cellHeader = [];
	var jsonKeys = [];
	var i = 0;
	var j = 0;
	var title = document.createElement("CAPTION");
	var style = document.getElementById("style");
	var propeties = `
	table,th,td,caption {
				border: 1px solid black;
				border-collapse: collapse;
				padding: 5px;
				text-align: center;
			}			
			caption{
				font-weight: bold;
			}
			tr:nth-child(even){
				background-color: #f2f2f2;
			}`;
	
	var stylePropeties = document.createTextNode(propeties);
	style.appendChild(stylePropeties);
	table.appendChild(style);
	title.innerHTML = tableTitle;
	table.appendChild(title);

	i = 0;
	for(x in jsonObject[0]){
		jsonKeys.push(x);
		cellHeader[i] = document.createElement("TH");
		rowHeader.appendChild(cellHeader[i]);
		cellHeader[i].innerHTML = jsonKeys[i];
		i++;
	}

	//document.write(jsonObject.length);

	for(i = 0; i < jsonObject.length; i++){
		rowTbody[i] = document.createElement("TR");
		tbody.appendChild(rowTbody[i]);
		for(j = 0; j < jsonKeys.length; j++){
			cellTbody[j] = document.createElement("TD");
			rowTbody[i].appendChild(cellTbody[j]);
			cellTbody[j].innerHTML = json[i][jsonKeys[j]];
		}
	}				

	table.appendChild(tbody);
	return table;
}

