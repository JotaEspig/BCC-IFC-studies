#include <stdio.h>

#define QUANT_VERTICES 10

unsigned int grafo[QUANT_VERTICES][QUANT_VERTICES];
unsigned int grau[QUANT_VERTICES];
unsigned int ciclo[QUANT_VERTICES * QUANT_VERTICES];
unsigned int comprimento_ciclo;

void encontraCicloEuleriano(unsigned int u) {
    for (unsigned int v = 0; v < QUANT_VERTICES; v++) {
        while (grafo[u][v] > 0) {
            grafo[u][v]--;
            grafo[v][u]--;
            encontraCicloEuleriano(v);
        }
    }
    ciclo[comprimento_ciclo++] = u;
}

int main() {
    unsigned int e;
    printf("Digite a quantidade de arestas: ");
    scanf("%u", &e);

    for (unsigned int i = 0; i < e; i++) {
        unsigned int u, v;
        do {
            printf("Lembre-se: O seu grafo possui %u vértices.\nDigite a aresta (u v), com valores de 0 até %u: ", QUANT_VERTICES, QUANT_VERTICES - 1);
            scanf("%u %u", &u, &v);
        } while (u >= QUANT_VERTICES || v >= QUANT_VERTICES);

        grafo[u][v]++;
        grafo[v][u]++;
        grau[u]++;
        grau[v]++;
    }

    for (unsigned int i = 0; i < QUANT_VERTICES; i++) {
        if (grau[i] % 2 != 0) {
            printf("O grafo não é Euleriano.\n");
            return 0;
        }
    }

    comprimento_ciclo = 0;
    encontraCicloEuleriano(0);

    printf("Ciclo Euleriano: ");
    for (int i = comprimento_ciclo - 1; i >= 0; i--)
        printf("%u ", ciclo[i]);
    printf("\n");

    return 0;
}
