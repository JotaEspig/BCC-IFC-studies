#include "avl.h"

int main() {
    avl_tree_t *tree = avl_create();
    for (int i = 0; i < 20; ++i) {
        avl_insert(tree, i * (i % 2 == 0 ? 1 : -1));
    }
    avl_node_print(tree->root, 0);
    return 0;
}
