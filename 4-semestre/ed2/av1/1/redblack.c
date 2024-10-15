#include <stdio.h>
#include <stdlib.h>

#include "redblack.h"

// Cria um novo nó com o valor passado
rb_node_t *rb_new(int data) {
    rb_node_t *node = malloc(sizeof(rb_node_t));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->color = RED;
    return node;
}

// Insere um novo nó na árvore
void rb_insert(rb_node_t *root, int data) {
    rb_node_t *node = rb_new(data);
    rb_node_t *parent = NULL;
    rb_node_t *current = root;
    // Encontra o pai do novo nó
    while (current != NULL) {
        parent = current;
        if (node->data < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    node->parent = parent;
    // Seta o novo nó no lugar correto
    if (parent == NULL) {
        root = node;
    }
    else if (node->data < parent->data) {
        parent->left = node;
    }
    else {
        parent->right = node;
    }

    // Se não tiver pai, seta para preto
    if (node->parent == NULL) {
        node->color = BLACK;
        return;
    }
    // Se não tiver avô, não faz nada
    if (node->parent->parent == NULL) {
        return;
    }

    // Chama a função auxiliar de correção da arvore
    rb_insert_fix(root, node);
}

void rb_insert_fix(rb_node_t *root, rb_node_t *node) {
    rb_node_t *parent = NULL;
    rb_node_t *grandparent = NULL;
    // Utiliza as regras de correção da árvore vermelho-preto nos nós
    // necessários
    while ((node != root) && (node->color != BLACK)
           && (node->parent->color == RED)) {
        parent = node->parent;
        grandparent = node->parent->parent;
        // Se o pai do nó é filho esquerdo do avô
        if (parent == grandparent->left) {
            rb_node_t *uncle = grandparent->right;
            // Caso 1: O tio é vermelho, o que significa que o avô precisa ser
            // recolorido
            if (uncle != NULL && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            }
            else {
                // Caso 2: O nó é filho direito do pai (rotação à esquerda
                // necessária)
                if (node == parent->right) {
                    rb_left_rot(parent);
                    node = parent;
                    parent = node->parent;
                }
                // Caso 3: O nó é filho esquerdo do pai (rotação à direita
                // necessária)
                rb_right_rot(grandparent);
                int temp = parent->color;
                parent->color = grandparent->color;
                grandparent->color = temp;
                node = parent;
            }
        }
        else {
            rb_node_t *uncle = grandparent->left;
            // Caso 1: O tio é vermelho (recoloração)
            if (uncle != NULL && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            }
            else {
                // Caso 2: O nó é filho esquerdo do pai (rotação à direita
                // necessária)
                if (node == parent->left) {
                    rb_right_rot(parent);
                    node = parent;
                    parent = node->parent;
                }
                // Caso 3: O nó é filho direito do pai (rotação à esquerda
                // necessária)
                rb_left_rot(grandparent);
                int temp = parent->color;
                parent->color = grandparent->color;
                grandparent->color = temp;
                node = parent;
            }
        }
    }
    // Garante que a raiz seja preta
    root->color = BLACK;
}

uint64_t rb_height_with_root(rb_node_t *node) {
    if (node == NULL) {
        return 0;
    }

    uint64_t left = rb_height_with_root(node->left);
    uint64_t right = rb_height_with_root(node->right);
    return 1 + (left > right ? left : right);
}

void rb_left_rot(rb_node_t *root) {
    // Aplica a rotacao a esquerda
    rb_node_t *right = root->right;
    root->right = right->left;
    if (right->left != NULL) {
        right->left->parent = root;
    }
    right->parent = root->parent;
    if (root->parent == NULL) {
        root = right;
    }
    else if (root == root->parent->left) {
        root->parent->left = right;
    }
    else {
        root->parent->right = right;
    }
    right->left = root;
    root->parent = right;
}

void rb_right_rot(rb_node_t *root) {
    // Aplica a rotacao a direita
    rb_node_t *left = root->left;
    root->left = left->right;
    if (left->right != NULL) {
        left->right->parent = root;
    }
    left->parent = root->parent;
    if (root->parent == NULL) {
        root = left;
    }
    else if (root == root->parent->right) {
        root->parent->right = left;
    }
    else {
        root->parent->left = left;
    }
    left->right = root;
    root->parent = left;
}

// Conta o número de nós de um tipo específico recursivamente
uint64_t rb_count_type(rb_node_t *node, int type) {
    if (node == NULL) {
        return 0;
    }

    uint64_t count = 0;
    if (node->color == type) {
        ++count;
    }
    count += rb_count_type(node->left, type);
    count += rb_count_type(node->right, type);
    return count;
}

// Printa em formato de árvore
void rb_pretty_print(rb_node_t *node, int indent) {
    if (node == NULL) {
        return;
    }

    rb_pretty_print(node->right, indent + 4);
    for (int i = 0; i < indent; ++i) {
        printf(" ");
    }
    printf("%d - %c\n", node->data, node->color == RED ? 'R' : 'B');
    rb_pretty_print(node->left, indent + 4);
}

void rb_print_in_order(rb_node_t *node) {
    if (node == NULL) {
        return;
    }

    rb_print_in_order(node->left);
    printf("%d ", node->data);
    rb_print_in_order(node->right);
}

void rb_destroy(rb_node_t **node) {
    if (*node == NULL) {
        return;
    }

    free(*node);
    *node = NULL;
}

// Destroi a árvore recursivamente
void rb_destroy_rec(rb_node_t **node) {
    if (*node == NULL) {
        return;
    }

    rb_destroy_rec(&(*node)->left);
    rb_destroy_rec(&(*node)->right);
    rb_destroy(node);
}
