#ifndef JOGADOR_H
#define JOGADOR_H

#include <memory>
#include <string>

using namespace std;

/** Classe base para os jogadores */

class Jogador {
 protected:
  const int pesoAtaque, pesoDefesa, pesoPasse;
  const string nome, posicao;
  int vlrAtaque, vlrDefesa, vlrPasse, habilidadeAdi;

 public:
  Jogador(string nome, string posicao, int vlrAtaque, int vlrDefesa,
          int vlrPasse, int habilidadeAdi, int pesoAtaque, int pesoDefesa,
          int pesoPasse);

  /** Retorna o nome do jogador */
  inline string getNome() { return this->nome; }

  /** Retorna a posicao do jogador */
  inline string getPosicao() { return this->posicao; }

  /** Retorna o valor de ataque do jogador */
  inline int getvlrAtaque() { return this->vlrAtaque; }

  /** Retorna o valor de defesa do jogador */
  inline int getvlrDefesa() { return this->vlrDefesa; }

  /** Retorna o valor de passe do jogador */
  inline int getvlrPasse() { return this->vlrPasse; }

  virtual int getHabilidade() = 0;
  virtual unique_ptr<Jogador> clone() = 0;
  virtual ~Jogador() = 0;
};

/** Classes derivadas para cada posição */

class Levantador : public Jogador {
 public:
  Levantador(string nome, int vlrAtaque, int vlrDefesa, int vlrPasse,
             int habilidadeAdi);
  int getHabilidade();

  unique_ptr<Jogador> clone() {
    return unique_ptr<Jogador>(new Levantador(*this));
  }
};

class Libero : public Jogador {
 public:
  Libero(string nome, int vlrAtaque, int vlrDefesa, int vlrPasse,
         int habilidadeAdi);
  int getHabilidade();
  unique_ptr<Jogador> clone() { return unique_ptr<Jogador>(new Libero(*this)); }
};

class Meia : public Jogador {
 public:
  Meia(string nome, int vlrAtaque, int vlrDefesa, int vlrPasse,
       int habilidadeAdi);
  int getHabilidade();
  unique_ptr<Jogador> clone() { return unique_ptr<Jogador>(new Meia(*this)); }
};

class Ponta : public Jogador {
 public:
  Ponta(string nome, int vlrAtaque, int vlrDefesa, int vlrPasse,
        int habilidadeAdi);
  int getHabilidade();
  unique_ptr<Jogador> clone() { return unique_ptr<Jogador>(new Ponta(*this)); }
};

class Oposto : public Jogador {
 public:
  Oposto(string nome, int vlrAtaque, int vlrDefesa, int vlrPasse,
         int habilidadeAdi);
  int getHabilidade();
  unique_ptr<Jogador> clone() { return unique_ptr<Jogador>(new Oposto(*this)); }
};

#endif
