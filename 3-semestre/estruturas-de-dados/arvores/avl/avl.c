#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "avl.h"
#include "utils.h"

avl_node_t avl_node_new(int value)
{
    avl_node_t node = malloc(sizeof(struct avl_node));
    if (node == NULL)
        return NULL;

    node->value = value;
    node->height = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void avl_node_insert(avl_node_t *node, int value)
{
    assert(node != NULL);

    if (*node == NULL)
    {
        *node = avl_node_new(value);
        return;
    }
    else if ((*node)->value > value)
    {
        avl_node_insert(&(*node)->left, value);
        avl_node_set_height(*node);
        avl_node_rot(node);
    }
    else if ((*node)->value <= value)
    {
        avl_node_insert(&(*node)->right, value);
        avl_node_set_height(*node);
        avl_node_rot(node);
    }
}

size_t avl_node_height(avl_node_t node)
{
    size_t height = 0;
    if (node != NULL)
        height = node->height;
    return height;
}

void avl_node_set_height(avl_node_t node)
{
    assert(node != NULL);
    size_t height = 0;
    if (node->left != NULL)
        height = avl_node_height(node->left) + 1;
    if (node->right != NULL)
        height = max(height, avl_node_height(node->right) + 1);

    node->height = height;
}

long avl_node_balance(avl_node_t node)
{
    return avl_node_height(node->left) - avl_node_height(node->right);
}

void avl_node_rot(avl_node_t *node)
{
    long balance = avl_node_balance(*node);
    if (balance >= 2)
    {
        avl_node_t left = (*node)->left;
        if (avl_node_balance(left) >= 1)
            avl_node_rot_ll(node);
        else
            avl_node_rot_lr(node);
    }
    else if (balance <= -2)
    {
        avl_node_t right = (*node)->right;
        if (avl_node_balance(right) <= -1)
            avl_node_rot_rr(node);
        else
            avl_node_rot_rl(node);
    }
}

void avl_node_rot_ll(avl_node_t *node)
{
    avl_node_t a = *node;
    avl_node_t b = a->left;
    a->left = b->right;
    b->right = a;
    *node = b;
    avl_node_set_height(a);
    avl_node_set_height(b);
}

void avl_node_rot_rr(avl_node_t *node)
{
    avl_node_t a = *node;
    avl_node_t b = a->right;
    a->right = b->left;
    b->left = a;
    *node = b;
    avl_node_set_height(a);
    avl_node_set_height(b);
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
    avl_node_set_height(a);
    avl_node_set_height(b);
    avl_node_set_height(c);
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
    avl_node_set_height(a);
    avl_node_set_height(b);
    avl_node_set_height(c);
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
    printf("%d - %ld\n", node->value, node->height);

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
