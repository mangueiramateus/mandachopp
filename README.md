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
3. PROTOCOLO DE COMUNICA��O
4. COMANDO ACK
5. COMANDO READ
6. COMANDO SENSOR
7. COMANDO VALVE
8. COMANDO MODO
9. COMANDO RESET
10. ERROS


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