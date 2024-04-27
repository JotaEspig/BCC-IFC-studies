#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int is_prime(int n) {
    if (n == 0 || n == 1) {
        return 0;
    }

    for (int i = 2; i <= n / 2; ++i) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    srand(time(NULL));
    int total = 0;
    int primes = 0;
    while (primes < 25) {
        int random = (rand() % 100) + 1;

        ++total;
        if (is_prime(random)) {
            ++primes;
        }
    }
    printf("%d\n", total);
}
