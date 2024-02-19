#ifndef AVL_H
#define AVL_H

#include <stddef.h>

typedef struct avl_node
{
    int value;
    struct avl_node *left, *right;
    size_t height;
} *avl_node_t;

avl_node_t avl_node_new(int value);
void avl_node_rot_ll(avl_node_t *node);
void avl_node_rot_rr(avl_node_t *node);
void avl_node_rot_lr(avl_node_t *node);
void avl_node_rot_rl(avl_node_t *node);
void avl_node_print(avl_node_t node, int space);

#endif
