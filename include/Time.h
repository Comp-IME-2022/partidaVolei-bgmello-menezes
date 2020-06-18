#ifndef TIME_H
#define TIME_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Jogador.h"
using namespace std;

/* Classe do time */

class Time {
 public:
  vector<unique_ptr<Jogador>> jogadores;
  map<string, int> tipoJogadores;
  string nomeTime;
  Time(string nomeTime);
  int getHabilidadeTotal();
  string getNome();
  bool isValid();
  bool addJogador(string nome, string posicao, int vlrAtaque, int vlrDefesa,
                  int vlrPasse, int habilidadeAdi);
  bool removeJogador(string nome);
  void printJogadores();
};

#endif
