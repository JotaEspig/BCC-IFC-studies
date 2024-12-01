#include <climits>
#include <iostream>
#include <queue>

#define INF INT_MAX
#define V 8

using namespace std;

struct Aresta {
    int anterior;
    int dist;
    bool operator>(const Aresta &outra) const {
        return dist > outra.dist;
    }
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
        cout << i << "\t" << tabela[i].dist << "\t\t";
        int anterior = tabela[i].anterior;
        while (anterior != -1) {
            cout << anterior << " ";
            anterior = tabela[anterior].anterior;
        }
        cout << endl;
    }

    return;
}

int main() {
    unsigned grafo[V][V]
        = {{0, 1, 9, 7, 0, 0, 0, 0},
           {1, 0, 9, 0, 0, 4, 7, 0},
           {9, 9, 0, 0, 5, 8, 0, 0},
           {7, 0, 0, 0, 0, 0, 0, 0},
           {0, 0, 5, 0, 0, 0, 3, 9},
           {0, 4, 8, 0, 0, 0, 0, 6},
           {0, 7, 0, 0, 3, 0, 0, 6},
           {0, 0, 0, 0, 9, 6, 6, 0}};
    dijkstra(grafo, 0);
    return 0;
}
