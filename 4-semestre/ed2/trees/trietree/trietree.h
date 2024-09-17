#ifndef TRIETREE_H
#define TRIETREE_H

#include <stdbool.h>

#define ALPHABET_SIZE 26

typedef struct tt_node {
    struct tt_node *children[ALPHABET_SIZE];
    char character;
    bool is_end_of_word;
} tt_node_t;

tt_node_t *trie_tree_create();
void trie_tree_insert(tt_node_t *root, const char *word);
bool trie_tree_search(tt_node_t *root, const char *word);
void trie_tree_destroy(tt_node_t *root);

#endif // TRIETREE_H
