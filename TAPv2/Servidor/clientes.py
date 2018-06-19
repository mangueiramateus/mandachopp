import MySQLdb

con = MySQLdb.connect(host = "localhost", user = "root", passwd = "12345678", db = "usuarios")
cur = con.cursor()
cur1 = con.cursor()
cur.execute("select * from client");
print "  ID |     NOME        |      CPF     |      SOBRENOME       |    BIRTH     |     PHONE    |   TAG   | SALDO"
for row in cur.fetchall():
	cli_id = str(row[0])
	name = str(row[1])
	cpf = str(row[2])
	last = str(row[3])
	birth = str(row[4])
	phone = str(row[5])
	s=""
	
	for i in range(0, 4-len(cli_id)): s += " "
	s += cli_id
	s += " | "
	
	s += name
	for i in range(0, 15-len(name)): s += " "
	s += " | "
	
	s += cpf
	for i in range(0, 12-len(cpf)): s += " "
	s += " | "
	
	s += last
	for i in range(0, 20-len(last)): s += " "
	s += " | "
	
	s += birth
	for i in range(0, 12-len(birth)): s += " "
	s += " | "
	
	s += phone
	for i in range(0, 12-len(phone)): s += " "
	s += " | "
	
	cur1.execute("select tag_number from rfid_client where client_id = " + str(row[0]) + ";")
	for raw in cur1.fetchall():
		s1 = str(raw[0])
	
	s += s1
	for i in range(0, 7-len(s1)): s += " "
	s += " | "
	
	cur1.execute("select balance from rfid where tag_number = " + s1 + ";")
	for raw in cur1.fetchall():
		s1 = str(raw[0])
	
	s += s1
	for i in range(0, 10-len(s1)): s += " "
	
	print s
