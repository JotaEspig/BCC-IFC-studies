#include <stdio.h>
#include <stdlib.h>

#include "unordered_map.h"

void dll_print(dll_t *node) {
    while (node != NULL) {
        printf("Key: %d, Value: %d\n", node->key, node->value);
        node = node->next;
    }
}

unordered_map_t *unordered_map_init() {
    unordered_map_t *um = (unordered_map_t *)malloc(sizeof(unordered_map_t));
    um->size = 0;
    for (int i = 0; i < BUCKETS_SIZE; i++) {
        um->buckets[i] = NULL;
    }
    return um;
}

int unordered_map_hash(int value) {
    return value % BUCKETS_SIZE;
}

void unordered_map_insert(unordered_map_t *um, int key, int value) {
    int hash = unordered_map_hash(key);
    dll_t *node = (dll_t *)malloc(sizeof(dll_t));
    node->key = key;
    node->value = value;
    node->next = um->buckets[hash];
    node->prev = NULL;
    um->buckets[hash] = node;
    um->size++;
}

int unordered_map_get(unordered_map_t *um, int key) {
    int hash = unordered_map_hash(key);
    dll_t *node = um->buckets[hash];
    while (node != NULL) {
        if (node->key == key) {
            return node->value;
        }
        node = node->next;
    }
    unordered_map_insert(um, key, 0);
    return 0;
}

void unordered_map_destroy(unordered_map_t **um) {
    for (int i = 0; i < BUCKETS_SIZE; i++) {
        dll_t *node = (*um)->buckets[i];
        while (node != NULL) {
            dll_t *temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(*um);
    *um = NULL;
}
