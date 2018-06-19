#include "Perifericos.h"
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <MFRC522.h>  //Leitor RFID
#include <SPI.h>      //Habilita comunicação SPI

SoftwareSerial esp(3, 4);
#define ESP_RST 18

#define SS_PIN 10
#define RST_PIN 9
MFRC522 RFID(SS_PIN, RST_PIN);


String resp = "";
String info = "";

void PerifericosClass::InicializarWifi() {
  ERRO = 0;
  esp.begin(9600);
  pinMode(ESP_RST, OUTPUT);
  digitalWrite(ESP_RST, LOW);
  delay(500);
  digitalWrite(ESP_RST, HIGH);
  long unsigned int tempo = millis();
  while ((millis() - tempo) < 5000) if (esp.available()) Serial.print((char)esp.read());
}

void PerifericosClass::Servidor(){
  //verificando conexão com o módulo
  ERRO = 0;
  enviar_comando("END", 2000);
  Serial.println(resp);
  if (resp.indexOf("OK") < 0) {
    //Serial.println(F("ERRO: Sem resposta do módulo"));
    ERRO = 1;
    return;
  }

  if (resp.indexOf("ERROR") != -1){
    ERRO = 2;
    return;
  }

  //Envia as informações ao servidor
  enviar_comando("INI:END", 10000);
  Serial.println(resp);
  int aux1 = resp.indexOf("PI");
  if (aux1 < 0) {
    //Serial.println(F("ERRO: Requisição recebida inválida"));
    ERRO = 3;
  }
  aux1 = resp.indexOf(":", aux1);
  int aux2 = resp.indexOf(":", aux1+1);
  VALOR = resp.substring(aux1+1, aux2).toInt();
  Serial.println("VALOR: " + String(VALOR));
}

void PerifericosClass::enviar_comando(String cmd, long int timeout) {
  long int tempo = millis();
  esp.print(cmd);
  while (!esp.available()) if ((millis() - tempo) > timeout) return "timeout";
  resp = (char)esp.read();
  tempo = millis();
  while (1) {
    if (esp.available()) {
      resp += (char)esp.read();
      tempo = millis();
    }
    else if (resp.indexOf("OK") != -1) break;
    if ((millis() - tempo) > timeout) {
      resp += ":timeout";
      break;
    }
    delay(1);
  }
}

void PerifericosClass::obtem_litros(){
  LITROS = EEPROM.read(1) << 8;
  LITROS |= EEPROM.read(0);
}

void PerifericosClass::atualiza_litros(int litros){
  LITROS = litros;
  byte val1 = litros;
  byte val2 = litros >> 8;
  EEPROM.write(0, val1);
  EEPROM.write(1, val2);
}
void PerifericosClass::InicializarRFID() {
  SPI.begin();
  RFID.PCD_Init();
}

String PerifericosClass::ler_TAG(byte BUZZER) {
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

bool PerifericosClass::consultaTAG(String TAG) {
  ERRO = 0;
  //Envia as informações ao servidor
  info = "SEARCH:" + TAG + ":END";
  enviar_comando(info, 10000);
  Serial.println(resp);
  if (resp.indexOf("PI") < 0) {
    //Serial.println(F("ERRO: Requisição recebida inválida"));
    ERRO = 4;
    return false;
  }

  int aux = resp.indexOf("FIND");
  int auxx;
  if (aux < 0) {
    return false;
  }
  aux = resp.indexOf(":", aux);
  auxx = resp.indexOf("&", aux);
  user.nome = resp.substring(aux + 1, auxx);

  aux = auxx;
  auxx = resp.indexOf("&", aux + 1);
  user.saldo = resp.substring(aux + 1, auxx).toInt();

  aux = auxx;
  auxx = resp.indexOf("/n", aux + 1);
  user.rank = resp.substring(aux + 1, auxx).toInt();

  user.litros = (user.saldo*1000.0)/VALOR;
  return true;
}

bool PerifericosClass::atualizarSaldo(int Saldo, String TAG) {
  ERRO = 0;
  info = "UPDATE:" + TAG + ":" + String(Saldo) + ":END";
  enviar_comando(info, 10000);
  Serial.println(resp);
  if (resp.indexOf("PI") < 0) {
    //Serial.println(F("ERRO: Requisição recebida inválida"));
    ERRO = 5;
    return false;
  }

  if (resp.indexOf("UPDATE") < 0) {
    return false;
  }
  return true;
}
