/*
Contagem de elementos. A biblioteca padrão de funções do Python possui um método
chamado count, que determina quantas vezes um determinado valor ocorre em uma lista.
Neste exercício você deve criar uma nova função chamada countRange que deve determinar
e retornar a quantidade de elementos em uma lista que são maiores ou iguais a um valor
mínimo e menores que um valor máximo. Sua função deve receber três parâmetros: a lista (de
números), o valor mínimo e o valor máximo. Ela deve retornar um valor inteiro maior ou igual a
zero. Escreva uma função main demonstrando o funcionamento de sua função.
*/

#include <stdio.h>

int countRange(const int* lista, int tamanho, int minimo, int maximo) {
    int count = 0;
    int i;

    for (i = 0; i < tamanho; i++) {
        if (lista[i] >= minimo && lista[i] < maximo) {
            count++;
        }
    }

    return count;
}

int main() {
    int numeros[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };
    int tamanho = sizeof(numeros) / sizeof(numeros[0]);
    int minimo = 30;
    int maximo = 70;

    int quantidade = countRange(numeros, tamanho, minimo, maximo);
    printf("Quantidade de elementos no intervalo [%d, %d): %d\n", minimo, maximo, quantidade);

    return 0;
}
