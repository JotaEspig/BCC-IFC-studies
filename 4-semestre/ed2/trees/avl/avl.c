#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

avl_tree_t *avl_create() {
    avl_tree_t *tree = malloc(sizeof(avl_tree_t));
    tree->root = NULL;
    return tree;
}

avl_tree_t *avl_insert(avl_tree_t **tree, int new_key) {
    if (*tree == NULL) {
        return NULL;
    }
    avl_node_t **curr = &(*tree)->root;
    while (*curr != NULL) {
        if ((*curr)->key > new_key) {
            curr = &(*curr)->right;
        }
        else {
            curr = &(*curr)->left;
        }
    }

    *curr = avl_node_create(new_key);
    return *tree;
}

void avl_destroy(avl_tree_t **tree) {
    if (*tree == NULL) {
        return;
    }

    free(*tree);
    *tree = NULL;
}

avl_node_t *avl_node_create(int new_key) {
    avl_node_t *node = (avl_node_t *)malloc(sizeof(avl_node_t));
    node->key = new_key;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->height = 1;
    return node;
}

void avl_node_print(avl_node_t *node, int indent) {
    if (node == NULL) {
        return;
    }

    avl_node_print(node->left, indent + 4);
    avl_node_print(node->right, indent + 4);
    for (int i = 0; i < indent; ++i)
        printf(" ");
    printf("%d\n", node->key);
}

void avl_node_destroy(avl_node_t **node) {
    if (*node == NULL) {
        return;
    }
    free(*node);
    *node = NULL;
}

void avl_node_destroy_recursive(avl_node_t **node) {
    if (*node == NULL) {
        return;
    }
    avl_node_destroy_recursive(&(*node)->left);
    avl_node_destroy_recursive(&(*node)->right);
    avl_node_destroy(node);
}
