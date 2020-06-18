#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <string>

#include "Time.h"

using namespace std;

class Partida {
  Time timeA, timeB;
  bool sacadorA, ended;
  int pointsA, pointsB;
  int setsA, setsB;

  inline double randd();

  bool addPoint(string nomeTime);

  bool timeIsValid(string nomeTime);

 public:
  Partida(string nomeA, string nomeB);

  bool addJogador(string nomeTime, string nomeJogador, string posicao,
                  int vlrAtaque, int vlrDefesa, int vlrPasse,
                  int habilidadeAdi);

  bool removeJogador(string nomeTime, string nomeJogador);

  bool playPoint();

  bool resetPartida();

  void printJogadores(string nomeTime);

  string showPlacar();
};
