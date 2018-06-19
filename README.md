FIRMWARE MODULE TAP
Costrução do firmware para rodar como periférico do tablet, que por sia vez controla todo o sistema. 
Atividades:
1. INICIALIZAR PERIFÉRICOS - DONE IN 12/JUN
    > Definir os periféricos da placa e forma de inicialização:
	>> BUETOOTH -> abertura da comunicação serial (.begin)
	>> RFID -> inicialização com comandos ao módulo (.init)
	>> LEDs(vermelho, amarelo, azul e verde) -> definição como saída (pinMode) e desativação (digitalWrite)
	>> BUZZER -> definição como saída (pinMode) e desativação (digitalWrite)
	>> BOTAO -> definição como entrada (pinMode)
	>> SENSOR -> definição como entrada
	>> VALVULA -> definição como saída (pinMode) e desativação (digitalWrite)
2. COMUNICAÇÃO BLUETOOTH
    > Verificar se a comunicação é bem estabelecida para troca de informações
3. PROTOCOLO DE COMUNICAÇÃO - DONE IN 18/JUN
    > Protocolo de comunicação definido como os seguintes comandos:
	ACK ->		TAP1:0:0: => TAP1:OK
	ECHO ->		TAP1:1:0: => devolve última resposta de comando
	READ -> 	TAP1:2:0: => TAP1:2:TAG:BTN:OK = ler status do RFID e do botão
	SENSOR ->	TAP1:3:0: => TAP1:3:OK = desativa interrupção do sensor
			TAP1:3:1: => TAP1:3:OK = ativa interrupção do sensor
			TAP1:3:2: => TAP1:3:PULSOS:VAZAO:OK = ler status do sensor
	VALVES ->	TAP1:4:0: => TAP1:4:OK = ativa válvula
			TAP1:4:1: => TAP1:4:OK = desativa válvula 
	FILL -> 	TAP1:5:0: => TAP1:5:OK = desativa modo consumo
			TAP1:5:PULSOS: => TAP1:5:OK = ativa modo consumo até PULSOS máximo
	LEDON -> 	TAP1:6:LED?: => TAP1:6:OK = desativa o LED de acordo com o número:
						0-vermelho, 1-amarelo, 2-azul, 3-verde
	LEDOFF -> 	TAP1:7:LED: => TAP1:7:OK = ativa o LED de acordo com o número acima
	BUZZER ->	TAP1:8:N: => TAP1:8:OK = apita o BUZZER N vezes
	RESET ->	TAP1:9:0: => TAP1:9:OK = reseta o módulo
4. COMANDOS ACK/ECHO - DONE IN 18/JUN
5. COMANDO READ
6. COMANDO SENSOR
7. COMANDO VALVE
8. COMANDO FILL
9. COMANDOS LEDON, LEDOFF, BUZZER
10. COMANDO RESET


APP TABLET ANDROID
Criação do aplicativo de controle que rodará no tablet
1. GERAL
    1.1 Instalar IDE Android Studio - DONE IN 4/JUN
    1.2 Criar projeto e diretório GIT - DONE IN 14/JUN
2. TELA INICIALIZAR
    2.1 Verificar background
    2.2 Conexão Wifi
    2.3 Comunicação Servidor
    2.4 Comunicação Module Tap
3. TELA PRONTO
4. TELA LIBERADO
5. TELA INATIVIDADE
6. TELA CONSUMO
7. TELA CALIBRANDO
8. DEMAIS TELAS


SERVIDOR RASPBERRY
1. ATIVAR BANCO DE DADOS PELO PYTHON
2. VERIFICAR PENDRIVE 
3. ALTERAR DIRETÓRIO SALVAMENTO BD
4. VALIDAÇÃO CÓDIGO ATUAL
5. COMUNICAÇÃO PHP E PYTHON POR SOCKET
6. SALVAMENTO CLIENTES EM EXCEL
7. CADASTRO DE NOVAS TAGS
8. DESLIGAMENTO
9. LAYOUT PCB