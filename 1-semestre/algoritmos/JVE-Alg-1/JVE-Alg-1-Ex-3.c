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