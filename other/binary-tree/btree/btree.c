#include <stdlib.h>

#include "btree.h"

bt_node_t *bt_new_node(int data) {
    bt_node_t *node =
        (bt_node_t *) malloc(sizeof(bt_node_t));

    node->left = NULL;
    node->right = NULL;
    node->data = data;

    return node;
}