#!/usr/bin/env python
# -*- encoding:utf-8 -*-
#SCRIPT ATUALIZAÇÃO DE NOVAS TAGS

import serial
import time
import MySQLdb

print "Leitor RFID - CTRL + C para sair"
com = True
while(1):
	try:
		ser = []
		ser = serial.Serial('/dev/ttyUSB0', 9600, timeout = 1)
		time.sleep(2)
		print "Dispositivo USB conectado"
		com = True
		while (1):
			ser.write("O")
			r = ser.readline()
			print r
			if r[:-2] == 'OK': break
			print "Dispositivo não reconhecido"
			time.sleep(5)
		print "Leitor reconhecido"
		con = MySQLdb.connect(host = "localhost", user = "root", passwd = "12345678", db = "usuarios")
		cur = con.cursor()
		while(True):
			ser.write("R")
			r = ser.readline()
			r = r[0:-2]
			if r != 'NULL':
				print "TAG lida: ", r
				cur.execute("select tag_number from rfid where tag_id = '" + r + "';")
				row = cur.fetchall()
				if len(row) != 0:
					print "TAG_id = " + str(row[0][0])
					num1 = row[0][0]
					new = False
				else: 
					print "TAG NOVA"
					new = True
				print
				print "Cadastra? S/N"
				op = raw_input()
				if op.upper() == 'S':
					print "Number: "
					num = raw_input()
					cur.execute("select tag_id from rfid where tag_number = " + num + ";")
					row = cur.fetchall()
					if len(row) != 0:
						print "TAG_number = " + str(row[0][0])
						new2 = False
					else:
						print "NUMBER NOVO"
						new2 = True
					
					if new:
						if new2: print "INSERT"
						else: print "UPDATE TAG_NUMBER"
					else:
						if new2: print "INSERT E DELETE"
						else: print "UPDATE E DELETE"
					print
					print "Continuar S/N"
					op = raw_input()
					if op.upper() == 'S':
						if new:
							if new2:
								cur.execute("insert into rfid (tag_number, tag_id) values (" + num + ",'" + r + "');")
							else:
								cur.execute("update rfid set tag_id='" + r + "' where tag_number = " + num + ";")
						else:
							if new2:
								cur.execute("delete from rfid where tag_number= " + str(num1) + ";")
								cur.execute("insert into rfid (tag_number, tag_id) values (" + num + ",'" + r + "');")
							else:
								cur.execute("delete from rfid where tag_number= " + str(num1) + ";")
								cur.execute("update rfid set tag_id='" + r + "' where tag_number = " + num + ";")
						print "Cadastrado"
						con.commit()
				ser.write('C')
			else: time.sleep(1)
				
	except serial.serialutil.SerialException:
		time.sleep(2)
		if com:
			print "Nenhum dispositivo USB conectado"
			print
			if ser != []: ser.close()
			com = False
	except KeyboardInterrupt:
		print
		print "Saindo"
		if ser != []: ser.close()
		quit()

#QUANDO DETECTADO LER DO TECLADO O NUMERO PARA INSERIR NO BANCO DE DADOS
#MOSTRA NO DISPLAY

#aguarda leitura da serial
#verifica se tem um módulo de cadastro conectado
#se sim e primeira vez escreve no log status do modulo
#verifica se tem algo na serial
#se sim ler a tag e numero e inclui no  banco de dados
#escreve no log
#volta a verificas se tem modulo
