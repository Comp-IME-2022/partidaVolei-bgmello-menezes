#include "Time.h"

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

Time ::Time(string nomeTime) {
  this->nomeTime = nomeTime;
  jogadores.clear();
  tipoJogadores.clear();
}

string Time ::getNome() { return this->nomeTime; }

bool Time ::isValid() {
  if (tipoJogadores["levantador"] != 1 or tipoJogadores["libero"] != 1 or
      tipoJogadores["oposto"] != 1 or tipoJogadores["meia"] != 2 or
      tipoJogadores["ponta"] != 2)
    return false;
  return true;
}

int Time ::getHabilidadeTotal() {
  if (!this->isValid()) {
    return -1;
  }
  int sumHab = 0;
  for (int i = 0; i < 7; ++i) sumHab += jogadores[i]->getHabilidade();
  return sumHab;
}

bool Time ::addJogador(string nome, string posicao, int vlrAtaque,
                       int vlrDefesa, int vlrPasse, int habilidadeAdi) {
  if ((int)jogadores.size() == 7) {
    if (this->isValid()) {
      return true;
    }
    return false;
  }
  tipoJogadores[posicao]++;
  if (posicao == "levantador") {
    jogadores.push_back(unique_ptr<Jogador>(
        new Levantador(nome, vlrAtaque, vlrDefesa, vlrPasse, habilidadeAdi)));
    return true;
  }
  if (posicao == "libero") {
    jogadores.push_back(unique_ptr<Jogador>(
        new Libero(nome, vlrAtaque, vlrDefesa, vlrPasse, habilidadeAdi)));
    return true;
  }
  if (posicao == "meia") {
    jogadores.push_back(unique_ptr<Jogador>(
        new Meia(nome, vlrAtaque, vlrDefesa, vlrPasse, habilidadeAdi)));
    return true;
  }
  if (posicao == "ponta") {
    jogadores.push_back(unique_ptr<Jogador>(
        new Ponta(nome, vlrAtaque, vlrDefesa, vlrPasse, 0)));
    return true;
  }
  if (posicao == "oposto") {
    jogadores.push_back(unique_ptr<Jogador>(
        new Oposto(nome, vlrAtaque, vlrDefesa, vlrPasse, habilidadeAdi)));
    return true;
  }
  return false;
}

bool Time ::removeJogador(string nome) {
  for (int i = 0; i < (int)jogadores.size(); ++i) {
    if (jogadores[i]->nome == nome) {
      tipoJogadores[jogadores[i]->posicao]--;
      jogadores.erase(jogadores.begin() + i);
      return true;
    }
  }
  return false;
}

void Time ::printJogadores() {
  if ((int)jogadores.size() == 0) {
    cout << "Nao ha jogadores nesse time\n\n";
    return;
  }
  for (int i = 0; i < (int)jogadores.size(); ++i) {
    cout << "Os jogadores do time sao\n\n";
    cout << jogadores[i]->nome << "\n";
    cout << "Informacoes\n";
    cout << "Posicao: " << jogadores[i]->posicao << "\n";
    cout << "Valor ataque: " << jogadores[i]->vlrAtaque << "\n";
    cout << "Valor defesa: " << jogadores[i]->vlrDefesa << "\n";
    cout << "Valor passe: " << jogadores[i]->vlrPasse << "\n";
    cout << "Habilidade total: " << jogadores[i]->getHabilidade() << "\n\n";
  }
  return;
}
