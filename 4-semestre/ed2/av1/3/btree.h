#ifndef BTREE_H
#define BTREE_H

#define MAX_KEYS 3

typedef struct bt_node {
    int is_leaf;
    int num_keys;
    int keys[MAX_KEYS];
    struct bt_node *children[MAX_KEYS + 1];
} bt_node_t;

bt_node_t *bt_create();
bt_node_t *bt_insert(bt_node_t *root, int key);
void bt_insert_non_full(bt_node_t *root, int key);
void bt_split_child(bt_node_t *parent, int i, bt_node_t *child);
bt_node_t *bt_search(bt_node_t *root, int key);
void bt_print_in_order(bt_node_t *root);
void bt_destroy(bt_node_t *root);

#endif // BTREE_H
