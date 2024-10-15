#ifndef RED_BLACK_H
#define RED_BLACK_H

#include <stdint.h>

// -1 para desconsiderar a raiz, pois a função que eu fiz considera a
// raiz como altura 1, poderia mudar isso, mas não quis pois provavelmente
// precisaria criar uma estrutura e função auxiliar para verificar se é o
// root :)
#define RB_HEIGHT(node) (rb_height_with_root(node) - 1)

enum { RED = 0, BLACK = 1 };

typedef struct rb_node {
    int data;
    struct rb_node *left;
    struct rb_node *right;
    struct rb_node *parent;
    int color;
} rb_node_t;

rb_node_t *rb_new(int data);
void rb_insert(rb_node_t *root, int data);
void rb_insert_fix(rb_node_t *root, rb_node_t *node);
uint64_t rb_height_with_root(rb_node_t *node);
void rb_left_rot(rb_node_t *root);
void rb_right_rot(rb_node_t *root);
uint64_t rb_count_type(rb_node_t *node, int type);
void rb_pretty_print(rb_node_t *node, int indent);
void rb_print_in_order(rb_node_t *node);
void rb_destroy(rb_node_t **node);
void rb_destroy_rec(rb_node_t **node);

#endif // RED_BLACK_H
