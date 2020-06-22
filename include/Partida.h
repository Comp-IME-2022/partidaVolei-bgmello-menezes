#ifndef PARTIDA_H
#define PARTIDA_H

#include <iostream>
#include <string>
#include <vector>

#include "Time.h"

using namespace std;
/**
 * Implementacao da classe Partida
 *
 * Nesta classe temos dois times e podemos jogar uma partida de Volei utilizando
 * as habilidades dos times por meio de um modelo probabilistico.
 *
 * Para podermos jogar o jogo os dois times devem ser validos.
 *
 * A partida pode ser reinicidada utilizando o metodo resetPartida
 *
 * Podemos acompanhar a evolucao do jogo por meio do metodo showPlacar
 *
 * Para visualizarmos os jogadores dos times utilizamos o metodo printJogadores
 */
class Partida {
  Time timeA, timeB;
  bool primeiroSacadorA, sacadorA, ended;
  int pointsA, pointsB;
  int numSetsA, numSetsB;
  vector<int> setsA, setsB;

  inline double randd();

  bool addPoint(string nomeTime);

  bool timeIsValid(string nomeTime);

 public:
  Partida(const Time&, const Time&, bool sacadorA);

  Partida(string nomeA, string nomeB, bool sacadorA);

  bool isEnded();

  bool addJogador(string nomeTime, string nomeJogador, string posicao,
                  int vlrAtaque, int vlrDefesa, int vlrPasse,
                  int habilidadeAdi);

  bool removeJogador(string nomeTime, string nomeJogador);

  bool playPoint();

  bool resetPartida();

  void printJogadores(ostream& o, string nomeTime);

  friend ostream& operator<<(ostream& o, const Partida& partida);
};

#endif
