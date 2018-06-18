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
3. PROTOCOLO DE COMUNICAÇÃO
4. COMANDO ACK
5. COMANDO READ
6. COMANDO SENSOR
7. COMANDO VALVE
8. COMANDO MODO
9. COMANDO RESET
10. ERROS


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