#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// first is peso
// second is vertice
typedef pair<unsigned int, unsigned int> aresta_t;

void prim(vector<vector<unsigned int>> adj) {
    vector<unsigned int> pesos(adj.size(), INT_MAX);
    vector<int> pai(adj.size(), -1);
    vector<bool> visitado(adj.size(), false);

    priority_queue<aresta_t, vector<aresta_t>, greater<aresta_t>> pq;

    pesos[0] = 0;
    pq.push({0, 0});

    while (pq.size() > 0) {
        aresta_t aresta = pq.top();
        pq.pop();
        unsigned int u = aresta.second;
        if (visitado[u])
            continue;

        visitado[u] = true;

        unsigned V = adj[u].size();
        for (int i = 0; i < V; ++i) {
            if (!visitado[i] && adj[u][i] < pesos[i]) {
                pesos[i] = adj[u][i];
                pai[i] = u;
                pq.push({pesos[i], i});
            }
        }
    }

    // print the MST
    for (int i = 0; i < adj.size(); ++i) {
        cout << i << " -> " << pai[i] << " = " << pesos[i] << endl;
    }
}

int main() {
    vector<vector<unsigned int>> adj = {
        {0, 1, 9, 7, INT_MAX, INT_MAX, INT_MAX, INT_MAX},
        {1, 0, 9, INT_MAX, INT_MAX, 4, 7, INT_MAX},
        {9, 9, 0, INT_MAX, 5, 8, INT_MAX, INT_MAX},
        {7, INT_MAX, INT_MAX, INT_MAX, 0, INT_MAX, INT_MAX, INT_MAX},
        {INT_MAX, INT_MAX, 5, INT_MAX, 0, INT_MAX, 3, 9},
        {INT_MAX, 4, 8, INT_MAX, INT_MAX, 0, INT_MAX, 6},
        {INT_MAX, 7, INT_MAX, INT_MAX, 3, INT_MAX, 0, 6},
        {INT_MAX, INT_MAX, INT_MAX, INT_MAX, 9, 6, 6, 0}
    };
    prim(adj);
    return 0;
}
