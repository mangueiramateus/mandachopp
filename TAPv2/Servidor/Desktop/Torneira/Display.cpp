#include "Display.h"

#include <U8glib.h>   //Display Gráfico 128x64
#define ENABLE 7
#define RW 6
#define RS 5

#define fonte_maior u8g_font_osb18r
//#define fonte_menor u8g_font_courB12r
#define fonte_menor u8g_font_6x10r

U8GLIB_ST7920_128X64_1X u8g(ENABLE, RW, RS);

void DisplayClass::inicializar() {
  u8g.setFont(fonte_maior);                   //aqui
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();

  u8g.firstPage();
  while ( u8g.nextPage() ) {
    u8g.drawStr( 0, 10, "CERVEJA");
    //taça
    u8g.drawLine(43, 49, 43, 59);
    u8g.drawLine(44, 60, 45, 61);
    u8g.drawLine(46, 62, 50, 62);
    u8g.drawLine(51, 61, 52, 60);
    u8g.drawLine(53, 59, 53, 49);
    u8g.drawLine(53, 48, 43, 48);
    u8g.drawLine(54, 50, 55, 51);
    u8g.drawLine(56, 52, 56, 54);
    u8g.drawLine(55, 55, 54, 56);
    u8g.drawLine(45, 50, 45, 58);
    u8g.drawLine(48, 50, 48, 58);
    u8g.drawLine(51, 50, 51, 58);
    u8g.drawFilledEllipse(43, 46, 2, 2);
    u8g.drawFilledEllipse(53, 46, 2, 2);
    u8g.drawFilledEllipse(47, 44, 4, 4);
    u8g.drawFilledEllipse(51, 43, 2, 2);

    //garrafa
    u8g.drawEllipse(64, 35, 2, 1);
    u8g.drawLine(62, 36, 62, 40);
    u8g.drawLine(66, 36, 66, 40);
    u8g.drawLine(61, 41, 60, 42);
    u8g.drawLine(67, 41, 68, 42);
    u8g.drawLine(59, 43, 59, 61);
    u8g.drawLine(69, 43, 69, 61);
    u8g.drawLine(60, 61, 68, 61);
    u8g.drawLine(61, 44, 61, 59);
  }
}

void DisplayClass::calibrar(byte state, int t_s) {
  //TELA INCICIAL DA CALIBRAÇÃO  
  if (state == 0){
    u8g.firstPage();
    while ( u8g.nextPage() ) {
      u8g.setFont(fonte_menor);
      u8g.setFontPosTop();
      u8g.drawStr( 10, 10, "CALIBRANDO");

      u8g.setFont(fonte_menor);
      u8g.setFontPosTop();
      u8g.drawStr(13, 25, "Pressione o botao");
      u8g.drawStr(22, 33, "para iniciar a");
      u8g.drawStr(1, 41, "calibracao ou aguarde");
      drawInt(20, 53, t_s);
    }
  }
  else if (state == 1){
    u8g.firstPage();
    while ( u8g.nextPage() ) {
      u8g.setFont(fonte_menor);
      u8g.setFontPosTop();
      u8g.drawStr( 10, 10, "CALIBRANDO");
  
      u8g.setFont(fonte_menor);
      u8g.setFontPosTop();
      u8g.drawStr(13, 25, "Pressione o botao");
      u8g.drawStr(19, 33, "para iniciar a ");
      u8g.drawStr(31, 41, "saida de ar");
    }
  }
  else if (state == 2){
    u8g.firstPage();
    while ( u8g.nextPage() ) {
      u8g.setFont(fonte_menor);
      u8g.setFontPosTop();
      u8g.drawStr( 10, 10, "CALIBRANDO");
  
      u8g.setFont(fonte_menor);
      u8g.setFontPosTop();
      u8g.drawStr(8, 25, "Pressione o botao");
      u8g.drawStr(20, 33, "fechar a valvula");
    }
  }
  else if (state == 3){
    u8g.firstPage();
    while ( u8g.nextPage() ) {
      u8g.setFont(fonte_menor);
      u8g.setFontPosTop();
      u8g.drawStr( 10, 10, "CALIBRANDO");
  
      u8g.setFont(fonte_menor);
      u8g.setFontPosTop();
      u8g.drawStr(8, 25, "Pressione o botao");
      u8g.drawStr(3, 33, "para saida da cerveja");
      u8g.drawStr(8, 53, "Volume esperado: 1L");
    }
  }
  else if (state == 4){
    u8g.firstPage();
    while ( u8g.nextPage() ) {
      u8g.setFont(fonte_menor);
      u8g.setFontPosTop();
      u8g.drawStr( 10, 10, "CALIBRANDO");
  
      u8g.setFont(fonte_menor);
      u8g.setFontPosTop();
      u8g.drawStr(8, 25, "Pressione o botao");
      u8g.drawStr(20, 33, "para finalizar");
      u8g.drawStr(8, 53, "Pulsos:");
      drawInt(56, 53, t_s);
    }
  }
}

void DisplayClass::tela_inicial(int preco, bool state) {
  u8g.firstPage();
  while ( u8g.nextPage() ) {
    u8g.setFont(fonte_maior);
    u8g.setFontPosTop();
    u8g.drawStr( 0, 10, "CERVEJA");
    u8g.setFont(fonte_menor);
    u8g.setFontPosTop();
    if (state) u8g.drawStr( 0, 38, "ENCOSTE A TAG");
    else u8g.drawStr( 0, 38, "CONSULTANDO...");
    u8g.drawStr( 0, 54, "PRECO:");
    float a = preco/100.0;
    drawFloat(42, 54, a);
  }
}

void DisplayClass::tela_enchendo(byte tempo, unsigned long volume, unsigned long saldo, String nome, int rank, int preco) {
  char buff[nome.length() + 1];
  nome.toCharArray(buff, nome.length() + 1);
  u8g.firstPage();
  while ( u8g.nextPage() ) {
    u8g.setFont(fonte_menor);
    u8g.setFontPosTop();

    u8g.drawStr( 0, 8, "USUARIO:");
    
    u8g.drawStr( 10, 16, "NOME:");
    u8g.drawStr( 46, 16, buff);

    u8g.drawStr( 10, 24, "RANK:");
    drawInt( 46, 24, rank);

    u8g.drawStr( 10, 32, "SALDO(R$):");
    float a = preco/100.0;
    drawFloat(76, 32, a);    
    
    u8g.drawStr( 10, 40, "(mL):");
    byte d = drawInt( 52, 40, volume);
    u8g.drawStr( 52+d*6, 40, "/");
    drawInt( 58+d*6, 40, saldo);
    
    u8g.drawStr( 10, 56, "TEMPO:");
    drawInt( 52, 56, tempo);
  }
}

void DisplayClass::tela_finalizado(float volume, float saldo){
  u8g.firstPage();
  while ( u8g.nextPage() ) {
    u8g.setFont(fonte_menor);
    u8g.setFontPosTop();
    u8g.drawStr( 0, 8, "SALVANDO DADOS");
    u8g.drawStr( 8, 24, "VOLUME CONSUMIDO:");
    byte d = drawFloat( 14, 32, volume);
    u8g.drawStr( 20+d*6, 32, F("mL"));
    u8g.drawStr( 8, 40, "NOVO SALDO:");
    drawFloat(74, 40, saldo);
  }
}

void DisplayClass::tela_sem_saldo(String nome, int rank){
  char buff[nome.length() + 1];
  nome.toCharArray(buff, nome.length() + 1);
  u8g.firstPage();
  while ( u8g.nextPage() ) {
    u8g.setFont(fonte_menor);
    u8g.setFontPosTop();
    u8g.drawStr( 0, 10, "CERVEJA");
    u8g.setFont(fonte_menor);
    u8g.setFontPosTop();
    u8g.drawStr( 10, 25, "NOME:");
    u8g.drawStr( 46, 25, buff);
    u8g.drawStr( 10, 33, "SEM SALDO!");
    u8g.drawStr( 10, 41, "RANK:");
    drawInt( 46, 41, rank);
  }
}

void DisplayClass::tela_nao_encontrado(){
  u8g.firstPage();
  while ( u8g.nextPage() ) {
    u8g.setFont(fonte_menor);
    u8g.setFontPosTop();
    u8g.drawStr( 13, 25, "CADASTRO NAO ESTA");
    u8g.drawStr( 13, 33, "NO BANCO DE DADOS");
  }
}

void DisplayClass::tela_erro(byte erro) {
  u8g.firstPage();
  while ( u8g.nextPage() ) {
    u8g.setFont(fonte_menor);
    u8g.setFontPosTop();
    u8g.drawStr( 0, 10, "ERRO SISTEMA");
    u8g.setFont(fonte_menor);
    u8g.setFontPosTop();
    u8g.drawStr( 0, 25, "PROBLEMA:");
    if (erro == 1) u8g.drawStr( 20, 33, "MODULO WIFI");
    else if (erro == 2) u8g.drawStr( 20, 33, "REDE WIFI");
    else if (erro == 3) u8g.drawStr( 20, 33, "SERVIDOR");
    else if (erro == 4) u8g.drawStr( 20, 33, "BUSCA DE TAG");
    else if (erro == 4) u8g.drawStr( 20, 33, "UPDATE DE TAG");
  }
}

byte DisplayClass::drawInt(int x, int y, unsigned long num) {
  String aux = String(num);
  char buff[aux.length() + 1];
  aux.toCharArray(buff, aux.length() + 1);
  u8g.drawStr( x, y, buff);
  return aux.length();
}

byte DisplayClass::drawFloat(int x, int y, float num) {
  String aux = String(num);
  char buff[aux.length() + 1];
  aux.toCharArray(buff, aux.length() + 1);
  u8g.drawStr( x, y, buff);
  return aux.length();
}




//void DisplayClass::calibrar(byte btn, byte VALVE) {
//  //TELA INCICIAL DA CALIBRAÇÃO
//  long int tempo = millis();
//  byte t_s, t_so = 0;
//  const byte MAX = 4;
//  while (1) {
//    t_s = (millis() - tempo) / 1000;
//    t_s = MAX - t_s;
//    if (t_s != t_so) {
//      t_so = t_s;
//      u8g.firstPage();
//      while ( u8g.nextPage() ) {
//        u8g.setFont(fonte_menor);
//        u8g.setFontPosTop();
//        u8g.drawStr( 10, 10, "CALIBRANDO");
//
//        u8g.setFont(fonte_menor);
//        u8g.setFontPosTop();
//        u8g.drawStr(13, 25, "Pressione o botao");
//        u8g.drawStr(22, 33, "para iniciar a");
//        u8g.drawStr(1, 41, "calibracao ou aguarde");
//        drawInt(20, 53, t_s);
//      }
//    }
//
//    if (analogRead(btn) < 100) break;
//    if ((millis() - tempo) > 1000 * MAX) return;
//    t_s = (millis() - tempo) / 1000;
//  }
//  while (analogRead(btn) < 100);
//
//  u8g.firstPage();
//  while ( u8g.nextPage() ) {
//    u8g.setFont(fonte_menor);
//    u8g.setFontPosTop();
//    u8g.drawStr( 10, 10, "CALIBRANDO");
//
//    u8g.setFont(fonte_menor);
//    u8g.setFontPosTop();
//    u8g.drawStr(13, 25, "Pressione o botao");
//    u8g.drawStr(19, 33, "para iniciar a ");
//    u8g.drawStr(31, 41, "saida de ar");
//  }
//  delay(500);
//  while (analogRead(btn) > 100);
//  while (analogRead(btn) < 100);
//  digitalWrite(VALVE, HIGH);
//
//  //AGUARDA SAIR O AR DA TABULAÇÃO
//  u8g.firstPage();
//  while ( u8g.nextPage() ) {
//    u8g.setFont(fonte_menor);
//    u8g.setFontPosTop();
//    u8g.drawStr( 10, 10, "CALIBRANDO");
//
//    u8g.setFont(fonte_menor);
//    u8g.setFontPosTop();
//    u8g.drawStr(8, 25, "Pressione o botao");
//    u8g.drawStr(20, 33, "fechar a valvula");
//  }
//  delay(500);
//  while (analogRead(btn) > 100);
//  while (analogRead(btn) < 100);
//  digitalWrite(VALVE, LOW);
//
//  //AGUARDA PARA RETIRAR A CERVEJA PARA CALIBRAÇÃO
//  u8g.firstPage();
//  while ( u8g.nextPage() ) {
//    u8g.setFont(fonte_menor);
//    u8g.setFontPosTop();
//    u8g.drawStr( 10, 10, "CALIBRANDO");
//
//    u8g.setFont(fonte_menor);
//    u8g.setFontPosTop();
//    u8g.drawStr(8, 25, "Pressione o botao");
//    u8g.drawStr(3, 33, "para saida da cerveja");
//    u8g.drawStr(8, 53, "Volume esperado: 1L");
//  }
//  delay(500);
//  while (analogRead(btn) > 100);
//  while (analogRead(btn) < 100);
//  digitalWrite(VALVE, HIGH);
//
//  //AGUARDA FINALIZAR A SAIDA DE 1L DE CERVEJA
//  u8g.firstPage();
//  while ( u8g.nextPage() ) {
//    u8g.setFont(fonte_menor);
//    u8g.setFontPosTop();
//    u8g.drawStr( 10, 10, "CALIBRANDO");
//
//    u8g.setFont(fonte_menor);
//    u8g.setFontPosTop();
//    u8g.drawStr(8, 25, "Pressione o botao");
//    u8g.drawStr(20, 33, "para finalizar");
//  }
//  delay(500);
//  while (analogRead(btn) > 100);
//  while (analogRead(btn) < 100);
//  digitalWrite(VALVE, LOW);
//}
