#ifndef DISPLAY_H
#define DISPLAY_H
#include <Arduino.h>

class DisplayClass{
  public:

  void inicializar();
  void calibrar(byte state, int t_s);
  void tela_inicial(int preco, bool state);
  void tela_enchendo(byte tempo, unsigned long volume, unsigned long saldo, String nome, int rank, int preco);
  void tela_finalizado(float volume, float saldo);
  void tela_sem_saldo(String nome, int rank);
  void tela_nao_encontrado();
  void tela_erro(byte erro);

  byte drawInt(int x, int y, unsigned long num);
  byte drawFloat(int x, int y, float num);
};

static DisplayClass Display;

#endif
