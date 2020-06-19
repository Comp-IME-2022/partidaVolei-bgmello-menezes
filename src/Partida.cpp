#include <Partida.h>

#include <iomanip>
#include <sstream>
#include <string>

inline double Partida::randd() {
  return (double)rand() / ((double)RAND_MAX + 1);
}

Partida::Partida(const Time& timeA, const Time& timeB, bool sacadorA)
    : timeA(timeA),
      timeB(timeB),
      sacadorA(sacadorA),
      primeiroSacadorA(sacadorA) {
  this->pointsA = this->pointsB = 0;
  this->setsA.clear();
  this->setsB.clear();
  this->numSetsA = this->numSetsB = 0;
  this->ended = false;
}

Partida::Partida(std::string nomeA, std::string nomeB, bool sacadorA)
    : timeA(nomeA), timeB(nomeB) {
  this->pointsA = this->pointsB = 0;
  this->setsA.clear();
  this->setsB.clear();
  this->numSetsA = this->numSetsB = 0;
  this->sacadorA = this->primeiroSacadorA = sacadorA;
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
  this->setsA.clear();
  this->setsB.clear();
  this->numSetsA = this->numSetsB = 0;
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

  if (this->addPoint(ganhador))
    this->sacadorA =
        ((int)this->primeiroSacadorA + this->setsA.size()) % 2 == 0;
  else
    this->sacadorA = ganhador == this->timeA.getNome();

  return this->ended;
}

bool Partida::isEnded() { return this->ended; }

bool Partida::addPoint(string nomeTime) {
  if (this->ended) return true;

  bool swapSet = false;
  bool ended = this->numSetsA == 3 or this->numSetsB == 3;
  if (ended) return true;

  int pointLimit = this->numSetsA + this->numSetsB != 4 ? 25 : 15;

  if (nomeTime == this->timeA.getNome()) {
    if (this->pointsA < pointLimit - 1)
      this->pointsA++;
    else {
      if (this->pointsA <= this->pointsB)
        this->pointsA++;
      else {
        swapSet = true;
        this->setsA.push_back(this->pointsA + 1);
        this->setsB.push_back(this->pointsB);
        this->numSetsA++, this->pointsA = 0, this->pointsB = 0;
        if (this->numSetsA == 3) ended = true;
      }
    }
  }

  if (nomeTime == this->timeB.getNome()) {
    if (this->pointsB < pointLimit - 1)
      this->pointsB++;
    else {
      if (this->pointsB <= this->pointsA)
        this->pointsB++;
      else {
        swapSet = true;
        this->setsA.push_back(this->pointsA);
        this->setsB.push_back(this->pointsB + 1);
        this->numSetsB++, this->pointsA = 0, this->pointsB = 0;
        if (this->numSetsB == 3) ended = true;
      }
    }
  }

  this->ended = ended;
  return swapSet;
}

void Partida::printJogadores(string nomeTime) {
  if (nomeTime == this->timeA.getNome()) {
    this->timeA.printJogadores();
  }

  else if (nomeTime == this->timeB.getNome()) {
    this->timeB.printJogadores();
  }
  return;
}

string Partida::showPlacar() {
  stringstream placar;

  placar << setw(10) << "Nome do Time\t\t";
  for (int i = 1; i <= this->setsA.size(); i++) placar << "Set " << i << "\t\t";

  placar << "Pontos\t\tSacando" << endl;

  placar << setw(10) << this->timeA.getNome() << "\t\t";
  for (int i = 0; i < this->setsA.size(); i++)
    placar << this->setsA[i] << "\t\t";

  placar << this->pointsA << "\t\t" << (this->sacadorA ? "*" : "") << endl;

  placar << setw(10) << this->timeB.getNome() << "\t\t";
  for (int i = 0; i < this->setsB.size(); i++)
    placar << this->setsB[i] << "\t\t";

  placar << this->pointsB << "\t\t" << (this->sacadorA ? "" : "*") << endl;

  return placar.str();
}
