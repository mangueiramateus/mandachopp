/*
  FIRMARE 2.0 MODULE TAP MANDA CHOPP
    Versão para segunda versão do sistema na qual este código funcionará como firmware para o arduino que 
  por sua vez funcionará como periférico do tablet. Este último será o controlador principal.
  
  FAZER
    1. Enum com os comandos e os erros
    2. Biblioteca para cada operação
    3. Leitura do RFID
    4. Leitura do sensor

*/

#include <Arduino.h>
#include <TimerOne.h>
#include <SoftwareSerial.h>
#include <MFRC522.h>

//INTERFACE
#define BRANCO 14
#define AMARELO 15
#define AZUL 16
#define VERDE 17

#define BUZZER 5
#define BTN 20

//CONTROLE DO FLUXO
#define SENSOR 2
#define VALVE 8
unsigned int pulsos = 0;
int volume = 0;
int fluxo = 0;

//RFID
constexpr uint8_t RST_PIN = 9;
constexpr uint8_t SS_PIN = 10; 
MFRC522 RFID(SS_PIN, RST_PIN);

//BLUETOOTH
SoftwareSerial blue(3, 4);

//FUNÇÕES
#define LEDon(led) digitalWrite(led, HIGH)
#define LEDoff(led) digitalWrite(led, LOW)
String ler_TAG();
char ler_BTN();
void apitar(byte vezes, byte tempo);

void setup(){
  //Inicialização do bluetooth e da Serial
  blue.begin(9600);
  Serial.begin(9600);
  //Inicialização do RFID
  SPI.begin();
  RFID.PCD_Init();

  //Inicialização dos periféricos
  pinMode(BRANCO, OUTPUT);
  pinMode(AMARELO, OUTPUT);
  pinMode(AZUL, OUTPUT);
  pinMode(VERDE, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);
  pinMode(VALVE, OUTPUT);
  pinMode(SENSOR, INPUT);
  //Aviso sonoro de inicialização
  apitar(1, 100);


  //Timer1.initialize(100000);
  //Timer1.attachInterrupt( calculo );
  //blue.println("TAP1:__NULL__:0");
}

bool isData = false;
byte cmd = 0;
unsigned long int param = 0;
String data = "", ans = "";
String tag = "";
char btn = '0';
void loop(){

  //Verifica se há comando do bluetooth
  while (blue.available()){
    data += (char)blue.read();
    isData = true;
    delay(1);
  }

  //Verifica se TAG ou bortão já foi lida pelo bluetooth. Se não faz nova leitura
  if (tag == "") tag = ler_TAG();
  if (btn == '0') btn = ler_BTN();

  //Há novo dado
  if (isData){
    //Espelha o dado
    Serial.println(data);
    //Verifica o cabeçalho
    if (data.indexOf("TAP1") != -1){
      byte aux1 = data.indexOf(":");
      byte aux2 = data.indexOf(":", aux1+1);
      cmd = data.substring(aux1+1, aux2).toInt();
      aux1 = data.indexOf(":", aux2+1);
      param = data.substring(aux2+1, aux1).toInt();
      bool OK = data.substring(aux1+1, aux1+3) == "OK";
      bool write = true;
      if (OK){
        //Comando ACK
        if (cmd == 0)  ans = "TAP1:OK";
        //Comando ECHO
        else if (cmd == 1) {
          if (ans == "") ans = "TAP1:OK";
        }
        //Comando READ
        else if (cmd == 2) {
          if (tag == "") tag = "__NULL__";
          else Serial.println(tag);
          ans = "TAP1:2:" + tag + ":" + btn + ":OK";
          tag = "";
          btn = '0';
        }
        //Comando SENSOR
        else if (cmd == 3) ans = "TAP1:3:OK";
        //Comando VALVE
        else if (cmd == 4) ans = "TAP1:4:OK";
        //Comando FILL
        else if (cmd == 5) ans = "TAP1:5:OK";
        //Comando LEDON
        else if (cmd == 6) ans = "TAP1:6:OK";
        //Comando LEDOFF
        else if (cmd == 7) ans = "TAP1:7:OK";
        //Comando BUZZER
        else if (cmd == 8) ans = "TAP1:8:OK";
        //Comando RESET
        else if (cmd == 9) ans = "TAP1:9:OK";
        else write = false;
        if (write){
          blue.println(ans);
          Serial.println(ans);
        }
      }
      else blue.println("ERROR");  
    }
    else blue.println("ERROR");
    data = "";
    isData = false;
  }
}

void conta_vol() {
  pulsos++;
}
bool state = false;
int fluxo_1 = 0;
void calculo() {
  noInterrupts();
  volume += pulsos;
  fluxo = pulsos/2 + fluxo_1/2;
  fluxo_1 = fluxo;
  pulsos = 0;
  state = !state;
  digitalWrite(BRANCO, state);
  interrupts();
}

String ler_TAG() {
  if (RFID.PICC_IsNewCardPresent() && RFID.PICC_ReadCardSerial()) {
    apitar(2, 20);
    String conteudo = "";
    for (byte i = 0; i < RFID.uid.size; i++)
    {
      conteudo.concat(String(RFID.uid.uidByte[i] < 0x10 ? "0" : ""));
      conteudo.concat(String(RFID.uid.uidByte[i], HEX));
    }
    return conteudo;
  }
  else return "";
}

char ler_BTN(){
  if (analogRead(BTN) < 100) return '1';
  else return '0';
}

void apitar(byte vezes, byte tempo) {
  int i = 0;
  while(i < vezes){
    digitalWrite(BUZZER, HIGH);
    delay(tempo);
    digitalWrite(BUZZER, LOW);
    i++;
    if (i == vezes) break;
    delay(tempo);
  }
}

