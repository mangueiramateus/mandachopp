//Fazer TELA de consultando TAG
//Registrar na EEPROM quando o servidor falhar no momento critico
//Fazer requisição para armazenar no servidor e aguardar resposta
//Talvez se erro for igual a 3 resetar todo o ESP

#include "Display.h"
#include "Perifericos.h"
#include <TimerOne.h>

//INTERFACE
#define BRANCO 14
#define AMARELO 15
#define AZUL 16
#define VERDE 17

#define BUZZER 19
#define BTN 20

//CONTROLE DO FLUXO
#define SENSOR 2
#define VALVE 8
unsigned int pulsos = 0;
int volume = 0;
float fluxo = 0;
unsigned long int mililitros;
#define TIME_POLL 20
unsigned long int timer_delay;

void LEDon(byte led) {
  digitalWrite(led, HIGH);
}
void LEDoff(byte led) {
  digitalWrite(led, LOW);
}
void apitar(byte vezes, byte tempo) {
  int i = 0;
  while(1){
    digitalWrite(BUZZER, HIGH);
    delay(tempo);
    digitalWrite(BUZZER, LOW);
    i++;
    if (i == vezes) break;
    delay(tempo);
  }
}
void freeRam () {
  extern int __heap_start, *__brkval;
  int v;
  Serial.println("RAM: " + String((int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval)));
}

void setup() {
  Serial.begin(9600);
  //Inicializando entradas e saídas
  pinMode(BRANCO, OUTPUT);
  pinMode(AMARELO, OUTPUT);
  pinMode(AZUL, OUTPUT);
  pinMode(VERDE, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);
  pinMode(VALVE, OUTPUT);
  pinMode(SENSOR, INPUT);
  //Inicializando Interrupção interna
  Timer1.initialize(100000);
  Timer1.attachInterrupt( calculo );
  //Inicialização do sistema
  inicializar();
  //Inicia calibração
  LEDon(VERDE);
  calibrar();
  LEDoff(VERDE);
  Display.tela_inicial(Perifericos.VALOR, 1);
  //Prepara para a tela inicial
  Serial.println("TAG");
  freeRam();
  timer_delay = millis();
}
byte ERRO_COUNT;
bool existe = false;
String TAG = "";
void loop() {
  TAG = Perifericos.ler_TAG(BUZZER);
  //SE HOUVE UMA TAG ENCOSTADA
  if (TAG != "") {
    LEDoff(AZUL);
    apitar(1, 200);
    Serial.println(TAG);
    Display.tela_inicial(Perifericos.VALOR, 0);
    consulta();
    
    //VERIFICA SE A TAG EXISTE
    if (existe) { 
      Serial.println("FIND");
      Serial.println(Perifericos.user.nome);
      Serial.println(Perifericos.user.saldo);
      Serial.println(Perifericos.user.rank);
      Serial.println(Perifericos.user.litros);
      
      //VERIFICA SE HÁ SALDO
      if (Perifericos.user.saldo != 0) {
        //SE SIM ATIVA TORNEIRA E CONSUMO
        consumo();
        //VERIFICA SE ALGO FOI CONSUMIDO
        if (volume != 0) {
          atualiza();
        }
      }
      else {
        Display.tela_sem_saldo(Perifericos.user.nome, Perifericos.user.rank);
        delay(4000);
      }
    }
    else {
      Serial.println("NOT FIND");
      Display.tela_nao_encontrado();
      delay(2000);
    }
    freeRam();
    Display.tela_inicial(Perifericos.VALOR, 1);
    Serial.println(F("TAG"));
    timer_delay = millis();
  }

  
//CONSULTA DO SERVIDOR
  if ((millis() - timer_delay) > (TIME_POLL*1000)) {
    servidor();
    freeRam();
  }
}

void conta_vol() {
  pulsos++;
}
bool state = false;
void calculo() {
  noInterrupts();
  volume += pulsos;
  fluxo = pulsos;
  pulsos = 0;
  state = !state;
  digitalWrite(BRANCO, state);
  interrupts();
}

void inicializar(){
  //Inicializa display
  Serial.println("INI");
  Display.inicializar();
  //Perifericos.atualiza_litros(1250);
  Perifericos.obtem_litros();
  Serial.print("P/L: ");
  Serial.println(Perifericos.LITROS);
  
  byte ERRO_COUNT = 0;
  Perifericos.InicializarWifi();
  while (1) {
    //Inicializa WiFi
    Perifericos.Servidor();
    if (Perifericos.ERRO == 0) break;
    //Se gerou erro contabiliza
    ERRO_COUNT++;
    //Se houve 3 erros para o sistema e aguardao técnico
    if (ERRO_COUNT > 3) {
      Serial.println(F("RESET"));
      Display.tela_erro(Perifericos.ERRO);
      while (1);
    }
    //Imprime na serial o erro gerado
    Serial.print("ERRO " + String(ERRO_COUNT) + ": ");
    Serial.println(Perifericos.ERRO);
    //Liga o LED de ERRO
    LEDon(AMARELO);
    //Aguarda 5 s
    delay(5000);
  }
  apitar(2, 100);
  //Se saiu sem erro desliga o LED de ERRO
  LEDoff(AMARELO);
  LEDon(AZUL);
  //Inicializa RFID
  Serial.println(F("RFID"));
  Perifericos.InicializarRFID();
}
void calibrar(){
  long int tempo = millis();
  byte t_s, t_so = 0;
  const byte MAX = 4;
  //TELA INICIAL DE CALIBRAÇÃO
  while (1) {
    t_s = (millis() - tempo) / 1000;
    t_s = MAX - t_s;
    if (t_s != t_so) {
      t_so = t_s;
      Display.calibrar(0, t_s);
    }
    if (analogRead(BTN) < 100) break;
    if ((millis() - tempo) > 1000 * MAX) return;
    t_s = (millis() - tempo) / 1000;
  }
  while (analogRead(BTN) < 100);

  //TELA PARA ATIVAR VALVULA PARA SAIDA DO AR
  Display.calibrar(1, 0);
  delay(500);
  while (analogRead(BTN) > 100);
  while (analogRead(BTN) < 100);
  digitalWrite(VALVE, HIGH);

  //AGUARDA SAIR O AR DA TABULAÇÃO
  Display.calibrar(2, 0);
  delay(500);
  while (analogRead(BTN) > 100);
  while (analogRead(BTN) < 100);
  digitalWrite(VALVE, LOW);

  //AGUARDA PARA RETIRAR A CERVEJA PARA CALIBRAÇÃO
  Display.calibrar(3, 0);
  delay(500);
  while (analogRead(BTN) > 100);
  while (analogRead(BTN) < 100);
  digitalWrite(VALVE, HIGH);

  //AGUARDA FINALIZAR A SAIDA DE 1L DE CERVEJA
  Display.calibrar(4, 0);
  delay(500);
  attachInterrupt(0, conta_vol, RISING);
  while (analogRead(BTN) > 100){
    Serial.println("Pulsos: " + String(volume));
    Display.calibrar(4, volume);
    delay(300);
  }
  while (analogRead(BTN) < 100);
  digitalWrite(VALVE, LOW);
  detachInterrupt(0);
  Perifericos.atualiza_litros(volume);
  
}
void consulta(){
  existe = false;
  ERRO_COUNT = 0;
  //FAZ A CONSULTA NO SERVIDOR
  while (1) {
    if (ERRO_COUNT == 2) Perifericos.InicializarWifi(); //CASO A CONEXÃO FALHE 2 VEZES REINICIA MÓDULO
    existe = Perifericos.consultaTAG(TAG);
    if (Perifericos.ERRO == 0) break; // SE NÃO HOUVE NENHUM ERRO SAI
    ERRO_COUNT++; //SENÃO CONTABILIZA ERRO
    if (ERRO_COUNT == 3) { //CASO FALHE 3 VEZES TRAVA O SISTEMA E AGUARDA TÉCNICO
      LEDon(AMARELO);
      LEDoff(AZUL);
      Serial.println(F("RESET"));
      Display.tela_erro(Perifericos.ERRO);
      while (1);
    }
    Serial.print("ERRO " + String(ERRO_COUNT) + ": ");
    Serial.println(Perifericos.ERRO);
    delay(5000);
  }    
  LEDon(AZUL);
  LEDoff(AMARELO);
}
void consumo(){
  attachInterrupt(0, conta_vol, RISING);
  delay(500);
  volume = 0;
  fluxo = 0;
  pulsos = 0;
  digitalWrite(VALVE, HIGH);
  LEDon(VERDE);
  bool enchendo = false;
  unsigned long int tempo = millis();
  const byte MAX_WAIT = 10;
  byte t_s;
  //LOOP PARA USO DA TORNEIRA
  Serial.println("Vazao: " + String(fluxo));
  while (1) {
    if (fluxo == 0) {
      t_s = (millis() - tempo) / 1000;
      t_s = MAX_WAIT - t_s;
    }
    float tx = 1000.0/Perifericos.LITROS;
    mililitros = volume*tx;
    
    Display.tela_enchendo(t_s, mililitros, Perifericos.user.litros, Perifericos.user.nome, Perifericos.user.rank, Perifericos.user.saldo);
    if ((millis() - tempo) > 1000 * MAX_WAIT && fluxo == 0) break;
    if (fluxo != 0) enchendo = true;
    if (fluxo == 0 && enchendo) break; //finaliza se para de encher
    if (mililitros >= Perifericos.user.litros) break; //finaliza se não há mais saldo
    Serial.print("Vazao: ");
    Serial.print(fluxo);
    Serial.print(" | Volume: ");
    Serial.print(volume);
    Serial.print("/");
    Serial.println(mililitros);
    delay(100);
  }
  digitalWrite(VALVE, LOW);
  LEDoff(VERDE);
  detachInterrupt(0);
}
void atualiza(){
  Serial.print(F("Volume consumido(mL): "));
  Serial.println(mililitros);
  if (mililitros > Perifericos.user.litros) mililitros = Perifericos.user.litros;
  Perifericos.user.saldo -= (mililitros*Perifericos.VALOR)/1000;
  Serial.println("NOVO SALDO: " + String(Perifericos.user.saldo));
  Display.tela_finalizado(mililitros, Perifericos.user.saldo/100.0);
  ERRO_COUNT = 0;
  //LOOP PARA ATUALIZAR SERVIDOR
  while (1) {
    if (Perifericos.atualizarSaldo(Perifericos.user.saldo - volume, TAG)) break;
    freeRam();
    ERRO_COUNT++;
    if (ERRO_COUNT == 3) {
      LEDon(AMARELO);
      LEDoff(AZUL);
      Serial.println(F("RESET"));
      Display.tela_erro(Perifericos.ERRO);
      while (1);
    }
    Serial.print("ERRO " + String(ERRO_COUNT) + ": ");
    Serial.println(Perifericos.ERRO);
    delay(5000);
  }
  delay(3000);
}
void servidor(){
  LEDoff(AZUL);
  timer_delay = millis();
  ERRO_COUNT = 0;
  while (1) {
    //Inicializa WiFi
    Perifericos.Servidor();
    if (Perifericos.ERRO == 0) break;
    //Se gerou erro contabiliza
    ERRO_COUNT++;
    //Se houve 3 erros para o sistema e aguardao técnico
    if (ERRO_COUNT > 3) {
      
      Serial.println(F("RESET"));
      Display.tela_erro(Perifericos.ERRO);
      while (1);
    }
    //Imprime na serial o erro gerado
    Serial.print("ERRO " + String(ERRO_COUNT) + ": ");
    Serial.println(Perifericos.ERRO);
    //Liga o LED de ERRO
    LEDon(AMARELO);
    //Aguarda 5 s
    delay(5000);
  }
  Serial.println(Perifericos.VALOR);
  LEDon(AZUL);
}

