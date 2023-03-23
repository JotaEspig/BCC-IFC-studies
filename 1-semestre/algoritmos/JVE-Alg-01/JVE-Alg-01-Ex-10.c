/*
Aritmética. Escreva um programa Python que leia do usuário dois inteiros a e b. Seu
programa deve computar e exibir o seguinte:
• A soma de a e b
• A diferença quando b é subtraído de a
• O produto de a por b
• O quociente quando a é dividido por b
• O resto quando a é dividido por b
• O resultado de log10a
• O resultado de a^b
*/

// Compile with: gcc JVE-Alg-1-Ex-10.c -o main -lm

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Argumentos de linha de comando invalidos.\n"
               "use: ./<programa> <a> <b>\n");
        exit(1);
    }

    long int a = atoi(argv[1]);
    long int b = atoi(argv[2]);

    printf("a + b = %ld\n", a + b);
    printf("a - b = %ld\n", a - b);
    printf("a * b = %ld\n", a * b);
    printf("a / b = %.2f\n", (float) a / (float) b);
    printf("a %% b = %ld\n", a % b);
    printf("log10a = %.2f\n", log10((double) a));
    printf("a^b = %.2lf\n", pow((double) a, (double) b));
}
