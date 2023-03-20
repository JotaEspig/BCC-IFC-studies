#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Compile with: gcc JVE-Alg-1-Ex-10.c -o main -lm

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
