#include <bits/stdc++.h>
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

Jogador ::Jogador(string nome, string posicao, int vlrAtaque, int vlrDefesa,
                  int vlrPasse, int habilidadeAdi, int pesoAtaque,
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
    : Jogador(nome, "levantador", vlrAtaque, vlrDefesa, vlrPasse, habilidadeAdi, 1,
              3, 6) {}
              
/* Retorna a habilidade do levantador */
int Levantador ::getHabilidade() {
  	
  return this->vlrAtaque * pesoAtaque + this->vlrDefesa * pesoDefesa +
             this->vlrPasse * pesoPasse + 10*this->habilidadeAdi;
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
          this->vlrPasse * pesoPasse - this->habilidadeAdi);
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

class Time {
 public:
  vector<unique_ptr<Jogador>> jogadores;
  map<string, int> tipoJogadores;
  string nomeTime;
  Time(string nomeTime);
  int getHabilidadeTotal();
  string getNome();
  bool isValid();
  bool addJogador(string nome, string posicao, int vlrAtaque, int vlrDefesa,
                  int vlrPasse, int habilidadeAdi);
  bool removeJogador(string nome);
  void printJogadores();
};

Time ::Time(string nomeTime) {
	
/* Construtor da classe time */

  this->nomeTime = nomeTime;
  jogadores.clear();
  tipoJogadores.clear();
}

/* Retorna o nome do time */

string Time ::getNome() { return this->nomeTime; }



bool Time ::isValid() {
	
/* Verifica se o time está de acordo com as regras */
	
  if (tipoJogadores["levantador"] != 1 or tipoJogadores["libero"] != 1 or
      tipoJogadores["oposto"] != 1 or tipoJogadores["meia"] != 2 or
      tipoJogadores["ponta"] != 2)
    return false;
  return true;
}



int Time ::getHabilidadeTotal() {
	
/* Retorna a habilidade total do time */
	
  if (!this->isValid()) {
    return -1;
  }
  int sumHab = 0;
  for (int i = 0; i < 7; ++i) sumHab += jogadores[i]->getHabilidade();
  return sumHab;
}



bool Time ::addJogador(string nome, string posicao, int vlrAtaque,
                       int vlrDefesa, int vlrPasse, int habilidadeAdi) {
/* Adiciona um novo jogador ao time 
 * 
 * Argumentos:
 * string nome        ---> nome do jogador
 * string posicao     ---> posição do jogador
 * int vlrAtaque      ---> Valor de ataque desse jogador
 * int vlrDefesa      ---> Valor de defesa desse jogador
 * int vlrPasse       ---> Valor de passe desse jogador
 * int habilidadeAdi  ---> Habilidade adicional desse jogador de acordo com sua posição
 * 
 * Retorna:
 * True, caso o jogador seja adicionado ou a equipe já esteja completa e seja válida
 * False, caso a equipe esteja completa e seja inválida ou se a posição do jogador não for encontrada
 */					   
				
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
	
/* Remove jogador do time
 * 
 * Argumentos: string nome    ---> nome do jogador
 * 
 * Retorna:
 * True, caso o jogador seja removido com sucesso
 * False, caso contrário
 */
	
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

/* Printa as informações dos jogadores */

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

class Partida {
  Time timeA, timeB;
  bool sacadorA, ended;
  int pointsA, pointsB;
  int setsA, setsB;

  inline double randd();

  bool addPoint(string nomeTime);

 public:
  Partida(string nomeA, string nomeB);
  
  bool timeIsValid(string nomeTime);

	
	
  bool addJogador(string nomeTime, string nomeJogador, string posicao,
                  int vlrAtaque, int vlrDefesa, int vlrPasse,
                  int habilidadeAdi);

  bool removeJogador(string nomeTime, string nomeJogador);

  bool playPoint();

  bool resetPartida();

  string showPlacar();
  
  void printJogadores(string nomeTime);
};

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

  placar << "Nome do Time\t\tSets\t\tPontos\t\tSacando" << endl;
  placar << this->timeA.getNome() << "\t\t" << this->setsA << "\t\t"
         << this->pointsA << "\t\t" << (this->sacadorA ? "*" : "") << endl;
  placar << this->timeB.getNome() << "\t\t" << this->setsB << "\t\t"
         << this->pointsB << "\t\t" << (this->sacadorA ? "" : "*") << endl;

  return placar.str();
}
 
int main (){
	
	Partida A("Brasil", "EUA");
	A.addJogador("Brasil", "Mordomo1", "levantador", 10, 10, 30, 10);
	A.addJogador("Brasil", "Mordomo2", "libero", 10, 10, 30, 10);
	A.addJogador("Brasil", "Mordomo3", "oposto", 10, 10, 30, 10);
	A.addJogador("Brasil", "Mordomo4", "meia", 10, 10, 30, 10);
	A.addJogador("Brasil", "Mordomo5", "ponta", 10, 10, 30, 10);
	A.addJogador("Brasil", "Mordomo6", "meia", 10, 10, 30, 10);
    A.addJogador("Brasil", "Mordomo7", "ponta", 10, 10, 30, 10);
    
    A.addJogador("EUA", "Executivo1", "levantador", 10, 10, 30, 10);
	A.addJogador("EUA", "Executivo2", "libero", 10, 10, 30, 10);
	A.addJogador("EUA", "Executivo3", "oposto", 10, 10, 30, 10);
	A.addJogador("EUA", "Executivo4", "meia", 10, 10, 30, 10);
	A.addJogador("EUA", "Executivo5", "ponta", 10, 10, 30, 10);
	A.addJogador("EUA", "Executivo6", "meia", 10, 10, 30, 10);
    A.addJogador("EUA", "Executivo7", "ponta", 10, 10, 30, 10);
	for(int i = 0; i < 500; ++i)
		A.playPoint();
	cout << A.showPlacar();
    return 0;
}
