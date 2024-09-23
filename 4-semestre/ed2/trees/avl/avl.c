#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

#define max(a, b) ((a) > (b) ? (a) : (b))

avl_tree_t *avl_create() {
    avl_tree_t *tree = malloc(sizeof(avl_tree_t));
    tree->root = NULL;
    return tree;
}

avl_tree_t *avl_insert(avl_tree_t *tree, int new_key) {
    tree->root = avl_node_insert(tree->root, new_key);
    return tree;
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
    node->height = 1;
    return node;
}

uint64_t avl_node_height(avl_node_t *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

avl_node_t *avl_node_insert(avl_node_t *node, int new_key) {
    if (node == NULL) {
        return avl_node_create(new_key);
    }

    if (new_key < node->key) {
        node->left = avl_node_insert(node->left, new_key);
    }
    else if (new_key > node->key) {
        node->right = avl_node_insert(node->right, new_key);
    }
    else {
        return node;
    }

    node->height
        = 1 + max(avl_node_height(node->left), avl_node_height(node->right));

    int balance = avl_node_height(node->left) - avl_node_height(node->right);

    if (balance > 1 && new_key < node->left->key) {
        return avl_node_r_rotate(node);
    }

    if (balance < -1 && new_key > node->right->key) {
        return avl_node_l_rotate(node);
    }

    if (balance > 1 && new_key > node->left->key) {
        node->left = avl_node_l_rotate(node->left);
        return avl_node_r_rotate(node);
    }

    if (balance < -1 && new_key < node->right->key) {
        node->right = avl_node_r_rotate(node->right);
        return avl_node_l_rotate(node);
    }

    return node;
}

avl_node_t *avl_node_l_rotate(avl_node_t *node) {
    avl_node_t *new_root = node->right;
    node->right = new_root->left;
    new_root->left = node;

    node->height
        = 1 + max(avl_node_height(node->left), avl_node_height(node->right));
    new_root->height
        = 1
          + max(
              avl_node_height(new_root->left), avl_node_height(new_root->right)
          );

    return new_root;
}

avl_node_t *avl_node_r_rotate(avl_node_t *node) {
    avl_node_t *new_root = node->left;
    node->left = new_root->right;
    new_root->right = node;

    node->height
        = 1 + max(avl_node_height(node->left), avl_node_height(node->right));
    new_root->height
        = 1
          + max(
              avl_node_height(new_root->left), avl_node_height(new_root->right)
          );

    return new_root;
}

void avl_node_print(avl_node_t *node, int indent) {
    if (node == NULL) {
        return;
    }

    avl_node_print(node->left, indent + 4);
    for (int i = 0; i < indent; ++i)
        printf(" ");
    printf("%c%d\n", node->key >= 0 ? ' ' : '-', abs(node->key));
    avl_node_print(node->right, indent + 4);
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
