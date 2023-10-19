#ifndef HASHMAP_H
#define HASHMAP_H

#include <stddef.h>

typedef struct hmap_pair
{
    int key;
    int value;
} hmap_pair;

typedef struct hmap_ll_node
{
    hmap_pair pair;
    struct hmap_ll_node *next;
} hmap_ll_node;

hmap_ll_node *hmap_ll_node_new(hmap_pair pair);
void hmap_ll_insert(hmap_ll_node *node, hmap_pair pair);
void hmap_ll_set(hmap_ll_node *node, hmap_pair pair);
int hmap_ll_find(hmap_ll_node *node, int key);
void hmap_ll_print(hmap_ll_node *node);
void hmap_ll_destroy(hmap_ll_node *node);

typedef struct hmap_map
{
    hmap_ll_node **v;
    size_t size;
    size_t capacity;
} hmap_map;

hmap_map *hmap_map_new(size_t capacity);
void hmap_map_destroy(hmap_map *map);

#endif // !HASHMAP_H
