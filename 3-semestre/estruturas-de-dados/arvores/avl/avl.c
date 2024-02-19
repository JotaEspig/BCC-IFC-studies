#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

avl_node_t avl_node_new(int value)
{
    avl_node_t node = malloc(sizeof(struct avl_node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void avl_node_rot_ll(avl_node_t *node)
{
    avl_node_t aux = (*node)->left;
    (*node)->left = aux->right;
    aux->right = *node;
    *node = aux;
}

void avl_node_rot_rr(avl_node_t *node)
{
    avl_node_t aux = (*node)->right;
    (*node)->right = aux->left;
    aux->left = *node;
    *node = aux;
}

void avl_node_rot_lr(avl_node_t *node)
{
    avl_node_t b = (*node)->left;
    avl_node_t c = b->right;
    b->right = c->left;
    (*node)->left = c->right;
    c->left = b;
    c->right = *node;
    *node = c;
}

void avl_node_print(avl_node_t node, int space)
{
    if (node == NULL)
        return;

    int step = 8;
    space += step;

    avl_node_print(node->right, space);

    printf("\n");
    for (int i = step; i < space; i++)
        printf(" ");
    printf("%d\n", node->value);

    avl_node_print(node->left, space);
}
