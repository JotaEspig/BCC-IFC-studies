#include <climits>
#include <iostream>
#include <string>

using namespace std;

#define V 6
#define INF INT_MAX
string cidades[V] = {"Blu", "Indaial", "Gaspar", "Ilhota", "Itajaí", "Brusque"};

void floydWarshall(unsigned int grafo[V][V]) {
    unsigned int dist[V][V];
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = grafo[i][j];
        }
    }

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    cout << "Cidade\tDistância\tCaminho" << endl;
    for (int i = 0; i < V; i++) {
        cout << cidades[i] << "\t";
        for (int j = 0; j < V; j++) {
            cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    unsigned int grafo[V][V]
        = {{0, 15, 20, INF, INF, 25}, {15, 0, INF, 40, INF, 0},
           {20, INF, 0, 12, 30, 0},   {INF, 40, 12, 0, 10, 10},
           {INF, INF, 30, 10, 0, 10}, {25, INF, INF, 10, 10, 0}};
    floydWarshall(grafo);
    return 0;
}
