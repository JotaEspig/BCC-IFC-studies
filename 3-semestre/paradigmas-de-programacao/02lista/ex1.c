#include <stdio.h>

int fat(int n) {
    int product = 1;
    while (n > 1) {
        product *= n;
        --n;
    }
    return product;
}

int main() {
    int result = fat(5);
    printf("%d\n", result);
}
