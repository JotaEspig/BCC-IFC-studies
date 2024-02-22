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
    for (int i = 2; i < 20; ++i)
        avl_node_insert(&node, i);

    printf("%p\n", node);
    avl_node_print(node, 0);

    avl_node_destroy(&node);
    assert(node == NULL);
    return 0;
}
