#ifndef JOGADOR_H
#define JOGADOR_H

#include <string>

using namespace std;

/* Classe base para os jogadores */ 

class Jogador {
 public:
  const int pesoAtaque, pesoDefesa, pesoPasse;
  const string posicao, nome;
  int vlrAtaque, vlrDefesa, vlrPasse, habilidadeAdi;
  Jogador(string nome, string posicao, int vlrAtaque, int vlrDefesa,
          int vlrPasse, int habilidadeAdi, int pesoAtaque, int pesoDefesa,
          int pesoPasse);
  string getNome();
  string getPosicao();
  virtual int getHabilidade() = 0;
};

class Levantador : public Jogador {
 public:
  Levantador(string nome, int vlrAtaque, int vlrDefesa, int vlrPasse,
             int habilidadeAdi);
  int getHabilidade();
};

class Libero : public Jogador {
 public:
  Libero(string nome, int vlrAtaque, int vlrDefesa, int vlrPasse,
         int habilidadeAdi);
  int getHabilidade();
};

class Meia : public Jogador {
 public:
  Meia(string nome, int vlrAtaque, int vlrDefesa, int vlrPasse,
       int habilidadeAdi);
  int getHabilidade();
};

class Ponta : public Jogador {
 public:
  Ponta(string nome, int vlrAtaque, int vlrDefesa, int vlrPasse,
        int habilidadeAdi);
  int getHabilidade();
};

class Oposto : public Jogador {
 public:
  Oposto(string nome, int vlrAtaque, int vlrDefesa, int vlrPasse,
         int habilidadeAdi);
  int getHabilidade();
};

#endif
