#include "redblack.h"
#include <stdio.h>

int main() {
    // Hardcoded valores de entrada 12 5 15 3 10 13 17 4 7 11 14 6 8
    rb_node_t *root = NULL;
    int n;
    while (scanf("%d", &n) != EOF) {
        if (root == NULL) {
            root = rb_new(n);
        }
        else {
            rb_insert(root, n);
        }
    }

    printf("Percurso em ordem: ");
    rb_print_in_order(root);
    printf("\n");
    printf("Raiz: %d\n", root->data);
    printf("Altura: %lu\n", RB_HEIGHT(root));
    printf("Quantidade de nós vermelhos: %lu\n", rb_count_type(root, RED));
    printf("Quantidade de nós pretos: %lu\n", rb_count_type(root, BLACK));

    rb_destroy_rec(&root);
    return 0;
}
