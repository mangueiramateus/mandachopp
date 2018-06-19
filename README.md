FIRMWARE MODULE TAP
Costru��o do firmware para rodar como perif�rico do tablet, que por sia vez controla todo o sistema. 
Atividades:
1. INICIALIZAR PERIF�RICOS - DONE IN 12/JUN
	> Definir os perif�ricos da placa e forma de inicializa��o:
	>> BUETOOTH -> abertura da comunica��o serial (.begin)
	>> RFID -> inicializa��o com comandos ao m�dulo (.init)
	>> LEDs(vermelho, amarelo, azul e verde) -> defini��o como sa�da (pinMode) e desativa��o (digitalWrite)
	>> BUZZER -> defini��o como sa�da (pinMode) e desativa��o (digitalWrite)
	>> BOTAO -> defini��o como entrada (pinMode)
	>> SENSOR -> defini��o como entrada
	>> VALVULA -> defini��o como sa�da (pinMode) e desativa��o (digitalWrite)
2. COMUNICA��O BLUETOOTH
    > Verificar se a comunica��o � bem estabelecida para troca de informa��es
3. PROTOCOLO DE COMUNICA��O - DONE IN 18/JUN
    > Protocolo de comunica��o definido como os seguintes comandos:
	>> ACK ->		TAP1:0:0: => TAP1:OK
	>> ECHO ->		TAP1:1:0: => devolve �ltima resposta de comando
	>> READ -> 		TAP1:2:0: => TAP1:2:TAG:BTN:OK = ler status do RFID e do bot�o
	>> SENSOR ->	TAP1:3:0: => TAP1:3:OK = desativa interrup��o do sensor
	>>>				TAP1:3:1: => TAP1:3:OK = ativa interrup��o do sensor
	>>>				TAP1:3:2: => TAP1:3:PULSOS:VAZAO:OK = ler status do sensor
	>> VALVES ->	TAP1:4:0: => TAP1:4:OK = ativa v�lvula
	>>>				TAP1:4:1: => TAP1:4:OK = desativa v�lvula 
	>> FILL -> 		TAP1:5:0: => TAP1:5:OK = desativa modo consumo
	>>>				TAP1:5:PULSOS: => TAP1:5:OK = ativa modo consumo at� PULSOS m�ximo
	>> LEDON -> 	TAP1:6:LED?: => TAP1:6:OK = desativa o LED de acordo com o n�mero:
	>>>				0-vermelho, 1-amarelo, 2-azul, 3-verde
	>> LEDOFF -> 	TAP1:7:LED: => TAP1:7:OK = ativa o LED de acordo com o n�mero acima
	>> BUZZER ->	TAP1:8:N: => TAP1:8:OK = apita o BUZZER N vezes
	>> RESET ->		TAP1:9:0: => TAP1:9:OK = reseta o m�dulo
4. COMANDOS ACK/ECHO - DONE IN 18/JUN
	> Comando ACK e ECHO pronto.
5. COMANDO READ - DONE IN 18/JUN
	> Comando READ pronto
6. COMANDO SENSOR
7. COMANDO VALVE
8. COMANDO FILL
9. COMANDOS LEDON, LEDOFF, BUZZER
10. COMANDO RESET


APP TABLET ANDROID
Cria��o do aplicativo de controle que rodar� no tablet
1. GERAL
	1.1 Instalar IDE Android Studio - DONE IN 4/JUN
	1.2 Criar projeto e diret�rio GIT - DONE IN 14/JUN
2. TELA INICIALIZAR
	2.1 Verificar background
	2.2 Conex�o Wifi
	2.3 Comunica��o Servidor
	2.4 Comunica��o Module Tap
3. TELA PRONTO
4. TELA LIBERADO
5. TELA INATIVIDADE
6. TELA CONSUMO
7. TELA CALIBRANDO
8. DEMAIS TELAS


SERVIDOR RASPBERRY
1. ATIVAR BANCO DE DADOS PELO PYTHON
2. VERIFICAR PENDRIVE 
3. ALTERAR DIRET�RIO SALVAMENTO BD
4. VALIDA��O C�DIGO ATUAL
5. COMUNICA��O PHP E PYTHON POR SOCKET
6. SALVAMENTO CLIENTES EM EXCEL
7. CADASTRO DE NOVAS TAGS
8. DESLIGAMENTO
9. LAYOUT PCB