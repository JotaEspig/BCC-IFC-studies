/*
Saudação. Escreva um programa que pergunte o nome do(a) usuário(a) e em seguida exiba
uma mensagem de “Olá" ao usuário, utilizando o nome fornecido.
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
    printf("Qual o seu nome?\n");
    char *str = read_input(80);
    if (str == NULL)
        exit(1);
    
    printf("Ola, %s\n", str);
}
