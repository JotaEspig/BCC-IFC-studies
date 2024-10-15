#include <stdio.h>
#include <string.h>

#include "trietree.h"

int main() {
    tt_node_t *root = trie_tree_create();
    char buffer[100];
    // Le do arquivo rockyou-menor.txt
    FILE *file = fopen("rockyou-menor.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    while (fgets(buffer, 100, file) != NULL) {
        // Remove o caractere de nova linha
        buffer[strcspn(buffer, "\n")] = 0;
        trie_tree_insert(root, buffer);
    }
    fclose(file);

    while (fgets(buffer, 100, stdin) != NULL) {
        // Remove o caractere de nova linha
        buffer[strcspn(buffer, "\n")] = 0;
        tt_node_t *found = trie_tree_search(root, buffer);
        if (found) {
            trie_tree_print(found, buffer, 1);
        }
        else {
            printf("Nenhuma senha encontrada com esse prefixo.\n");
        }
    }

    trie_tree_destroy(root);
    return 0;
}
