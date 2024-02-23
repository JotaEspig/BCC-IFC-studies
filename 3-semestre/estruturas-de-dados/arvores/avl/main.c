#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

int main()
{
    avl_node_t node = avl_node_new(1);
    if (node == NULL)
    {
        perror("Memory allocation failed");
        exit(1);
    }
    for (int i = 2; i < 120000000; ++i)
        avl_node_insert(&node, i);

    printf("%p\n", node);
    // avl_node_beautiful_print(node, 0);

    printf("\n");
    avl_node_print(node);
    printf("\n");

    avl_node_t value = avl_node_search(node, 7500);
    assert(value != NULL);
    printf("Found value: %d\n", value->value);

    //avl_node_destroy(&node);
    //assert(node == NULL);
    printf("sizeof(struct avl_node): %ld\n", sizeof(struct avl_node));
    return 0;
}
