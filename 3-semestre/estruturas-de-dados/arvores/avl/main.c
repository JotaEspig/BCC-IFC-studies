#include <assert.h>
#include <stdio.h>

#include "avl.h"

int main()
{
    avl_node_t node = avl_node_new(1);
    node->left = avl_node_new(-5);
    node->right = avl_node_new(10);
    node->right->left = avl_node_new(5);
    node->right->right = avl_node_new(15);
    node->right->left->left = avl_node_new(3);
    node->right->left->right = avl_node_new(9);
    node->right->left->right->left = avl_node_new(8);

    printf("%p\n", node);
    avl_node_print(node, 0);
    avl_node_rot_rl(&node);
    printf("%p\n", node);
    avl_node_print(node, 0);

    avl_node_destroy(&node);
    assert(node == NULL);
    return 0;
}
