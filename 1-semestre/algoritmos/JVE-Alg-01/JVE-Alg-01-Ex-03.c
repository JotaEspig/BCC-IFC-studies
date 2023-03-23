/*
Área de uma sala. Escreva um programa Python que peça para o usuário os comprimentos
da largura e profundidade de uma sala. Após a leitura dos valores, seu programa deve exibir a
área da sala. A largura e a profundidade devem ser números reais. Inclua as unidades nas
mensagens de entrada e saída (metros e metros quadrados).
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
    printf("Largura da sala (metros): ");
    char *str_width = read_input(10);
    printf("Profundidade da sala (metros): ");
    char *str_length = read_input(10);
    float width = atof(str_width);
    float length = atof(str_length);
    float area = width * length;
    printf("A sala tem: %.2f metros quadrados\n", area);
}
