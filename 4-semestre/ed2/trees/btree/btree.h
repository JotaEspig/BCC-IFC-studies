#ifndef BTREE_H
#define BTREE_H

typedef struct bt_node {
    int data;
    struct bt_node *left;
    struct bt_node *right;
} bt_node_t;

#endif // BTREE_H
