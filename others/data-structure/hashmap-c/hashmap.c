#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "hashmap.h"

hmap_ll_node *hmap_ll_node_new(hmap_pair pair)
{
    hmap_ll_node *node = (hmap_ll_node *)malloc(sizeof(hmap_ll_node));
    node->pair = pair;
    node->next = NULL;
    return node;
}

void hmap_ll_insert(hmap_ll_node *node, hmap_pair pair)
{
    if (node == NULL)
        return;

    if (node->next == NULL)
    {
        hmap_ll_node *next = hmap_ll_node_new(pair);
        node->next = next;
        return;
    }

    hmap_ll_insert(node->next, pair);
}

void hmap_ll_set(hmap_ll_node *node, hmap_pair pair)
{
    if (node == NULL)
        return;

    if (node->pair.key == pair.key)
    {
        node->pair.value = pair.value;
        return;
    }
    else if (node->next == NULL)
        return hmap_ll_insert(node, pair);

    hmap_ll_set(node->next, pair);
}

int hmap_ll_find(hmap_ll_node *node, int key)
{
    if (node == NULL)
        return 0;

    if (node->pair.key == key)
        return node->pair.value;

    return hmap_ll_find(node->next, key);
}

void hmap_ll_print(hmap_ll_node *node)
{
    if (node == NULL)
        return;

    printf("Key: %d Value: %d\n", node->pair.key, node->pair.value);
    hmap_ll_print(node->next);
}

void hmap_ll_destroy(hmap_ll_node *node)
{
    if (node == NULL)
        return;

    hmap_ll_destroy(node->next);
    free(node);
}

hmap_map *hmap_map_new(size_t capacity)
{
    hmap_map *map = (hmap_map *)malloc(sizeof(hmap_map));
    map->size = 0;
    map->buckets_amount = capacity;
    map->v = (hmap_ll_node **)calloc(capacity, sizeof(hmap_ll_node *));
    for (size_t i = 0; i < capacity; ++i)
        map->v[i] = NULL;

    return map;
}

size_t hmap_map_hash(hmap_map *map, int key)
{
    return (key - 1) % map->buckets_amount;
}

int hmap_map_at(hmap_map *map, int key)
{
    int idx = hmap_map_hash(map, key);
    hmap_ll_node *head = map->v[idx];
    return hmap_ll_find(head, key);
}

void hmap_map_set(hmap_map *map, hmap_pair pair)
{
    int idx = hmap_map_hash(map, pair.key);
    hmap_ll_node *head = map->v[idx];
    if (head != NULL)
        hmap_ll_set(head, pair);
    else
        map->v[idx] = hmap_ll_node_new(pair);
}

void hmap_map_destroy(hmap_map *map)
{
    if (map == NULL || map->v == NULL)
        return;

    size_t capacity = map->buckets_amount;
    for (size_t i = 0; i < capacity; ++i)
        if (map->v[i] != NULL)
            hmap_ll_destroy(map->v[i]);

    free(map->v);
    map->v = NULL;
    free(map);
}
