#ifndef BTREE_H
#define BTREE_H

typedef struct bt_node {
    int data;
    struct bt_node *left;
    struct bt_node *right;
} bt_node_t;

bt_node_t *bt_new_node(int data);

#endif // BTREE_H