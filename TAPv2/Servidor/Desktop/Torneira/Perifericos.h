#ifndef PERIFERICOS_H
#define PERIFERICOS_H
#include <Arduino.h>

struct stru_usuario {
  String nome;
  unsigned long int saldo;
  int rank;
  unsigned long int litros;
};

class PerifericosClass {
public:

  struct stru_usuario user;
  byte ERRO;
  int VALOR;
  int LITROS;
  
  void InicializarRFID();
  String ler_TAG(byte BUZZER);
  void InicializarWifi();
  void Servidor();
  bool consultaTAG(String TAG);
  bool atualizarSaldo(int Saldo, String TAG);
  void obtem_litros();
  void atualiza_litros(int litros);
  
  void enviar_comando(String cmd, long int timeout);
};

static PerifericosClass Perifericos;

#endif
