#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Assume INT_MAX como infinito
#define INF INT_MAX

// Define um item da tabela do algoritmo de Dijkstra (distância e vértice
// anterior)
struct DistMin {
    unsigned int dist;
    int previous;
};

vector<DistMin>
Dijkstra(vector<vector<unsigned int>> adj, unsigned int origin) {
    // Inicializa a tabela de distâncias mínimas
    vector<DistMin> dist_min(adj.size(), {INF, -1});
    // A distância do vértice de origem para ele mesmo é 0
    dist_min[origin] = {0, -1};

    // Inicia o algoritmo com o vertice origem
    queue<unsigned int> q;
    q.push(origin);

    while (q.size() > 0) {
        unsigned int u = q.front();
        q.pop();
        // Passa por cada vértice adjacente a u
        for (int i = 0; i < adj.size(); ++i) {
            // Se u == i sigfnica que é o mesmo vértice, pula para o próximo
            if (u == i) {
                continue;
            }
            // Se for INF, não tem aresta entre u e i, pula para o próximo
            if (adj[u][i] == INF) {
                continue;
            }

            // d é o possível novo valor da distância mínima de i
            int d = adj[u][i] + dist_min[u].dist;
            // Verifica se d é menor que o valor atual da distância mínima de i
            if (d < dist_min[i].dist) {
                // Atualiza a distância mínima e vértice anterior de i e
                // adiciona i na fila
                q.push(i);
                dist_min[i].dist = d;
                dist_min[i].previous = u;
            }
        }
    }

    // Retorna a tabela de distâncias mínimas
    return dist_min;
}

int main() {
    int n, e;
    while (true) {
        // le N e E
        cin >> n >> e;
        if (n == 0 && e == 0) {
            break;
        }

        // Initializa a matriz de adjacência
        vector<vector<unsigned int>> adj(n);
        for (int i = 0; i < n; ++i) {
            adj[i] = vector<unsigned int>(n, INF); // Seta tudo para INF
            adj[i][i] = 0; // A distância de um vértice para ele mesmo é 0
        }

        for (int i = 0; i < e; ++i) {
            unsigned int x, y, h;
            cin >> x >> y >> h;
            // Caso ambos os vértices tenham aresta, significa que ambos estão
            // no mesmo país (enunciado do problema), logo suas distâncias (em
            // horas de envio) são 0
            if (adj[y - 1][x - 1] < INT_MAX) {
                adj[x - 1][y - 1] = 0;
                adj[y - 1][x - 1] = 0;
            }
            else {
                // Caso não, seta a distância (horas de envio) de x para y como
                // h
                adj[x - 1][y - 1] = h;
            }
        }

        // consultas
        int k;
        cin >> k;
        for (int i = 0; i < k; ++i) {
            int o, d;
            cin >> o >> d;
            // Executa o algoritmo de Dijkstra
            // O Dijkstra é utilizado pois o problema pede o caminho mínimo
            // entre o ponto origem (O) e o ponto destino (D)
            vector<DistMin> dist_min = Dijkstra(adj, o - 1);

            // Caso o vértice de destino não tenha um vértice anterior, não é possível chegar nele saindo de O
            if (dist_min[d - 1].previous == -1) {
                cout << "Nao e possivel entregar a carta\n";
            }
            else {
                cout << dist_min[d - 1].dist << "\n";
            }
        }
        cout << "\n";
    }

    return 0;
}
