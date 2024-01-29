#include <stdio.h>

#include "hashmap.h"

int main(void)
{
    /*
    hmap_ll_node *head = hmap_ll_node_new((hmap_pair){1, 2});
    hmap_ll_insert(head, (hmap_pair){2, 4});
    hmap_ll_insert(head, (hmap_pair){3, 6});
    hmap_ll_insert(head, (hmap_pair){4, 8});

    printf("Found value: %d\n", hmap_ll_find(head, 4));
    hmap_ll_set(head, (hmap_pair){5, 10});
    printf("Found value: %d\n", hmap_ll_find(head, 5));

    hmap_ll_print(head);
    hmap_ll_destroy(head);
    */
    hmap_map *map = hmap_map_new(10);
    hmap_map_set(map, (hmap_pair){1, 5});
    int val = hmap_map_at(map, 1);
    printf("Key: %d Value: %d\n", 1, val);
    hmap_map_destroy(map);
    return 0;
}
