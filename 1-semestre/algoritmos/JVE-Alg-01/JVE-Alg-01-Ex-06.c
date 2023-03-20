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
    printf("Quanto custou o prato principal?\n");
    char *str_main_price = read_input(10);
    printf("Quanto custou o suco?\n");
    char *str_juice_price = read_input(10);
    printf("Quanto custou a sobremesa?\n");
    char *str_dessert_price = read_input(10);

    // It calculates in cents to avoid precision errors
    // when doing math with floats
    int main_price_cents    = (int) (atof(str_main_price) * 100);
    int juice_price_cents   = (int) (atof(str_juice_price) * 100);
    int dessert_price_cents = (int) (atof(str_dessert_price) * 100);
    float result_cents = (float) (main_price_cents  +
                                  juice_price_cents +
                                  dessert_price_cents) * 1.1;
    float result_reais = result_cents / 100;
    printf("O preço total foi: %.2f\n", result_reais);
}
