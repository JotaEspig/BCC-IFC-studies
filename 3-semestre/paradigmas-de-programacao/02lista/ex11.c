/*
Altere o exercício 5 para que ele pare somente quando encontrar os 25 números
primos existentes entre 1 e 100, isto é, os 25 números primos devem ser
diferentes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUCKETS_SIZE 100

typedef struct ll_node {
    int value;
    struct ll_node *next;
} *ll_node_t;

ll_node_t ll_node_new(int value) {
    ll_node_t node = malloc(sizeof(struct ll_node));
    node->value = value;
    node->next = NULL;
    return node;
}

void ll_node_print(ll_node_t node) {
    if (node == NULL) {
        printf("\n");
        return;
    }

    printf("%d", node->value);
    if (node->next != NULL)
        printf(", ");
    ll_node_print(node->next);
}

typedef struct set {
    ll_node_t *buckets;
    int amount;
} *set_t;

set_t set_new() {
    set_t set = malloc(sizeof(struct set));
    set->buckets = calloc(BUCKETS_SIZE, sizeof(ll_node_t));
    set->amount = 0;
    return set;
}

int hash(int value) {
    return ((value - 1) % BUCKETS_SIZE + BUCKETS_SIZE) % BUCKETS_SIZE;
}

set_t set_append(set_t set, int value) {
    if (set == NULL) {
        return NULL;
    }

    int index = hash(value);
    ll_node_t *node = &set->buckets[index];
    if (*node == NULL) {
        *node = ll_node_new(value);
        ++set->amount;
        return set;
    }

    while (*node != NULL) {
        if ((*node)->value == value) {
            return set;
        }

        node = &(*node)->next;
    }

    *node = ll_node_new(value);
    ++set->amount;
    return set;
}

int set_value_is_in(set_t set, int value) {
    if (set == NULL) {
        return 0;
    }

    int index = hash(value);
    ll_node_t *node = &set->buckets[index];
    while (*node != NULL) {
        if ((*node)->value == value) {
            return 1;
        }

        node = &(*node)->next;
    }

    return 0;
}

void set_print(set_t set) {
    if (set == NULL) {
        return;
    }

    for (int i = 0; i < BUCKETS_SIZE; ++i) {
        ll_node_t node = set->buckets[i];
        if (node) {
            ll_node_print(node);
        }
    }
}

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
    set_t set = set_new();
    int total = 0;
    int primes = 0;
    while (primes < 25) {
        int random = (rand() % 100) + 1;

        ++total;
        if (is_prime(random) && !set_value_is_in(set, random)) {
            set_append(set, random);
            ++primes;
        }
    }
    printf("%d\n", total);
    set_print(set);
}
