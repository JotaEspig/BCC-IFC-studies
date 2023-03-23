/*
Juros compostos. Faça de conta que você acabou de abrir uma conta de investimento que
rende 12% de juros ao ano. Os juros que você ganha são pagos ao final do ano. Escreva um
programa que começa lendo do usuário o valor inicial depositado na conta. Em seguida, o
programa deve computar e exibir o saldo da conta de investimento após 1, 2 e 3 anos. Exiba
cada valor com exatamente 2 casas decimais.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_input(int strlength) {
    char *str = (char *) calloc(strlength, sizeof(char));
    if (fgets(str, strlength, stdin) == NULL)
        return NULL;

    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';

    return str;
}

int main() {
    printf("Valor inicial: ");
    char *str = read_input(20);

    double initial = atof(str);
    double first = initial * 1.12;
    double second = first * 1.12;
    double third = second * 1.12;
    printf("Inicial: %.2lf\n"
           "Primeiro ano: %.2lf\n"
           "Segundo ano: %.2lf\n"
           "Terceiro ano: %.2lf\n", initial, first, second, third);
    return 0;
}
