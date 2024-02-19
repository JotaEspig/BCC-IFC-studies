#include "avl.h"
#include <stdio.h>

int main()
{
    avl_node_t node = avl_node_new(0);
    node->left = avl_node_new(-2);
    node->right = avl_node_new(1);
    node->left->left = avl_node_new(-3);
    node->left->right = avl_node_new(-1);
    node->left->left->left = avl_node_new(-4);
    printf("%p\n", node);
    avl_node_print(node, 0);
    avl_node_rot_ll(&node);
    printf("%p\n", node);
    avl_node_print(node, 0);
    avl_node_rot_rr(&node);
    printf("%p\n", node);
    avl_node_print(node, 0);
    return 0;
}
