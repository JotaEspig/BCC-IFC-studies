/*
Centralizando uma string. Escreva uma função que recebe uma string como seu primeiro
parâmetro e a largura de uma linha do terminal em caracteres como seu segundo parâmetro.
Sua função deve retornar uma nova string que consiste na string original e no número correto
de espaços iniciais para que a string original apareça centralizada dentro da largura fornecida
quando for impressa. Não adicione nenhum caractere ao final da string. Inclui um programa
principal que demonstre sua função.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *centralize(char *str, int width)
{
    char *new_str = (char *)calloc(width + 1, sizeof(char));
    size_t str_len = strlen(str);

    if (str_len > width + 1)
        return str;

    int left = (width - str_len) / 2;
    int right = width - str_len - left;
    for (int i = 0; i < left; i++)
        new_str[i] = ' ';
    for (int j = left; j < left + str_len; j++)
        new_str[j] = str[j - left];
    for (int k = left + str_len; k < width; k++)
        new_str[k] = ' ';

    return new_str;
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("passe os dois argumento\n ./main <str> <largura>\n");
        return -1;
    }

    printf("|%s|\n", centralize(argv[1], atoi(argv[2])));

    return 0;
}
