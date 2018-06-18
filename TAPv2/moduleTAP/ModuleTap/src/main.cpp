#include <Arduino.h>
#include <TimerOne.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>

//INTERFACE
#define BRANCO 14
#define AMARELO 15
#define AZUL 16
#define VERDE 17

#define BUZZER 18
#define BTN 21

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
String data = "";
String tag = "", btn = "0";
void loop(){
  while (blue.available()){
    data += (char)blue.read();
    isData = true;
    delay(1);
  }
  if (tag == "") tag = ler_TAG();
  //if (btn != "1") btn = ler_BTN();
  if (isData){
    Serial.println(data);
    if (data.indexOf("TAP1") != -1){
      if (data.indexOf("ACK") != -1) blue.print("TAP1:OK");
      if (data.indexOf("READ") != -1) {
        if (tag == "") tag = "__NULL__";
        else Serial.println(tag);
        blue.print("TAP1:" + tag + ":" + btn);
        Serial.println("TAP1:" + tag + ":" + btn);
        tag = "";
        btn = "0";
      }
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

String ler_BTN(){
  if (analogRead(BTN) < 100) return "1";
  else return "0";
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

