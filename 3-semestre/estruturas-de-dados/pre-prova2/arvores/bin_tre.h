#ifndef BIN_TRE_H
#define BIN_TRE_H

#include <stddef.h>

typedef struct bt_node {
    int data;
    struct bt_node *left;
    struct bt_node *right;
} *bt_node_t;

bt_node_t bt_init(void);
bt_node_t bt_init_with_data(int data, bt_node_t left, bt_node_t right);
bt_node_t bt_insert(bt_node_t *node, int data);
bt_node_t bt_search(bt_node_t node, int data);
bt_node_t *bt_inorder_sucessor(bt_node_t *node);
void bt_remove(bt_node_t *node, int data);
void bt_destroy(bt_node_t *node);
void bt_destroy_rec(bt_node_t *node);
void bt_print_infix(bt_node_t node);
void bt_pretty_print(bt_node_t p, int indent);
#endif // BIN_TRE_H
