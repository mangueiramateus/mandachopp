#!/usr/bin/env python
# -*- encoding:utf-8 -*-
#SCRIPT DE INICIALIZACAO DO SISTEMA

import ds1302
import time
import os
import commands

import sys

import MySQLdb

from lib_oled96 import ssd1306
from PIL import ImageFont
from smbus import SMBus

DEBUG = False

def tela_inicial (status, valor = ""):
	o = commands.getoutput("date -Ins ")
	y, m, d, h, mi, s = o[0:4], o[5:7], o[8:10], o[11:13], o[14:16], o[17:19]
	oled.canvas.rectangle((1, 13, oled.width-2, oled.height-3), outline=0, fill=0)
	oled.canvas.text((0,12), d + "/" + m + "/" + y, fill=1, font = font)
	oled.canvas.text((0,28), h + ":" + mi + ":" + s, fill=1, font = font)
	if (status): 
		oled.canvas.text((80,28), 'RFID', fill=1, font = font)
		if valor != "":
			oled.canvas.text((0,44), valor[:-2], fill=1, font = font)
	oled.display()

try:
	
	f = open('/home/pi/init/rtc.log', 'a')
	if (not DEBUG): sys.stdout = f 
	
	#VERIFICANDO DATA DO SISTEMA


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
		try:
			font = ImageFont.truetype('/home/pi/init/FreeSans.ttf', 20)
			i2cbus = SMBus(1)
			oled = ssd1306(i2cbus)
			oled.canvas.text((0,28),   'ERRO RTC', fill=1, font = font)
		except:
			print ">>OLED: erro do display"
			print
		f.close()	
		quit()
		
	print ">> RTC: " + str(day) + "/" + str(month) + "/" + str(year) + " " + str(hour) + ":" + str(minute) + ":" + str(second)
	print ">> RASP: " + d + "/" + m + "/" + y + " " + h + ":" + mi + ":" + s
	erro_display = False
	try:
		i2cbus = SMBus(1)
		oled = ssd1306(i2cbus)
		oled.cls()
		oled.canvas.rectangle((0, 0, oled.width-1, oled.height-2), outline=1, fill=0)
		font = ImageFont.truetype('/home/pi/init/FreeMonoBold.ttf', 16)
		oled.canvas.text((10,0),    'MANDA CHOPP', fill=1, font = font)
		font = ImageFont.truetype('/home/pi/init/FreeSans.ttf', 20)
		#oled.canvas.text((0,12), d + "/" + m + "/" + y, fill=1, font = font)
		#oled.canvas.text((0,28), h + ":" + mi + ":" + s, fill=1, font = font)
		oled.display()
	except:
		erro_display = True

	#RESETA AS FLAGS DO BANCO DE DADOS
	print "> Resetando flags"
	time.sleep(5)
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
except:
	f = open('/home/pi/init/rtc.err', 'a')
	if (not DEBUG): sys.stdout = f
	print "INIT ERROR " + commands.getoutput("date")
	print 
	
if erro_display:
	print ">>ERRO DISPLAY"
	f.close()
	quit()
	
import serial

def escreve(dado):
	f = open('/home/pi/init/rfid.log', 'a')
	if (not DEBUG): sys.stdout = f
	print dado
	f.close()
	
flag = False
f = open('/home/pi/init/rfid.log', 'w')
f.close()
while(1):
	tela_inicial(False)
	time.sleep(0.3)
	try:
		ser = []
		ser = serial.Serial('/dev/ttyUSB0', 9600, timeout = 1)
		time.sleep(2)
		escreve("Dispositivo conectado")
		flag = False
		b = ""
		while (1):
			ser.write("O")
			r = ser.readline()
			if (r.find('OK') > 0):
				tela_inicial(False)
			else :
				ser.write("R")
				r = ser.readline()
				if (r.find('NULL') == -1): b = r
				if (b.find('NULL') == -1): tela_inicial(True, b)
				else: tela_inicial(True)
				
			time.sleep(0.3)
	except:
		if (not flag):
			flag = True
			escreve("Leitor não conectado")
		if ser != []: ser.close()

	
while(1):
	try:
		tela_inicial(False)
		time.sleep(0.3)
	except:
		f = open('/home/pi/init/rtc.err', 'w')
		if (not DEBUG): sys.stdout = f
		print "RUN ERROR " + commands.getoutput("date")
		print 
		oled.cls()
		quit()
	

				





#escreve no log status/data

#escreve no log status do banco de dados

#aguarda leitura da serial
#verifica se tem um módulo de cadastro conectado
#se sim e primeira vez escreve no log status do modulo
#verifica se tem algo na serial
#se sim ler a tag e numero e inclui no  banco de dados
#escreve no log
#volta a verificas se tem modulo
