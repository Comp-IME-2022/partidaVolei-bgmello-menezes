#include "Jogador.h"



Jogador ::Jogador(string nome, string posicao, int vlrAtaque, int vlrDefesa,
                  int vlrPasse, int habilidaeAdi, int pesoAtaque,
                  int pesoDefesa, int pesoPasse)
    : pesoAtaque(pesoAtaque),
      pesoDefesa(pesoDefesa),
      pesoPasse(pesoPasse),
      nome(nome),
      posicao(posicao) {
/* Construtor da classe jogador */
 
  this->vlrAtaque = vlrAtaque;
  this->vlrDefesa = vlrDefesa;
  this->vlrPasse = vlrPasse;
  this->habilidadeAdi = habilidadeAdi;
}

/* Retorna o nome do jogador */
string Jogador ::getNome() { return this->nome; }

/* Retorna a posicao do jogador */
string Jogador ::getPosicao() { return this->posicao; }

/* Construtor da classe derivada Levantador */
Levantador ::Levantador(string nome, int vlrAtaque, int vlrDefesa, int vlrPasse,
                        int habilidadeAdi)
    : Jogador(nome, "levantador", vlrAtaque, vlrDefesa, vlrPasse, habilidadeAdi,
              1, 3, 6) {}

/* Retorna a habilidade do levantador */
int Levantador ::getHabilidade() {
  return (this->vlrAtaque * pesoAtaque + this->vlrDefesa * pesoDefesa +
          this->vlrPasse * pesoPasse + 10 * habilidadeAdi);
}

/* Construtor da classe derivada Libero */
Libero ::Libero(string nome, int vlrAtaque, int vlrDefesa, int vlrPasse,
                int habilidadeAdi)
    : Jogador(nome, "libero", vlrAtaque, vlrDefesa, vlrPasse, habilidadeAdi, 0,
              5, 5) {}

/* Retorna a habilidade do libero */
int Libero ::getHabilidade() {
  if (habilidadeAdi >= 10) {
    habilidadeAdi /= 10;
    return ((this->vlrAtaque * pesoAtaque + this->vlrDefesa * pesoDefesa +
             this->vlrPasse * pesoPasse) *
            (2 * habilidadeAdi));
  }
  return this->vlrAtaque * pesoAtaque + this->vlrDefesa * pesoDefesa +
         this->vlrPasse * pesoPasse;
}

/* Construtor da classe derivada Meia*/
Meia ::Meia(string nome, int vlrAtaque, int vlrDefesa, int vlrPasse,
            int habilidadeAdi)
    : Jogador(nome, "meia", vlrAtaque, vlrDefesa, vlrPasse, habilidadeAdi, 4, 3,
              1) {}
              
/* Retorna a habilidade do meia */
int Meia ::getHabilidade() {
  return (this->vlrAtaque * pesoAtaque + this->vlrDefesa * pesoDefesa +
          this->vlrPasse * pesoPasse - habilidadeAdi);
}

/* Construtor da classe derivada Ponta */
Ponta ::Ponta(string nome, int vlrAtaque, int vlrDefesa, int vlrPasse,
              int habilidadeAdi)
    : Jogador(nome, "ponta", vlrAtaque, vlrDefesa, vlrPasse, habilidadeAdi, 4,
              3, 3) {}
              
/* Retorna a habilidade do ponta */
int Ponta ::getHabilidade() {
  return (this->vlrAtaque * pesoAtaque + this->vlrDefesa * pesoDefesa +
          this->vlrPasse * pesoPasse);
}

/* Construtor da classe derivada Oposto */
Oposto ::Oposto(string nome, int vlrAtaque, int vlrDefesa, int vlrPasse,
                int habilidadeAdi)
    : Jogador(nome, "oposto", vlrAtaque, vlrDefesa, vlrPasse, habilidadeAdi, 6,
              3, 1) {}
              
/* Retorna a habilidade do oposto */
int Oposto ::getHabilidade() {
  return (this->vlrAtaque * pesoAtaque + this->vlrDefesa * pesoDefesa +
          this->vlrPasse * pesoPasse + 20 * habilidadeAdi);
}
