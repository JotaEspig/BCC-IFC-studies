#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trietree.h"

tt_node_t *trie_tree_create() {
    // Aloca memória para o nó
    tt_node_t *node = malloc(sizeof(tt_node_t));
    if (node == NULL) {
        return NULL;
    }

    node->is_end_of_word = false;
    node->character = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }

    return node;
}

void trie_tree_insert(tt_node_t *root, const char *word) {
    // Insere a palavra na árvore usando indice do caractere - 32 pois
    // é o limite inferior do intervalo
    tt_node_t *current = root;
    while (*word) {
        int index = *word - 32;
        if (current->children[index] == NULL) {
            current->children[index] = trie_tree_create();
            current->children[index]->character = *word;
        }
        current = current->children[index];
        ++word;
    }
    // Marca o caractere como fim da palavra
    current->is_end_of_word = true;
}

tt_node_t *trie_tree_search(tt_node_t *root, const char *word) {
    tt_node_t *current = root;
    while (*word) {
        if (*word < 32 || *word > 126) {
            return false;
        }
        int index = *word - 32;
        // Se não existe o caractere na árvore, não existe palavra com tal
        // sequencia de caracteres
        if (current->children[index] == NULL) {
            return false;
        }
        current = current->children[index];
        ++word;
    }
    return current;
}

void trie_tree_print(tt_node_t *node, char *prefix, bool is_first) {
    if (is_first) {
        // Remove o primeiro elemento pois a função faz o papel de adicionar
        // esse ultimo caractere para ser printado
        prefix[strlen(prefix) - 1] = 0;
    }
    if (node->is_end_of_word) {
        printf("%s%c\n", prefix, node->character);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] == NULL) {
            continue;
        }

        char *new_prefix = malloc(strlen(prefix) + 2);
        if (new_prefix == NULL) {
            continue;
        }
        // Cria o novo prefixo para ser passado pela função
        strcpy(new_prefix, prefix);
        unsigned long len = strlen(new_prefix);
        new_prefix[len] = node->character;
        ++len;
        new_prefix[len] = '\0';
        // Seta is_first para falso pois não é o primeiro caractere e itera
        // recursivamente pelo restantes dos caracteres
        trie_tree_print(node->children[i], new_prefix, 0);
        free(new_prefix);
    }
}

void trie_tree_destroy(tt_node_t *root) {
    // Libera a memória alocada para a árvore
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i] != NULL) {
            trie_tree_destroy(root->children[i]);
        }
    }
    free(root);
}
