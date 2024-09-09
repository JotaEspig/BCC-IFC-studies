#include <stdio.h>

#include "unordered_map.h"

int main() {
    printf("Hello, World!\n");
    unordered_map_t *um = unordered_map_init();
    for (int i = 0; i < 10; i++) {
        unordered_map_insert(um, i * 100, i * 2 + 1);
    }

    for (int i = 0; i < BUCKETS_SIZE; ++i) {
        dll_t *node = um->buckets[i];
        if (node == NULL) {
            continue;
        }
        printf("%p:\n", node);
        dll_print(node);
    }
    printf("Key: %d -> %d\n", 3, unordered_map_get(um, 3));
    return 0;
}
