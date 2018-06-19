#!/usr/bin/env python
# -*- encoding:utf-8 -*-

import time
import serial
import MySQLdb


flag = False

con = MySQLdb.connect(host = "localhost", user = "beer", passwd = "12345678", db = "usuarios")
cur = con.cursor()

while(1):
	time.sleep(0.3)
	try:
		ser = []
		ser = serial.Serial('/dev/ttyUSB0', 9600, timeout = 1)
		time.sleep(2)
		print "Dispositivo conectado"
		flag = False
		b = ""
		while (1):
			ser.write("O")
			r = ser.readline()
			if (r.find('OK') > 0):
				print "Dispositivo não reconhecido"
			else :
				ser.write("R")
				r = ser.readline()
				if (r.find('NULL') == -1): 
					r = r [:-2]
					print r
					#print "DIGITE ID:"
					#ID = raw_input()
					#s = "insert into rfid(tag_number,tag_id,balance,rank,flag) values (" + str(ID) + ",\"" + str(r) + "\",'0','0','0');"
					#cur.execute(str(s))
					#print "OK"
					time.sleep(2)
				
			time.sleep(0.3)
	except:	
		if (not flag):
			flag = True
			print "Leitor não conectado"
		if ser != []: ser.close()
