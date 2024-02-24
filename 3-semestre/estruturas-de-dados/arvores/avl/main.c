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
    for (int i = 2; i < 12; ++i)
        avl_node_insert(&node, i);

    printf("%p\n", node);
    avl_node_beautiful_print(node, 0);

    printf("\n");
    avl_node_print(node);
    printf("\n");

    for (int i = 4; i < 9; ++i)
    {
        avl_node_t value = avl_node_search(node, i);
        assert(value != NULL);
        printf("Found value: %d\n", value->value);

        avl_node_delete(&node, i);

        value = avl_node_search(node, i);
        assert(value == NULL);
        printf("Found pointer: %p\n", value);

        printf("%p\n", node);
        avl_node_beautiful_print(node, 0);

        printf("\n");
        avl_node_print(node);
        printf("\n");
    }


    avl_node_destroy(&node);
    assert(node == NULL);
    printf("sizeof(struct avl_node): %ld\n", sizeof(struct avl_node));
    return 0;
}
