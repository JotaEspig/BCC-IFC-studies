/*
Área de um terreno. Crie um programa Python que leia as dimensões de um terreno em
metros (largura e profundidade), e exiba o resultado em hectares.
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
    printf("Largura do terreno (metros): ");
    char *str_width = read_input(10);
    printf("Profundidade do terreno (metros): ");
    char *str_length = read_input(10);
    float width = atof(str_width);
    float length = atof(str_length);
    float area_meters = width * length;
    float area_hectares = area_meters / 10000;
    printf("O terreno tem: %.2f hectares\n", area_hectares);
    return 0;
}
