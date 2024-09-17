#include <stdio.h>

#include "trietree.h"

int main() {
    printf("Hello, World!\n");
    tt_node_t *root = trie_tree_create();
    trie_tree_insert(root, "hello");
    trie_tree_insert(root, "world");
    printf("Search for 'hello': %d\n", trie_tree_search(root, "hel"));
    return 0;
}
