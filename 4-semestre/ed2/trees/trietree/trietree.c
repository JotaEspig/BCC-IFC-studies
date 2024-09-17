#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trietree.h"

tt_node_t *trie_tree_create() {
    tt_node_t *node = malloc(sizeof(tt_node_t));
    if (node == NULL) {
        return NULL;
    }

    node->is_end_of_word = false;
    node->character = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }

    return node;
}

void trie_tree_insert(tt_node_t *root, const char *word) {
    tt_node_t *current = root;
    while (*word) {
        int index = *word - 'a';
        if (current->children[index] == NULL) {
            current->children[index] = trie_tree_create();
            current->children[index]->character = *word;
        }
        current = current->children[index];
        ++word;
    }
    current->is_end_of_word = true;
}

bool trie_tree_search(tt_node_t *root, const char *word) {
    tt_node_t *current = root;
    while (*word) {
        int index = *word - 'a';
        if (current->children[index] == NULL) {
            return false;
        }
        current = current->children[index];
        ++word;
    }
    return current->is_end_of_word;
}

void trie_tree_destroy(tt_node_t *root) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i] != NULL) {
            trie_tree_destroy(root->children[i]);
        }
    }
    free(root);
}
