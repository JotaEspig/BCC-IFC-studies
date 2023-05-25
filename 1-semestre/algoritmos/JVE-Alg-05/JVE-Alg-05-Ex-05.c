/*
Números ordinais. Palavras como primeiro, segundo e terceiro são chamadas de números
ordinais. Neste exercício, você deve escrever uma função que recebe um inteiro como seu
único parâmetro e retorna uma string contendo o número ordinal em português como seu
único resultado. Sua função deve lidar com números inteiros entre 1 e 12 (inclusive). Ela deve
retornar uma string vazia se um valor fora desse intervalo for fornecido como um parâmetro.
Inclua um programa principal que demonstra sua função exibindo cada inteiro de 1 a 12 e seu
respectivo número ordinal.
*/

#include <stdio.h>

char *ordinal(int val)
{
    switch (val)
    {
    case 1:
        return "primeiro";
    case 2:
        return "segundo";
    case 3:
        return "terceiro";
    case 4:
        return "quarto";
    case 5:
        return "quinto";
    case 6:
        return "sexto";
    case 7:
        return "setimo";
    case 8:
        return "oitavo";
    case 9:
        return "nono";
    case 10:
        return "decimo";
    case 11:
        return "decimo primeiro";
    case 12:
        return "decimo segundo";
    default:
        return "";
    }
}

int main(void)
{
    int a;
    printf("Num: ");
    scanf("%d", &a);
    printf("%s\n", ordinal(a));

    return 0;
}
