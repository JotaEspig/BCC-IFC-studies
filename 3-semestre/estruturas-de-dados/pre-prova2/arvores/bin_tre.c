#include "bin_tre.h"

#include <stdio.h>
#include <stdlib.h>

bt_node_t bt_init(void) {
    return NULL;
}

bt_node_t bt_init_with_data(int data, bt_node_t left, bt_node_t right) {
    bt_node_t node = bt_init();
    node = (bt_node_t)calloc(1, sizeof(struct bt_node));
    node->data = data;
    node->left = left;
    node->right = right;
    return node;
}

bt_node_t bt_insert(bt_node_t *node, int data) {
    if (node == NULL)
        return NULL;

    if (*node == NULL) {
        *node = bt_init_with_data(data, NULL, NULL);
        return *node;
    }

    if ((*node)->data > data) {
        return bt_insert(&(*node)->left, data);
    }
    else {
        return bt_insert(&(*node)->right, data);
    }
}

bt_node_t bt_search(bt_node_t node, int data) {
    if (node == NULL)
        return NULL;

    if (node->data > data) {
        return bt_search(node->left, data);
    }
    else if (node->data < data) {
        return bt_search(node->right, data);
    }
    else {
        return node;
    }
}

bt_node_t *bt_inorder_sucessor(bt_node_t *node) {
    if (node == NULL || *node == NULL)
        return NULL;

    if ((*node)->left == NULL) {
        return node;
    }
    else {
        return bt_inorder_sucessor(&(*node)->left);
    }
}

void bt_remove(bt_node_t *node, int data) {
    if (node == NULL || *node == NULL)
        return;

    if ((*node)->data > data) {
        bt_remove(&(*node)->left, data);
    }
    else if ((*node)->data < data) {
        bt_remove(&(*node)->right, data);
    }
    else {
        if ((*node)->left == NULL) {
            if ((*node)->right == NULL) {
                bt_destroy(node);
            }
            else {
                bt_node_t right = (*node)->right;
                bt_destroy(node);
                *node = right;
            }
        }
        else {
            if ((*node)->right == NULL) {
                bt_node_t left = (*node)->left;
                bt_destroy(node);
                *node = left;
            }
            else {
                bt_node_t *next = bt_inorder_sucessor(&(*node)->right);
                int aux = (*next)->data;
                printf("Max: %d\n", aux);
                (*next)->data = data;
                (*node)->data = aux;
                bt_remove(next, data);
            }
        }
    }
}

void bt_destroy(bt_node_t *node) {
    if (node == NULL || *node == NULL)
        return;

    free(*node);
    *node = NULL;
}

void bt_destroy_rec(bt_node_t *node) {
    if (node == NULL || *node == NULL)
        return;

    bt_destroy_rec(&(*node)->left);
    bt_destroy_rec(&(*node)->right);
    free(*node);
    *node = NULL;
}

void bt_print_infix(bt_node_t node) {
    if (node == NULL)
        return;

    bt_print_infix(node->left);
    printf("%d\n", node->data);
    bt_print_infix(node->right);
}

void bt_pretty_print(bt_node_t node, int space) {
    int step = 8;
    if (node == NULL) {
        return;
    }

    space += step;

    bt_pretty_print(node->right, space);

    printf("\n");
    for (int i = step; i < space; i++)
        printf(" ");
    printf("%d\n", node->data);

    bt_pretty_print(node->left, space);
}
