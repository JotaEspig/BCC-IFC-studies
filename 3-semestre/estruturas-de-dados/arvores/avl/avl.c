#include <assert.h>
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
    avl_node_t a = *node;
    avl_node_t b = a->left;
    a->left = b->right;
    b->right = a;
    *node = b;
}

void avl_node_rot_rr(avl_node_t *node)
{
    avl_node_t a = *node;
    avl_node_t b = a->right;
    a->right = b->left;
    b->left = a;
    *node = b;
}

void avl_node_rot_lr(avl_node_t *node)
{
    avl_node_t a = *node;
    avl_node_t b = a->left;
    avl_node_t c = b->right;
    b->right = c->left;
    a->left = c->right;
    c->left = b;
    c->right = a;
    *node = c;
}

void avl_node_rot_rl(avl_node_t *node)
{
    avl_node_t a = *node;
    avl_node_t b = a->right;
    avl_node_t c = b->left;
    b->left = c->right;
    a->right = c->left;
    c->right = b;
    c->left = a;
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

void avl_node_destroy(avl_node_t *node)
{
    assert(node != NULL);
    if (*node == NULL)
        return;

    avl_node_destroy(&(*node)->left);
    avl_node_destroy(&(*node)->right);
    free(*node);
    *node = NULL;
}
