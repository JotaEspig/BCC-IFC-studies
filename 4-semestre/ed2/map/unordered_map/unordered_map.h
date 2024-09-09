#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

#define BUCKETS_SIZE 100

typedef struct dll {
    int key;
    int value;
    struct dll *next;
    struct dll *prev;
} dll_t;

void dll_print(dll_t *node);

typedef struct unordered_map {
    int size;
    dll_t *buckets[BUCKETS_SIZE];
} unordered_map_t;

unordered_map_t *unordered_map_init();
int unordered_map_hash(int value);
void unordered_map_insert(unordered_map_t *um, int key, int value);
int unordered_map_get(unordered_map_t *um, int key);
void unordered_map_destroy(unordered_map_t **um);

#endif // UNORDERED_MAP_H
