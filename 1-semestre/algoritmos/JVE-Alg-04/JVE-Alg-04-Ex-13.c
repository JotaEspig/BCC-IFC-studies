/*
Fatoração numérica. A fatoração de um número inteiro n pode ser feita por meio de números
primos de acordo com o procedimento descrito abaixo:
Inicialize fator com valor 2
Enquanto fator for menor ou igual a n, faça
Se n for divisível por fator então
Concluímos que fator faz parte da fatoração de n
Faça divisão inteira de n por fator
Senão
Incremente fator em uma unidade
Escreva um programa Python que lê um número inteiro do usuário. Se o valor fornecido pelo
usuário é menor do que 2, seu programa deve exibir uma mensagem de erro. Caso contrário,
seu programa deve exibir os números primos que podem ser multiplicados para formar o
número n, com um fator exibido em cada linha. Por exemplo:
Digite um número inteiro (maior ou igual a 2): 72
2
2
2
3
3
*/

#include <stdio.h>

int main(void)
{
    int x;
    printf("Digite: ");
    scanf("%d", &x);

    int fator = 2;
    while (fator <= x)
    {
        if (x % fator == 0)
        {
            printf("%d\n", fator);
            x /= fator;
        }
        else
            fator++;
    }
    return 0;
}