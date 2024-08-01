#include <stdio.h>
#include <stdlib.h>

#include "bin_tre.h"

int main(void) {
    printf("Hello, World!\n");
    bt_node_t root = bt_init();
    for (int i = 0; i < 10; ++i) {
        int data = rand() % 100;
        printf("d: %d\n", data);
        bt_insert(&root, data);
    }
    bt_insert(&root, 42);
    bt_pretty_print(root, 0);
    bt_print_infix(root);
    bt_node_t a = bt_search(root, 35);
    if (a->left == NULL && a->right == NULL)
        printf("NO CHILD\n");
    else if (a->left || a->right)
        printf("ONE CHILD\n");
    else
        printf("TWO CHILDREN\n");

    bt_remove(&root, 35);
    bt_pretty_print(root, 0);
    bt_print_infix(root);
    bt_destroy_rec(&root);
    return 0;
}
