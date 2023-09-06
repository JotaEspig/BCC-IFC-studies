#include <stdio.h>
#include <stdlib.h>

#include "binarytree.h"

bt_node_t *bt_new_node(int data) {
    bt_node_t *node =
        (bt_node_t *) malloc(sizeof(bt_node_t));

    node->left = NULL;
    node->right = NULL;
    node->data = data;

    return node;
}

bt_node_t *bt_insert(bt_node_t *root, int data) {
    bt_node_t *node = bt_new_node(data);
    if (root == NULL)
        return node;
    
    bt_node_t *current = root;
    while (1) {
        if (data < current->data) {
            if (current->left == NULL) {
                current->left = node;
                break;
            }

            current = current->left;
        }
        else {
            if (current->right == NULL) {
                current->right = node;
                break;
            }

            current = current->right;
        }
    }

    return root;
}

bt_node_t *bt_search(bt_node_t *root, int data) {
    bt_node_t *current = root;
    while (current != NULL) {
        if (data < current->data) {
            current = current->left;
        }
        else if (data > current->data) {
            current = current->right;
        }
        else {
            return current;
        }
    }

    return NULL;
}

void bt_print(bt_node_t *node) {
    if (node) {
        bt_print(node->left);
        printf("%d ", node->data);
        bt_print(node->right);
    }
}
