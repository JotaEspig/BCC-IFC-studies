/*
Valor das entradas. Um determinado zoológico estipula o valor da entrada baseado na idade
do visitante. Visitantes com até dois anos de idade não precisam pagar. Crianças entre 3 e 12
anos de idade pagam R$ 14.00. Idosos com 65 anos ou mais pagam R$ 18.00. Todos os
demais pagam R$ 23.00. Crie um programa que inicia lendo as idades, uma por uma, de um
grupo de pessoas. O usuário deve entrar uma linha em branco para indicar que não há mais
pessoas no grupo. Depois disso, seu programa deve exibir uma mensagem informando o
preço total de todas as entradas para o grupo. O valor deve ser exibido com duas casas
decimais.
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int sum = 0;
    char input[5];
    while (1)
    {
        fgets(input, 5, stdin);
        if (*input == '\n')
            break;

        int age = atoi(input);
        if (age < 0 || age > 120)
            break;
        else if (age <= 2)
            sum += 0;
        else if (age <= 12)
            sum += 14;
        else if (age < 65)
            sum += 23;
        else
            sum += 18;
    }

    printf("Valor total: %.2d\n", sum);

    return 0;
}
