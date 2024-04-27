#include <stdio.h>

int fib(int n) {
    if (n <= 0) {
        return 0;
    }

    int ini1 = 0;
    int ini2 = 1;
    while (n > 1) {
        ini2 = ini1 + ini2;
        ini1 = ini2 - ini1;
        --n;
    }

    return ini2;
}

int main() {
    int fib10 = fib(10);
    printf("%d\n", fib10);
    for (int i = 0; i < 11; ++i) {
        printf("%d\n", fib(i));
    }
}
