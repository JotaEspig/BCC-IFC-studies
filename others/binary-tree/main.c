#include <stdio.h>
#include <stdlib.h>

#include "binarytree/binarytree.h"

int main() {
    bt_node_t *node;
    bt_node_t *root = bt_new_node(10);
    bt_insert(root, 15);
    bt_insert(root, 7);
    bt_insert(root, 13);
    bt_insert(root, 4);
    bt_insert(root, 199);
    bt_insert(root, 8);

    bt_print(root);
    return 0;
}
