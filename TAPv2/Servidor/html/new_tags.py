#!/usr/bin/env python
# -*- encoding:utf-8 -*-
import MySQLdb
import time
import serial

	

con = MySQLdb.connect(host = "localhost", user = "beer", passwd = "12345678", db = "usuarios")

cur = con.cursor()

cur.execute("update taps set valor = 320 where taps_id = 3")

cur.execute("SELECT * from taps")

for row in cur.fetchall():
	print row[0], " ", row[1]

con.commit()

#verifica se tem algo na serial
#verifica se é o arduino com o leitor de TAG
#abre banco de dados
#aguarda arduino lê a tag
#verifica se a tag já não foi escrita
#se não escreve a tag no banco de dados
#verificar se tem como executar este script pelo navegador com a saída em tempo real
