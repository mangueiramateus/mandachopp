#!/usr/bin/env python
# -*- encoding:utf-8 -*-
#SCRIPT DE INICIALIZACAO DO SISTEMA

import ds1302
import time
import os
import commands

import sys

import MySQLdb


#VERIFICANDO DATA DO SISTEMA

f = open('rtc.log', 'a')
sys.stdout = f

print "> Sistema iniciado"

o = commands.getoutput("date -Ins ")

y, m, d, h, mi, s = o[0:4], o[5:7], o[8:10], o[11:13], o[14:16], o[17:19]

ds1302.init_clock()

for i in range(10):		
	year, month, day = ds1302.get_date()
	hour, minute, second = ds1302.get_time()
	if (month > 12): month = 0
	if (day > 31): day = 0
	if (hour > 24): hour = 0
	if (minute > 60): minute = 0
	if (second > 60): second = 0
	if (int(mi) < minute or int(h) < hour or 
		int(d) < day or int(m) < month):
		print ">>> Atualizando data"
		os.system("date -s " + str(year) + "/" + str(month) + "/" + str(day))
		os.system("date -s " + str(hour) + ":" + str(minute)+ ":" + str(second))
		o = commands.getoutput("date -Ins ")
		y, m, d, h, mi, s = o[0:4], o[5:7], o[8:10], o[11:13], o[14:16], o[17:19]
		break
	if (int(mi) == minute and int(h) == hour and
		int(d) == day and int(m) == month and int(y) == year):
		break
else:
	print ">>> ERRO RTC: execute script de atualização da data do RTC"
	print ">> RTC: " + str(day) + "/" + str(month) + "/" + str(year) + " " + str(hour) + ":" + str(minute) + ":" + str(second)
	
	print
	f.close()
	quit()
	
print ">> RTC: " + str(day) + "/" + str(month) + "/" + str(year) + " " + str(hour) + ":" + str(minute) + ":" + str(second)
print ">> RASP: " + d + "/" + m + "/" + y + " " + h + ":" + mi + ":" + s


#RESETA AS FLAGS DO BANCO DE DADOS
print "> Resetando flags"

con = MySQLdb.connect(host = "localhost", user = "beer", passwd = "12345678", db = "usuarios")

cur = con.cursor()

cur.execute("SELECT * from rfid;")

for row in cur.fetchall():
	if row[4] == 1: 
		cur.execute("update rfid set flag=0 where tag_number=" + str(row[0])+";")
		print ">> reset tag_number=" + str(row[0]) +";"
con.commit()
		

print "> pronto"
print
f.close()





#escreve no log status/data

#escreve no log status do banco de dados

#aguarda leitura da serial
#verifica se tem um módulo de cadastro conectado
#se sim e primeira vez escreve no log status do modulo
#verifica se tem algo na serial
#se sim ler a tag e numero e inclui no  banco de dados
#escreve no log
#volta a verificas se tem modulo
