#!/usr/bin/env python

import serial
import time
import os


ser = serial.Serial('/dev/ttyUSB0', 9600, timeout = 1)
time.sleep(2)


print "Serial conectada"

ser.write('r')

resp = ser.readline()
print 'Resposta: ' + resp

print resp[0:2] + "/" + resp[2:4] + "/" + resp[4:8] + " " + resp[8:10] + ":" + resp[10:12] + ":" + resp[12:14]

print "Deseja atualizar data: [Y/N]"

op = raw_input()
if (op == 'Y' or op == 'y'):
	s = os.system("date -s " + resp[4:8] + "/" + resp[2:4] + "/" + resp[0:2])
	s = os.system("date -s " + resp[8:10] + ":" + resp[10:12] + ":" + resp[12:14])
	

