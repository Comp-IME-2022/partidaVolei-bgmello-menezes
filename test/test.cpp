#include <bits/stdc++.h>

#include "Partida.h"

using namespace std;

int main() {
  srand(time(NULL));

  Partida A("Brasil", "EUA", true);
  A.addJogador("Brasil", "Mordomo1", "levantador", 40, 10, 30, 10);
  A.addJogador("Brasil", "Mordomo2", "libero", 10, 10, 30, 10);
  A.addJogador("Brasil", "Mordomo3", "oposto", 10, 10, 30, 10);
  A.addJogador("Brasil", "Mordomo4", "meia", 10, 10, 30, 10);
  A.addJogador("Brasil", "Mordomo5", "ponta", 10, 20, 30, 10);
  A.addJogador("Brasil", "Mordomo6", "meia", 10, 30, 30, 10);
  A.addJogador("Brasil", "Mordomo7", "ponta", 80, 10, 30, 10);

  A.addJogador("EUA", "Executivo1", "levantador", 10, 10, 30, 10);
  A.addJogador("EUA", "Executivo2", "libero", 10, 10, 30, 10);
  A.addJogador("EUA", "Executivo3", "oposto", 10, 10, 30, 10);
  A.addJogador("EUA", "Executivo4", "meia", 10, 10, 30, 10);
  A.addJogador("EUA", "Executivo5", "ponta", 10, 10, 30, 10);
  A.addJogador("EUA", "Executivo6", "meia", 10, 10, 30, 10);
  A.addJogador("EUA", "Executivo7", "ponta", 10, 10, 30, 10);

  cout << "Brasil" << endl;
  A.printJogadores("Brasil");

  cout << endl << endl;
  cout << "EUA" << endl;
  A.printJogadores("EUA");

  for (int i = 1; not A.isEnded(); i++) {
    A.playPoint();
    if (i % 50 == 0) cout << A.showPlacar() << endl;
  }
  cout << A.showPlacar() << endl;
  return 0;
}
