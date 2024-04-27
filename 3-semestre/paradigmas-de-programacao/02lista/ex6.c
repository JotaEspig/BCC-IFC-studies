#include <stdio.h>

int is_friend(int n1, int n2) {
    int sum1 = 1;
    int sum2 = 1;

    for (int i = 2; i <= n1 / 2; ++i) {
        if (n1 % i == 0) {
            sum1 += i;
        }
    }

    for (int i = 2; i <= n2 / 2; ++i) {
        if (n2 % i == 0) {
            sum2 += i;
        }
    }

    return sum1 == n2 && sum2 == n1;
}

int main() {
    printf("%d\n", is_friend(220, 284));
}
