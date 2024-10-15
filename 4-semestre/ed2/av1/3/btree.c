#include <stdio.h>
#include <stdlib.h>

#include "btree.h"

bt_node_t *bt_create() {
    bt_node_t *root = malloc(sizeof(bt_node_t));
    if (root == NULL) {
        return NULL;
    }
    root->is_leaf = 1;
    root->num_keys = 0;
    for (int i = 0; i < MAX_KEYS + 1; i++) {
        root->children[i] = NULL;
    }
    return root;
}

bt_node_t *bt_insert(bt_node_t *root, int key) {
    // Se a raiz estiver cheia, cria uma nova raiz e divide a raiz antiga
    if (root->num_keys == MAX_KEYS) {
        bt_node_t *new_root = bt_create();
        new_root->is_leaf = 0;
        new_root->children[0] = root;
        bt_split_child(new_root, 0, root);
        bt_insert_non_full(new_root, key);
        return new_root;
    }
    // Insere após "desesvaziar" a raiz (se necessário)
    bt_insert_non_full(root, key);
    return root;
}

// Insere em um nó não cheio
void bt_insert_non_full(bt_node_t *node, int key) {
    int i = node->num_keys - 1;
    if (node->is_leaf) {
        // Caso onde o nó é folha, insere a chave na posição correta
        // Inserção "normal"
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            --i;
        }
        node->keys[i + 1] = key;
        ++node->num_keys;
    }
    else {
        // Caso onde o nó não é folha, procura o filho correto para inserir
        // a chave
        while (i >= 0 && key < node->keys[i]) {
            --i;
        }
        ++i;
        // Verifica se o filho está cheio, caso esteja, divide o filho
        if (node->children[i]->num_keys == MAX_KEYS) {
            bt_split_child(node, i, node->children[i]);
            // Acha o filho correto para inserir a chave
            if (key > node->keys[i]) {
                ++i;
            }
        }
        // Finalmente insere a chave no filho correto
        bt_insert_non_full(node->children[i], key);
    }
}

void bt_split_child(bt_node_t *parent, int i, bt_node_t *child) {
    int mid = MAX_KEYS / 2;

    bt_node_t *new_node = bt_create();
    new_node->is_leaf = child->is_leaf;
    new_node->num_keys = MAX_KEYS - mid - 1;

    for (int j = 0; j < new_node->num_keys; ++j) {
        new_node->keys[j] = child->keys[j + mid + 1];
    }
    if (!child->is_leaf) {
        for (int j = 0; j < new_node->num_keys + 1; ++j) {
            new_node->children[j] = child->children[j + mid + 1];
        }
    }

    child->num_keys = mid;

    for (int j = parent->num_keys; j > i; --j) {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[i + 1] = new_node;

    for (int j = parent->num_keys - 1; j >= i; --j) {
        parent->keys[j + 1] = parent->keys[j];
    }
    parent->keys[i] = child->keys[mid];
    ++parent->num_keys;
}

bt_node_t *bt_search(bt_node_t *node, int key) {
    if (node == NULL) {
        return NULL;
    }

    int next_node_idx;
    // Procura o indice onde a chave é menor ou igual a proxima chave do nó
    // Assim achando qual intervalo deve se entrar
    for (next_node_idx = 0; next_node_idx < node->num_keys; ++next_node_idx) {
        if (key <= node->keys[next_node_idx]) {
            break;
        }
    }

    // Verifica se o indice é menor que a quantidade de chaves para que evite um
    // index out of bounds
    if (next_node_idx < node->num_keys && key == node->keys[next_node_idx]) {
        return node;
    }
    if (node->is_leaf) {
        return NULL;
    }
    // Caso não seja igual ou não seja folha, procura dentro do intervalo já
    // reduzido
    return bt_search(node->children[next_node_idx], key);
}

void bt_print_in_order(bt_node_t *node) {
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < node->num_keys; i++) {
        bt_print_in_order(node->children[i]);
        printf(" %d", node->keys[i]);
    }
    bt_print_in_order(node->children[node->num_keys]);
}

void bt_destroy(bt_node_t *root) {
    if (root == NULL) {
        return;
    }
    if (!root->is_leaf) {
        // A quantidade de filhos é sempre o número de chaves + 1
        for (int i = 0; i < root->num_keys + 1; i++) {
            bt_destroy(root->children[i]);
        }
    }
    free(root);
}
