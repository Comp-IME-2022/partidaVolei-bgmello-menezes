#ifndef TIME_H
#define TIME_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Jogador.h"
using namespace std;

/** Classe do time */

class Time {
 public:
  vector<unique_ptr<Jogador>> jogadores;
  map<string, int> tipoJogadores;
  string nomeTime;
  Time(const Time&);
  Time(string nomeTime);
  int getHabilidadeTotal();

  /** Retorna o nome do time */
  inline string getNome() const { return this->nomeTime; }

  bool isValid();
  bool addJogador(string nome, string posicao, int vlrAtaque, int vlrDefesa,
                  int vlrPasse, int habilidadeAdi);
  bool removeJogador(string nome);
  friend ostream& operator<<(ostream&, const Time&);
};

#endif
