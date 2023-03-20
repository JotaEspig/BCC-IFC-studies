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
}