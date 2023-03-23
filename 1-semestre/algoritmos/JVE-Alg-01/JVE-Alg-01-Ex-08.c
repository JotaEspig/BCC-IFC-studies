/*
Bugigangas e quinquilharias. Uma loja online oferece aos seus clientes dois tipos de
produto: bugigangas e quinquilharias. Cada bugiganga pesa 75 gramas e cada quinquilharia
pesa 112 gramas. Faça um programa Python que leia a quantidade de bugigangas e a
quantidade de quinquilharias de um pedido do usuário. A seguir, seu programa deve calcular e
exibir o peso total do pedido.
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
    printf("Quantas bugigangas? ");
    char *str_bugigangas = read_input(10);
    printf("Quantas quinquilharias? ");
    char *str_quinquilharias = read_input(10);

    int bugigangas     = (int) atoi(str_bugigangas);
    int quinquilharias = (int) atoi(str_quinquilharias);
    int total_grams = bugigangas * 75 + quinquilharias * 112;
    float total_kg = (float) total_grams / 1000;

    printf("Total grams: %d\nTotal kg: %.3f\n", total_grams, total_kg);
}
