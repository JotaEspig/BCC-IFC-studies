/*
Cara ou coroa. Qual é o menor número de vezes que você precisa sortear uma moeda para
ter três resultados consecutivos iguais de cara ou de coroa? Qual é o número máximo de
sorteios necessários? Quantos sorteios precisamos em média? Neste exercício vamos
explorar estas questões criando um programa que simula várias séries de sorteios de cara ou
coroa.
Crie um programa que utilize o gerador de números randômicos do Python para simular o
sorteio de uma moeda várias vezes. A moeda simulada deve ser justa, ou seja, deve ter a
mesma probabilidade de gerar cara e coroa. Seu programa deve continuar simulando sorteios
até que ocorra uma sequencia de 3 caras ou de 3 coroas consecutivas. Exiba A para cada vez
que ocorrer cara e O para cada vez que ocorrer coroa, com todos os resultados sendo
exibidos na mesma linha. Então exiba a quantidade de sorteios que levou para chegar a três
resultados iguais consecutivos. Quando seu programa executar, ele deve fazer esta simulação
10 vezes e, ao final, mostrar a quantidade média de sorteios necessária. Abaixo segue um
exemplo de saída do programa:
A O O O (4 sorteios)
A A O O A O A O O A A O A O O A O O O (19 sorteios)
O O O (3 sorteios)
O A A A (4 sorteios)
A A A (3 sorteios)
O A O O A O A A O O A A O A O A A A (18 sorteios)
A O O A A A (6 sorteios)
A O A A A (5 sorteios)
O O A O O A O A O A A A (12 sorteios)
O A O O O (5 sorteios)
Na média, foram necessários 7.9 sorteios.
*/

// compile with "list.c"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "list.h"

int raffle();

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Use: ./<app_name> <number_of_raffles>\n");
        return -1;
    }
    
    srandom(time(NULL)); // set seed "randomly"

    int count = atoi(argv[1]);
    int sum = 0;
    for (int i = 0; i < count; i++)
        sum += raffle();

    float average = (float)sum / count;

    printf("Media de sorteios: %f\n", average);
    return 0;
}

int raffle()
{
    num_list_t *nl = new_num_list();
    int i = 0;
    while (nl->size < 3 ||
           !(nl->values[i - 1] == nl->values[i - 2] &&
            nl->values[i - 2] == nl->values[i - 3]))
    {
        int heads_or_tails = random() & 1; // same as random() % 2 
        num_list_append(nl, heads_or_tails);
        if (heads_or_tails == 0)
            printf("O ");
        else
            printf("A ");

        i++;
    }

    printf("(%d sorteios)\n", i);
    return i;
}
