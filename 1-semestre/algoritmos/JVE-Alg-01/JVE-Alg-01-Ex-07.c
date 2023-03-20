#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Argumentos de linha de comando invalidos.\n"
               "use: ./<programa> <n>\n");
        exit(1);
    }

    int n = atoi(argv[1]);
    long unsigned int total = (n * (n + 1)) / 2;
    printf("%d -> %lu\n", n, total);
}
