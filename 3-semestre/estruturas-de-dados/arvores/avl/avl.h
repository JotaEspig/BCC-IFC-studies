#ifndef AVL_H
#define AVL_H

#include <stddef.h>

typedef struct avl_node
{
    int value;
    size_t height;
    struct avl_node *left, *right;
} *avl_node_t;

avl_node_t avl_node_new(int value);
void avl_node_insert(avl_node_t *node, int value);
avl_node_t avl_node_search(avl_node_t node, int value);
avl_node_t avl_node_min_value(avl_node_t node);
void avl_node_delete(avl_node_t *node, int value);
size_t avl_node_height(avl_node_t node);
void avl_node_set_height(avl_node_t node);
long avl_node_balance(avl_node_t node);

void avl_node_rot(avl_node_t *node);
void avl_node_rot_ll(avl_node_t *node);
void avl_node_rot_rr(avl_node_t *node);
void avl_node_rot_lr(avl_node_t *node);
void avl_node_rot_rl(avl_node_t *node);
void avl_node_print(avl_node_t node);
void avl_node_beautiful_print(avl_node_t node, int space);
void avl_node_destroy(avl_node_t *node);

#endif
