#include <Partida.h>

#include <iomanip>
#include <sstream>
#include <string>

inline double Partida::randd() {
  return (double)rand() / ((double)RAND_MAX + 1);
}

Partida::Partida(std::string nomeA, std::string nomeB)
    : timeA(nomeA), timeB(nomeB) {
  this->pointsA = this->pointsB = 0;
  this->setsA = this->setsB = 0;
  this->sacadorA = true;
  this->ended = false;
}

bool Partida::addJogador(string nomeTime, string nomeJogador, string posicao,
                         int vlrAtaque, int vlrDefesa, int vlrPasse,
                         int habilidadeAdi) {
  if (nomeTime == this->timeA.getNome()) {
    return this->timeA.addJogador(nomeJogador, posicao, vlrAtaque, vlrDefesa,
                                  vlrPasse, habilidadeAdi);
  }

  else if (nomeTime == this->timeB.getNome()) {
    return this->timeB.addJogador(nomeJogador, posicao, vlrAtaque, vlrDefesa,
                                  vlrPasse, habilidadeAdi);
  }

  return false;
}

bool Partida::removeJogador(string nomeTime, string nomeJogador) {
  if (nomeTime == this->timeA.getNome()) {
    return this->timeA.removeJogador(nomeJogador);
  }

  else if (nomeTime == this->timeB.getNome()) {
    return this->timeB.removeJogador(nomeJogador);
  }

  return false;
}

bool Partida::timeIsValid(string nomeTime) {
  if (nomeTime == this->timeA.getNome()) {
    return this->timeA.isValid();
  }

  else if (nomeTime == this->timeB.getNome()) {
    return this->timeB.isValid();
  }

  return false;
}

bool Partida::resetPartida() {
  this->setsA = 0;
  this->setsB = 0;
  this->pointsA = 0;
  this->pointsB = 0;
  this->sacadorA = true;
  this->ended = false;
  return true;
}

bool Partida::playPoint() {
  string ganhador("");

  if (not this->timeA.isValid() or not this->timeB.isValid())
    cout << "Algum dos times inválido!" << endl;

  double habilidadeA = this->timeA.getHabilidadeTotal();
  double habilidadeB = this->timeB.getHabilidadeTotal();
  double probA(0.0);

  if (this->sacadorA)
    probA = habilidadeA * 1.25 / (habilidadeA * 1.25 + habilidadeB);

  else
    probA = habilidadeA / (habilidadeA + habilidadeB * 1.25);

  ganhador =
      this->randd() < probA ? this->timeA.getNome() : this->timeB.getNome();

  this->sacadorA = ganhador == this->timeA.getNome();

  this->ended = this->addPoint(ganhador);

  return this->ended;
}

bool Partida::addPoint(string nomeTime) {
  if (this->ended) return true;

  bool ended = this->setsA == 3 or this->setsB == 3;
  if (ended) return true;

  int pointLimit = this->setsA + this->setsB != 4 ? 24 : 14;

  if (nomeTime == this->timeA.getNome()) {
    if (this->pointsA < pointLimit)
      this->pointsA++;
    else {
      if (this->pointsA <= this->pointsB)
        this->pointsA++;
      else {
        this->setsA++, this->pointsA = 0, this->pointsB = 0;
        if (this->setsA == 3) ended = true;
      }
    }
  }

  if (nomeTime == this->timeB.getNome()) {
    if (this->pointsB < pointLimit)
      this->pointsB++;
    else {
      if (this->pointsB <= this->pointsA)
        this->pointsB++;
      else {
        this->setsB++, this->pointsA = 0, this->pointsB = 0;
        if (this->setsB == 3) ended = true;
      }
    }
  }

  return ended;
}

string Partida::showPlacar() {
  stringstream placar;

  placar << setw(11) << "Nome do Time\t\tSets\t\tPontos\t\tSacando" << endl;
  placar << setw(11) << this->timeA.getNome() << "\t\t" << this->setsA << "\t\t"
         << this->pointsA << "\t\t" << (this->sacadorA ? "*" : "") << endl;
  placar << setw(11) << this->timeB.getNome() << "\t\t" << this->setsB << "\t\t"
         << this->pointsB << "\t\t" << (this->sacadorA ? "" : "*") << endl;

  return placar.str();
}
