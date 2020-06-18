#include "Jogador.h"

Jogador ::Jogador(string nome, string posicao, int vlrAtaque, int vlrDefesa,
                  int vlrPasse, int habilidaeAdi, int pesoAtaque,
                  int pesoDefesa, int pesoPasse)
    : pesoAtaque(pesoAtaque),
      pesoDefesa(pesoDefesa),
      pesoPasse(pesoPasse),
      nome(nome),
      posicao(posicao) {
  this->vlrAtaque = vlrAtaque;
  this->vlrDefesa = vlrDefesa;
  this->vlrPasse = vlrPasse;
  this->habilidadeAdi = habilidadeAdi;
}

string Jogador ::getNome() { return this->nome; }

string Jogador ::getPosicao() { return this->posicao; }

Levantador ::Levantador(string nome, int vlrAtaque, int vlrDefesa, int vlrPasse,
                        int habilidadeAdi)
    : Jogador(nome, "levantador", vlrAtaque, vlrDefesa, vlrPasse, habilidadeAdi,
              1, 3, 6) {}

int Levantador ::getHabilidade() {
  return (this->vlrAtaque * pesoAtaque + this->vlrDefesa * pesoDefesa +
          this->vlrPasse * pesoPasse + 10 * habilidadeAdi);
}

Libero ::Libero(string nome, int vlrAtaque, int vlrDefesa, int vlrPasse,
                int habilidadeAdi)
    : Jogador(nome, "libero", vlrAtaque, vlrDefesa, vlrPasse, habilidadeAdi, 0,
              5, 5) {}

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

Meia ::Meia(string nome, int vlrAtaque, int vlrDefesa, int vlrPasse,
            int habilidadeAdi)
    : Jogador(nome, "meia", vlrAtaque, vlrDefesa, vlrPasse, habilidadeAdi, 4, 3,
              1) {}

int Meia ::getHabilidade() {
  return (this->vlrAtaque * pesoAtaque + this->vlrDefesa * pesoDefesa +
          this->vlrPasse * pesoPasse - habilidadeAdi);
}

Ponta ::Ponta(string nome, int vlrAtaque, int vlrDefesa, int vlrPasse,
              int habilidadeAdi)
    : Jogador(nome, "ponta", vlrAtaque, vlrDefesa, vlrPasse, habilidadeAdi, 4,
              3, 3) {}

int Ponta ::getHabilidade() {
  return (this->vlrAtaque * pesoAtaque + this->vlrDefesa * pesoDefesa +
          this->vlrPasse * pesoPasse);
}

Oposto ::Oposto(string nome, int vlrAtaque, int vlrDefesa, int vlrPasse,
                int habilidadeAdi)
    : Jogador(nome, "oposto", vlrAtaque, vlrDefesa, vlrPasse, habilidadeAdi, 6,
              3, 1) {}

int Oposto ::getHabilidade() {
  return (this->vlrAtaque * pesoAtaque + this->vlrDefesa * pesoDefesa +
          this->vlrPasse * pesoPasse + 20 * habilidadeAdi);
}
