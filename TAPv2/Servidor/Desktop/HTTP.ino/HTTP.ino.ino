/*COMANDOS DE TESTE
  INI:END -> testa o servidor e verifica o preço por litro
  SEARCH:TAG:END -> verifica uma TAG no servidor
  UPDATE:TAG:SALDO:END -> atualiza um novo saldo de uma TAG no servidor

*/
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#define TAP 1  //!!!!!!!!!!!!!!!!!MUDAR ISSO DE TORNEIRA A TORNEIRA


const char* ssid = "Pi3-PIBIC";
const char* password = "raspberry";

String resp = "";
HTTPClient http;

void setup () {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("START");
}

bool timer = false;
long unsigned int tempo = 0;
bool status = false;
void loop() {
  if (Serial.available()) {
    resp += (char)Serial.read();
    status = !status;
    digitalWrite(LED_BUILTIN, status);
  }
  if (resp != "" && !timer) {
    tempo = millis();
    timer = true;
  }
  if (timer && (millis()-tempo)>2000){
     resp = "";
     timer = false;
  }
  
  if (resp.indexOf("END") != -1) {
    Serial.println(">" + resp);
    if (WiFi.status() == WL_CONNECTED) {
      if (resp.indexOf("INI") != -1) {
        
        http.begin("http://192.168.1.1/hello.php?TAP=" + String(TAP));
        int httpCode = http.GET();
        String payload = http.getString();
        
        Serial.print(">DATA:" + String(httpCode) + ":");
        Serial.print(payload);
        http.end();
      }
      else if (resp.indexOf("SEARCH") != -1){
        byte aux1 = resp.indexOf(":");
        byte aux2 = resp.indexOf(":", aux1+1);
        http.begin("http://192.168.1.1/search.php?TAG=" + resp.substring(aux1+1, aux2));
        int httpCode = http.GET();
        String payload = http.getString();
        
        Serial.print(">DATA:" + String(httpCode) + ":");
        Serial.print(payload);
        http.end();
      }
      else if (resp.indexOf("UPDATE") != -1){
        byte aux1 = resp.indexOf(":");
        byte aux2 = resp.indexOf(":", aux1+1);
        byte aux3 = resp.indexOf(":", aux2+1);
        http.begin("http://192.168.1.1/update.php?TAG=" + resp.substring(aux1+1, aux2) + "&SALDO=" + resp.substring(aux2+1, aux3));
        int httpCode = http.GET();
        String payload = http.getString();
        
        Serial.print(">DATA:" + String(httpCode) + ":");
        Serial.print(payload);
        http.end();
      }
    }
    else {
      Serial.println(">ERROR:WIFI");
    }
    Serial.println(":OK");
    timer = false;
    resp = "";
  }
  
  //delay(500);
}

//void setup () {
// 
//  Serial.begin(9600);
//  WiFi.begin(ssid, password);
// 
//  while (WiFi.status() != WL_CONNECTED) {
// 
//    delay(1000);
//    Serial.println("Connecting..");
// 
//  }
//  Serial.println("CONECTADO");
//  delay(1000);
//}
// 
//void loop() {
// 
//  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
// 
//    HTTPClient http;  //Declare an object of class HTTPClient
//    Serial.println("REQUEST");
//    http.begin("http://192.168.1.1/hello.php");  //Specify request destination
//    int httpCode = http.GET();                                                                  //Send the request
//    Serial.println(httpCode);
//    if (httpCode > 0) { //Check the returning code
// 
//      String payload = http.getString();   //Get the request response payload
//      Serial.println(payload);                     //Print the response payload
// 
//    }
// 
//    http.end();   //Close connection
// 
//  }
// 
//  delay(10000);    //Send a request every 30 seconds
// 
//}
