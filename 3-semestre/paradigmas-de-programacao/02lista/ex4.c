#include <stdio.h>

int fib(int n) {
    if (n == 0) {
        return 0;
    }
    else if (n == 1) {
        return 1;
    }

    return fib(n - 1) + fib(n - 2);
}

int main() {
    int fib10 = fib(10);
    printf("%d\n", fib10);
    for (int i = 0; i < 11; ++i) {
        printf("%d\n", fib(i));
    }
}
