#ifndef AVL_H
#define AVL_H

typedef struct avl_node {
    int key;
    struct avl_node *left;
    struct avl_node *right;
    struct avl_node *parent;
    int height;
} avl_node_t;

typedef struct avl_tree {
    avl_node_t *root;
} avl_tree_t;

avl_tree_t *avl_create();
avl_tree_t *avl_insert(avl_tree_t **tree, int new_key);
void avl_destroy(avl_tree_t **tree);

avl_node_t *avl_node_create(int new_key);
void avl_node_print(avl_node_t *node, int indent);
void avl_node_destroy(avl_node_t **node);
void avl_node_destroy_recursive(avl_node_t **node);

#endif // AVL_H
