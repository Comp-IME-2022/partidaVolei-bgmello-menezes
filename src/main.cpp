#include <algorithm>
#include <set>

#include "Partida.h"
using namespace std;

int menuInicial() {
  int opcaoMenu;
  cout << "\t\t         SISTEMA PARA SIMULAR JOGOS DE VOLEI\n";
  cout << "\t\t\t======================================\n";
  cout << "\t\t\t|\t                              |\n";
  cout << "\t\t\t|    1 - Criar time                   |\n";
  cout << "\t\t\t|    2 - Adicionar jogador            |\n";
  cout << "\t\t\t|    3 - Remover jogador              |\n";
  cout << "\t\t\t|    4 - Simular partida              |\n";
  cout << "\t\t\t|    5 - Mostrar time                 |\n";
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
  int opcaoMenu, opcaoObjeto = 1;
  string nomeTime;
  map<string, unique_ptr<Time>> times;
  set<string> posicoes{"levantador", "libero", "meia", "ponta", "oposto"};
  printf("\n\n");
  do {
    opcaoMenu = menuInicial();
    if (opcaoMenu == 1) {
      cout << "Digite o nome do time: \n";
      cin >> nomeTime;
      if (not criaTime(nomeTime, times)) cout << "Time já existe!" << endl;
    }

    if (opcaoMenu == 2) {
      cout << "Digite o time em que o jogador ira jogar\n\n";
      cin >> nomeTime;
      cout << "\n\n";
      if (times.find(nomeTime) == times.end()) {
        char c;
        cout << "Time não encontrado\n\n";
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
          if (times[nomeTime]->addJogador(nome, posicao, vlrAtaque, vlrDefesa,
                                          vlrPasse, habilidadeAdi))
            cout << "Jogador adicionado com sucesso\n\n";
          else
            cout << "Jogador nao pode ser adicionado ao time\n\n";
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
      if (times.find(nomeTime) == times.end())
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
          if (escolha == 1) {
            Time timeA = *times[nomeTime1];
            Time timeB = *times[nomeTime2];
            Partida partida(timeA, timeB, true);
            cout << "Escolha quantos pontos deseja simular\n\n";
            do {
              cin >> numPontos;
              cout << "\n\n";
              for (int i = 0; i < numPontos and not partida.isEnded(); ++i)
                partida.playPoint();
              cout << partida;
              cout << "\n\n";
              cout << "Deseja simular mais pontos? (Digite 0 caso nao)\n\n";
            } while (numPontos != 0);
          } else {
            Time timeA = *times[nomeTime1];
            Time timeB = *times[nomeTime2];
            Partida partida(timeA, timeB, false);
            cout << "Escolha quantos pontos deseja simular\n\n";
            do {
              cin >> numPontos;
              cout << "\n\n";
              for (int i = 0; i < numPontos and not partida.isEnded(); ++i)
                partida.playPoint();
              cout << partida;
              cout << "\n\n";
              cout << "Deseja simular mais pontos? (Digite 0 caso nao)\n\n";
            } while (numPontos != 0);
          }
        }
      }
    }
    if (opcaoMenu == 5) {
      string nomeTime;
      cout << "Digite o nome do time:";
      cin >> nomeTime;
      if (times.find(nomeTime) == times.end())
        cout << "Time nao existe!\n\n";
      else {
        cout << *times[nomeTime] << endl;
      }
    }

  } while ((opcaoMenu == 1) || (opcaoMenu == 2) || (opcaoMenu == 3) ||
           (opcaoMenu == 4) || (opcaoMenu == 5));

  return 0;
}
