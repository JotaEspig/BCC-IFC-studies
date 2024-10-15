#include <stdio.h>
#include <stdlib.h>

#include "btree.h"

int main() {
    bt_node_t *root = bt_create();
    char buff[10];
    int key;
    while (scanf("%s", buff) != EOF && scanf("%d", &key) != EOF) {
        // Busca
        if (*buff == 'b') {
            bt_node_t *node = bt_search(root, key);
            if (node != NULL) {
                printf("Valor %d encontrado!\n", key);
            }
            else {
                printf("Valor %d não encontrado!\n", key);
            }
        }
        // Insere
        else if (*buff == 'i') {
            root = bt_insert(root, key);
        }
        // Percorre
        else {
            printf("Percurso da árvore B em ordem:");
            bt_print_in_order(root);
            printf("\n");
        }
    }

    bt_destroy(root);
    return 0;
}
