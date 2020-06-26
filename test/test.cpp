#include <memory>
#include <string>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <set>
#include <algorithm> 
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
  string getNome();
  string getPosicao();
  int getvlrAtaque();
  int getvlrDefesa();
  int getvlrPasse();
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

Jogador ::Jogador(string nome, string posicao, int vlrAtaque, int vlrDefesa,
                  int vlrPasse, int habilidadeAdi, int pesoAtaque,
                  int pesoDefesa, int pesoPasse)
    : pesoAtaque(pesoAtaque),
      pesoDefesa(pesoDefesa),
      pesoPasse(pesoPasse),
      nome(nome),
      posicao(posicao) {
  /** Construtor da classe jogador */

  this->vlrAtaque = vlrAtaque;
  this->vlrDefesa = vlrDefesa;
  this->vlrPasse = vlrPasse;
  this->habilidadeAdi = habilidadeAdi;
}

/** Retorna o nome do jogador */
string Jogador ::getNome() { return this->nome; }

/** Retorna a posicao do jogador */
string Jogador ::getPosicao() { return this->posicao; }

/** Retorna o valor de ataque do jogador */
int Jogador ::getvlrAtaque() { return this->vlrAtaque; }

/** Retorna o valor de defesa do jogador */
int Jogador ::getvlrDefesa() { return this->vlrDefesa; }

/** Retorna o valor de passe do jogador */
int Jogador ::getvlrPasse() { return this->vlrPasse; }

/** Construtor da classe derivada Levantador */
Levantador ::Levantador(string nome, int vlrAtaque, int vlrDefesa, int vlrPasse,
                        int habilidadeAdi)
    : Jogador(nome, "levantador", vlrAtaque, vlrDefesa, vlrPasse, habilidadeAdi,
              1, 3, 6) {}

/** Retorna a habilidade do levantador */
int Levantador ::getHabilidade() {
  return (this->vlrAtaque * pesoAtaque + this->vlrDefesa * pesoDefesa +
          this->vlrPasse * pesoPasse + 10 * habilidadeAdi);
}

/** Construtor da classe derivada Libero */
Libero ::Libero(string nome, int vlrAtaque, int vlrDefesa, int vlrPasse,
                int habilidadeAdi)
    : Jogador(nome, "libero", vlrAtaque, vlrDefesa, vlrPasse, habilidadeAdi, 0,
              5, 5) {}

/** Retorna a habilidade do libero */
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

/** Construtor da classe derivada Meia*/
Meia ::Meia(string nome, int vlrAtaque, int vlrDefesa, int vlrPasse,
            int habilidadeAdi)
    : Jogador(nome, "meia", vlrAtaque, vlrDefesa, vlrPasse, habilidadeAdi, 4, 3,
              1) {}

/** Retorna a habilidade do meia */
int Meia ::getHabilidade() {
  return (this->vlrAtaque * pesoAtaque + this->vlrDefesa * pesoDefesa +
          this->vlrPasse * pesoPasse - habilidadeAdi);
}

/** Construtor da classe derivada Ponta */
Ponta ::Ponta(string nome, int vlrAtaque, int vlrDefesa, int vlrPasse,
              int habilidadeAdi)
    : Jogador(nome, "ponta", vlrAtaque, vlrDefesa, vlrPasse, habilidadeAdi, 4,
              3, 3) {}

/** Retorna a habilidade do ponta */
int Ponta ::getHabilidade() {
  return (this->vlrAtaque * pesoAtaque + this->vlrDefesa * pesoDefesa +
          this->vlrPasse * pesoPasse);
}

/** Construtor da classe derivada Oposto */
Oposto ::Oposto(string nome, int vlrAtaque, int vlrDefesa, int vlrPasse,
                int habilidadeAdi)
    : Jogador(nome, "oposto", vlrAtaque, vlrDefesa, vlrPasse, habilidadeAdi, 6,
              3, 1) {}

/** Retorna a habilidade do oposto */
int Oposto ::getHabilidade() {
  return (this->vlrAtaque * pesoAtaque + this->vlrDefesa * pesoDefesa +
          this->vlrPasse * pesoPasse + 20 * habilidadeAdi);
}

/** Destrutor virtual da classe*/

Jogador ::~Jogador(){}

/** Classe do time */

class Time {
 public:
  vector<unique_ptr<Jogador>> jogadores;
  map<string, int> tipoJogadores;
  string nomeTime;
  Time(const Time&);
  Time(string nomeTime);
  int getHabilidadeTotal();
  string getNome() const;
  bool isValid();
  bool addJogador(string nome, string posicao, int vlrAtaque, int vlrDefesa,
                  int vlrPasse, int habilidadeAdi);
  bool removeJogador(string nome);
  friend ostream& operator<<(ostream&, const Time&);
};

Time::Time(const Time& time) {
  for (const auto& jogador : time.jogadores) {
    this->jogadores.push_back(jogador->clone());
  }
  this->nomeTime = time.nomeTime;
  this->tipoJogadores = time.tipoJogadores;
}

Time ::Time(string nomeTime) {
  /** Construtor da classe time */

  this->nomeTime = nomeTime;
  jogadores.clear();
  tipoJogadores.clear();
}

/** Retorna o nome do time */

string Time ::getNome() const { return this->nomeTime; }

bool Time ::isValid() {
  /** Verifica se o time está de acordo com as regras */

  if (tipoJogadores["levantador"] != 1 or tipoJogadores["libero"] != 1 or
      tipoJogadores["oposto"] != 1 or tipoJogadores["meia"] != 2 or
      tipoJogadores["ponta"] != 2)
    return false;
  return true;
}

int Time ::getHabilidadeTotal() {
  /** Retorna a habilidade total do time */

  if (!this->isValid()) {
    return -1;
  }
  int sumHab = 0;
  for (int i = 0; i < 7; ++i) sumHab += jogadores[i]->getHabilidade();
  return sumHab;
}

bool Time ::addJogador(string nome, string posicao, int vlrAtaque,
                       int vlrDefesa, int vlrPasse, int habilidadeAdi) {
  /** Adiciona um novo jogador ao time
   *
   * Argumentos:
   * string nome        ---> nome do jogador
   * string posicao     ---> posição do jogador
   * int vlrAtaque      ---> Valor de ataque desse jogador
   * int vlrDefesa      ---> Valor de defesa desse jogador
   * int vlrPasse       ---> Valor de passe desse jogador
   * int habilidadeAdi  ---> Habilidade adicional desse jogador de acordo com
   * sua posição
   *
   * Retorna:
   * True, caso o jogador seja adicionado ou a equipe já esteja completa e seja
   * válida False, caso a equipe esteja completa e seja inválida ou se a posição
   * do jogador não for encontrada
   */

  if ((int)jogadores.size() == 7) {
    if (this->isValid()) {
      return true;
    }
    return false;
  }

  for (int i = 0; i < (int)jogadores.size(); i++) {
    if (jogadores[i]->getNome() == nome) return false;
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
  /** Remove jogador do time
   *
   * Argumentos: string nome    ---> nome do jogador
   *
   * Retorna:
   * True, caso o jogador seja removido com sucesso
   * False, caso contrário
   */

  for (int i = 0; i < (int)jogadores.size(); ++i) {
    if (jogadores[i]->getNome() == nome) {
      tipoJogadores[jogadores[i]->getPosicao()]--;
      jogadores.erase(jogadores.begin() + i);
      return true;
    }
  }
  return false;
}

ostream& operator<<(ostream& o, const Time& time) {
  /** Printa as informações dos jogadores */

  if ((int)time.jogadores.size() == 0) {
    o << "Nao ha jogadores nesse time\n\n";
    return o;
  }

  int width = 20;

  o << "Os jogadores do time sao" << endl << endl;
  o << setw(width) << setfill(' ') << "Nome";
  o << setw(width) << setfill(' ') << "Posicao";
  o << setw(width) << setfill(' ') << "Valor ataque";
  o << setw(width) << setfill(' ') << "Valor defesa";
  o << setw(width) << setfill(' ') << "Valor passe";
  o << setw(width) << setfill(' ') << "Habilidade total" << endl;

  for (int i = 0; i < (int)time.jogadores.size(); ++i) {
    o << setw(width) << setfill(' ') << time.jogadores[i]->getNome();
    o << setw(width) << setfill(' ') << time.jogadores[i]->getPosicao();
    o << setw(width) << setfill(' ') << time.jogadores[i]->getvlrAtaque();
    o << setw(width) << setfill(' ') << time.jogadores[i]->getvlrDefesa();
    o << setw(width) << setfill(' ') << time.jogadores[i]->getvlrPasse();
    o << setw(width) << setfill(' ') << time.jogadores[i]->getHabilidade();
    o << endl;
  }
  return o;
}
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

  if (not this->timeA.isValid() or not this->timeB.isValid()) {
    cout << "Algum dos time e invalido" << endl;
    return this->ended = true;
  }

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
  for (int i = 1; i <= (int)partida.setsA.size(); i++) o << "Set " << i << "\t\t";

  o << "Pontos\t\tSacando" << endl;

  o << setw(10) << partida.timeA.getNome() << "\t\t";
  for (int i = 0; i < (int)partida.setsA.size(); i++)
    o << partida.setsA[i] << "\t\t";

  o << partida.pointsA << "\t\t" << (partida.sacadorA ? "*" : "") << endl;

  o << setw(10) << partida.timeB.getNome() << "\t\t";
  for (int i = 0; i < (int)partida.setsB.size(); i++)
    o << partida.setsB[i] << "\t\t";

  o << partida.pointsB << "\t\t" << (partida.sacadorA ? "" : "*") << endl;

  return o;
}

int menuInicial() {
  int opcaoMenu;
  cout << "\t\t         SISTEMA PARA SIMULAR JOGOS DE VOLEI\n";
  cout << "\t\t\t======================================\n";
  cout << "\t\t\t|\t                              |\n";
  cout << "\t\t\t|    1 - Criar time                   |\n";
  cout << "\t\t\t|    2 - Adicionar jogador            |\n";
  cout << "\t\t\t|    3 - Remover jogador              |\n";
  cout << "\t\t\t|    4 - Simular partida              |\n";
  cout << "\t\t\t|    0 - Sair                         |\n";
  cout << "\t\t\t|                                     |\n";
  cout << "\t\t\t======================================\n";
  cout << "\n\n";
  cout << "\t\t\tPor favor, selecione uma opcao: ";
  cin >> opcaoMenu;
  cout << "\n\n";
  return opcaoMenu;
}

bool criaTime(string nomeTime, map<string, unique_ptr<Time>>& times) {
  if (times.find(nomeTime) != times.end()) return false;
  times[nomeTime] = unique_ptr<Time>(new Time(nomeTime));
  return true;
}


int main() {
  int opcaoMenu;
  string nomeTime;
  map<string, unique_ptr<Time>> times;
  set<string> posicoes{"levantador", "libero", "meia", "ponta", "oposto"};
  printf("\n\n");
  do {
    opcaoMenu = menuInicial();
    if (opcaoMenu == 1) {
      cout << "Digite o nome do time: \n";
      cin >> nomeTime;
      criaTime(nomeTime, times);
      cout << "Time criado com sucesso!\n\n";
    }

    if (opcaoMenu == 2) {
      cout << "Digite o time em que o jogador ira jogar\n\n";
      cin >> nomeTime;
      cout << "\n\n";
      if (times.find(nomeTime) == times.end()) {
        char c;
        cout << "Time nao encontrado\n\n";
        cout << "Deseja cria-lo?\n";
        cout << "S para sim, N para nao\n\n";
        cin >> c;
        cout << "\n\n";
        if (tolower(c) == 's') {
          criaTime(nomeTime, times);
          cout << "Time criado com sucesso!\n\n";
        }

      } else {
        string nome, posicao;
        int vlrAtaque, vlrDefesa, vlrPasse, habilidadeAdi;
        cout << "Digite o nome do jogador\n\n";
        cin >> nome;
        cout << "\n\n";
        cout << "Digite em que posicao o jogador joga\n\n";
        cout << "Ela pode ser: Levantador, libero, oposto, meia e ponta\n\n";
        cin >> posicao;
        cout << "\n\n";
        for_each(posicao.begin(), posicao.end(),
                 [](char& c) { c = tolower(c); });
        if (posicoes.find(posicao) != posicoes.end()) {
          cout << "Digite o valor de ataque\n\n";
          cin >> vlrAtaque;
          cout << "\n\n";
          cout << "Digite o valor de defesa\n\n";
          cin >> vlrDefesa;
          cout << "\n\n";
          cout << "Digite o valor de passe\n\n";
          cin >> vlrPasse;
          cout << "\n\n";
          if (posicao == "levantador") {
            cout << "Digite quantas vezes o levantador foi o melhor jogador do "
                    "campeonato\n\n";
            cin >> habilidadeAdi;
            cout << "\n\n";
          }
          if (posicao == "libero") {
            cout << "Digite quantas vezes o libero foi o jogador com melhor "
                    "qualidade de passe\n\n";
            cin >> habilidadeAdi;
            cout << "\n\n";
          }
          if (posicao == "meia") {
            cout << "Digite quantas vezes o meia nao fez um bloqueio\n\n";
            cin >> habilidadeAdi;
            cout << "\n\n";
          }
          if (posicao == "oposto") {
            cout << "Digite quantas vezes o oposto foi o jogador que mais "
                    "marcou pontos\n\n";
            cin >> habilidadeAdi;
            cout << "\n\n";
          } else {
            habilidadeAdi = 0;
          }
          times[nomeTime]->addJogador(nome, posicao, vlrAtaque, vlrDefesa,
                                      vlrPasse, habilidadeAdi);
          cout << "Jogador adicionado com sucesso\n\n";
          for (auto time = times.begin(); time != times.end(); ++time) {
            cout << *(time->second);
          }
        } else {
          cout << "Posicao nao existente\n\n";
        }
      }
    }

    if (opcaoMenu == 3) {
      cout << "Digite o time do jogador\n\n";
      cin >> nomeTime;
      cout << "\n\n";
      if (times.find(nomeTime) != times.end())
        cout << "Time não encontrado\n\n";
      else {
        string nome;
        cout << "Digite o nome do jogador\n\n";
        cin >> nome;
        cout << "\n\n";
        if (times[nomeTime]->removeJogador(nome))
          cout << "Jogador removido com sucesso!\n\n";
        else
          cout << "Jogador nao encontrado!\n\n";
      }
    }

    if (opcaoMenu == 4) {
      string nomeTime1, nomeTime2;
      int escolha, numPontos;
      cout << "Digite o nome do primeiro time\n\n";
      cin >> nomeTime1;
      cout << "\n\n";
      if (times.find(nomeTime1) == times.end())
        cout << "Time nao encontrado\n\n";
      else {
        cout << "Digite o nome do segundo time\n\n";
        cin >> nomeTime2;
        cout << "\n\n";
        if (times.find(nomeTime2) == times.end())
          cout << "Time nao encontrado\n\n";
        else {
          cout << "Escolha quem inicia sacando\n";
          cout << "1 - " << nomeTime1 << "\n";
          cout << "2 - " << nomeTime2 << "\n";
          cin >> escolha;
          cout << "\n\n";
          Time timeA = *times[nomeTime1];
          Time timeB = *times[nomeTime2];
          if (escolha == 1) {
            Partida partida(timeA, timeB, true);
            cout << "Escolha quantos pontos deseja simular\n\n";
            do {
              cin >> numPontos;
              cout << "\n\n";
              for (int i = 0; i < numPontos or partida.isEnded(); ++i)
                partida.playPoint();
              cout << partida;
              cout << "\n\n";
              cout << "Deseja simular mais pontos? (Digite 0 caso nao)\n\n";
            } while (numPontos != 0);
          } else {
            Partida partida(timeA, timeB, false);
            cout << "Escolha quantos pontos deseja simular\n\n";
            do {
              cin >> numPontos;
              cout << "\n\n";
              for (int i = 0; i < numPontos or partida.isEnded(); ++i)
                partida.playPoint();
              cout << partida;
              cout << "\n\n";
              cout << "Deseja simular mais pontos? (Digite 0 caso nao)\n\n";
            } while (numPontos != 0);
          }
        }
      }
    }

  } while ((opcaoMenu == 1) || (opcaoMenu == 2) || (opcaoMenu == 3) ||
           (opcaoMenu == 4));
	return 0;
}
