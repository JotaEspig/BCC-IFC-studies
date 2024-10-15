#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node_t;

// Cria un novo nó
node_t *new_n(int data) {
    node_t *n = (node_t *)malloc(sizeof(node_t));
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    return n;
}

// Insere um novo nó
void insert(node_t *root, int data) {
    if (root->data > data) {
        if (root->left == NULL) {
            root->left = new_n(data);
        }
        else {
            insert(root->left, data);
        }
    }
    else {
        if (root->right == NULL) {
            root->right = new_n(data);
        }
        else {
            insert(root->right, data);
        }
    }
}

void preorder(node_t *root) {
    if (root == NULL) {
        return;
    }
    // Espaço antes do %d para que não exista um espaço no final, aproveita para
    // imprimir o espaço existente na saida esperada
    printf(" %d", root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder(node_t *root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    // Espaço antes do %d para que não exista um espaço no final, aproveita para
    // imprimir o espaço existente na saida esperada
    printf(" %d", root->data);
    inorder(root->right);
}

void postorder(node_t *root) {
    if (root == NULL) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    // Espaço antes do %d para que não exista um espaço no final, aproveita para
    // imprimir o espaço existente na saida esperada
    printf(" %d", root->data);
}

void clean(node_t *root) {
    if (root == NULL) {
        return;
    }
    clean(root->left);
    clean(root->right);
    free(root);
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        printf("Case %d:\n", i + 1);
        int m;
        scanf("%d", &m);
        node_t *root = NULL;
        for (int j = 0; j < m; ++j) {
            int data;
            scanf("%d", &data);
            if (j == 0) {
                root = new_n(data);
            }
            else {
                insert(root, data);
            }
        }
        printf("Pre.:");
        preorder(root);
        printf("\nIn..:");
        inorder(root);
        printf("\nPost:");
        postorder(root);
        printf("\n\n");

        // Limpa a memória
        clean(root);
    }
    return 0;
}
