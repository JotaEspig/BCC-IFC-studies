#include <climits>
#include <iostream>
#include <queue>
#include <string>

#define INF INT_MAX
#define V 6

using namespace std;

string cidades[V] = {"Blu", "Indaial", "Gaspar", "Ilhota", "Itajaí", "Brusque"};

struct Aresta {
  int anterior;
  int dist;
  bool operator>(const Aresta &outra) const { return dist > outra.dist; }
};

void dijkstra(unsigned int grafo[V][V], int origem) {
  Aresta tabela[V];
  tabela[origem] = {-1, 0};
  for (int i = 0; i < V; i++) {
    if (i != origem) {
      tabela[i] = {i, INF};
    }
  }

  queue<int> q;
  q.push(origem);
  while (q.size() > 0) {
    int atual = q.front();
    q.pop();

    for (int j = 0; j < V; ++j) {
      if (grafo[atual][j] > 0) {
        int d = grafo[atual][j] + tabela[atual].dist;
        if (d <= tabela[j].dist) {
          tabela[j].dist = d;
          tabela[j].anterior = atual;
          q.push(j);
        }
      }
    }
  }

  // print na tabela
  cout << "Cidade\tDistância\tCaminho" << endl;
  for (int i = 0; i < V; i++) {
    cout << cidades[i] << "\t" << tabela[i].dist << "\t\t";
    int anterior = tabela[i].anterior;
    while (anterior != -1) {
      cout << cidades[anterior] << " ";
      anterior = tabela[anterior].anterior;
    }
    cout << endl;
  }

  return;
}

int main() {
  unsigned int grafo[V][V] = {{0, 15, 20, 0, 0, 25}, {15, 0, 0, 40, 0, 0},
                              {20, 0, 0, 12, 30, 0}, {0, 40, 12, 0, 10, 10},
                              {0, 0, 30, 10, 0, 10}, {25, 0, 0, 10, 10, 0}};
  dijkstra(grafo, 0);
  return 0;
}
