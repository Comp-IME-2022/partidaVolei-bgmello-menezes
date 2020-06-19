#include <Partida.h>

#include <iomanip>
#include <sstream>
#include <string>

/**
 * Gera um numero aleatorio de 0 a 1
 */
inline double Partida::randd() {
  return (double)rand() / ((double)RAND_MAX + 1);
}
/**
 * Construtor que recebe dois times e se o timeA sera o sacador inicial
 */
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

/**
 *
 * Construtor que recebe o nome dos dois times e se o timeA sera o sacador
 * inicial Os times serao construidos vazios, logo devemos adicionar os jogadors
 * nos times pela funcao add jogador
 */
Partida::Partida(std::string nomeA, std::string nomeB, bool sacadorA)
    : timeA(nomeA), timeB(nomeB) {
  this->pointsA = this->pointsB = 0;
  this->setsA.clear();
  this->setsB.clear();
  this->numSetsA = this->numSetsB = 0;
  this->sacadorA = this->primeiroSacadorA = sacadorA;
  this->ended = false;
}

/**
 * Adiciona jogador em um time
 *
 * Recebe o nome do time, nome do jogador, sua posicao, valor do ataque, valor
 * de defesa e habilidade adicional.
 *
 * Se o nome do time nao existe ou nao e possivel adicionar o jogador no time
 * a funcao retorna falso.
 */
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

/**
 * Remove um jogador de um time pelo nome.
 *
 * Se o time nao existe ou se o jogador nao esta
 * no time o metodo retorna falso.
 */
bool Partida::removeJogador(string nomeTime, string nomeJogador) {
  if (nomeTime == this->timeA.getNome()) {
    return this->timeA.removeJogador(nomeJogador);
  }

  else if (nomeTime == this->timeB.getNome()) {
    return this->timeB.removeJogador(nomeJogador);
  }

  return false;
}
/**
 * Retorna se um time e valido pelo nome
 * Se o time nao e valido ou nao existe retorna falso.
 */
bool Partida::timeIsValid(string nomeTime) {
  if (nomeTime == this->timeA.getNome()) {
    return this->timeA.isValid();
  }

  else if (nomeTime == this->timeB.getNome()) {
    return this->timeB.isValid();
  }

  return false;
}
/**
 * Recomeca a partida
 * Reseta todos os atributos exceto os times.
 */
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
/**
 * Joga um ponto baseado no modelo probabilistico definido
 *
 */
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

/**
 * Retorna se a partida ja esta terminada
 */
bool Partida::isEnded() { return this->ended; }
/**
 * Adiciona um ponto a um time, se o jogo
 * ja estiver terminado, entao nao faz nada
 */
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
/**
 * Mostra os jogadores do time pelo nome
 * Se o time nao existe nao mostra nada.
 */
void Partida::printJogadores(ostream& o, string nomeTime) {
  if (nomeTime == this->timeA.getNome()) {
    o << this->timeA;
  }

  else if (nomeTime == this->timeB.getNome()) {
    o << this->timeB;
  }
  return;
}
/**
 * Mostra o historico do placar
 */
ostream& operator<<(ostream& o, const Partida& partida) {
  o << setw(10) << "Nome do Time\t\t";
  for (int i = 1; i <= partida.setsA.size(); i++) o << "Set " << i << "\t\t";

  o << "Pontos\t\tSacando" << endl;

  o << setw(10) << partida.timeA.getNome() << "\t\t";
  for (int i = 0; i < partida.setsA.size(); i++)
    o << partida.setsA[i] << "\t\t";

  o << partida.pointsA << "\t\t" << (partida.sacadorA ? "*" : "") << endl;

  o << setw(10) << partida.timeB.getNome() << "\t\t";
  for (int i = 0; i < partida.setsB.size(); i++)
    o << partida.setsB[i] << "\t\t";

  o << partida.pointsB << "\t\t" << (partida.sacadorA ? "" : "*") << endl;

  return o;
}
