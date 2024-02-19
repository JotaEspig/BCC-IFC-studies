#include <stdio.h>

#include "avl.h"

int main()
{
    avl_node_t node = avl_node_new(1);
    node->left = avl_node_new(-5);
    node->right = avl_node_new(5);
    node->left->left = avl_node_new(-10);
    node->left->right = avl_node_new(-1);
    node->left->right->left = avl_node_new(-3);
    node->left->right->right = avl_node_new(0);
    node->left->right->left->right = avl_node_new(-2);
    printf("%p\n", node);
    avl_node_print(node, 0);
    avl_node_rot_lr(&node);
    printf("%p\n", node);
    avl_node_print(node, 0);
    //    avl_node_rot_ll(&node);
    //    printf("%p\n", node);
    //    avl_node_print(node, 0);
    //    avl_node_rot_rr(&node);
    //    printf("%p\n", node);
    //    avl_node_print(node, 0);
    return 0;
}
