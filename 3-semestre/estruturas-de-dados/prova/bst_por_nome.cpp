#include <fstream>
#include <iostream>

struct Estudante {
    unsigned int id;
    std::string nome;
    std::string nascimento;
    std::string cpf;
};

struct DoubleLinkedListNode {
    Estudante estudante;
    DoubleLinkedListNode *next = nullptr;
    DoubleLinkedListNode *prev = nullptr;
};

struct DoubleLinkedList {
    DoubleLinkedListNode *head = nullptr;
    DoubleLinkedListNode *tail = nullptr;
    std::size_t next_id = 0;

    void insert(Estudante e);
    DoubleLinkedListNode *search(unsigned int id);
    DoubleLinkedListNode *remove(unsigned int id);
    void le_estudantes_arquivo(std::ifstream &arquivo);
    void print();
};

void DoubleLinkedList::insert(Estudante e) {
    DoubleLinkedListNode *node = new DoubleLinkedListNode;
    e.id = ++next_id;
    node->estudante = e;
    node->next = nullptr;
    node->prev = nullptr;
    if (head == nullptr) {
        head = node;
        tail = node;
    }
    else {
        node->next = head;
        head->prev = node;
        head = node;
    }
}

DoubleLinkedListNode *DoubleLinkedList::search(unsigned int id) {
    DoubleLinkedListNode *node = head;
    while (node != nullptr) {
        if (node->estudante.id == id) {
            return node;
        }
        node = node->next;
    }
    return nullptr;
}

// 7
DoubleLinkedListNode *DoubleLinkedList::remove(unsigned int id) {
    DoubleLinkedListNode *node = search(id);
    if (node == nullptr) {
        return nullptr;
    }

    if (node->prev != nullptr) {
        node->prev->next = node->next;
    }
    else {
        head = node->next;
    }

    if (node->next != nullptr) {
        node->next->prev = node->prev;
    }
    else {
        tail = node->prev;
    }

    return node;
}

void DoubleLinkedList::le_estudantes_arquivo(std::ifstream &arquivo) {
    std::string linha;
    for (int i = 0; i < 1000; ++i) {
        Estudante e;
        std::getline(arquivo, linha);
        e.nome = linha;
        std::getline(arquivo, linha);
        e.nascimento = linha;
        std::getline(arquivo, linha);
        e.cpf = linha;
        insert(e);
    }
}

void DoubleLinkedList::print() {
    DoubleLinkedListNode *node = head;
    while (node != nullptr) {
        std::cout << "ID: " << node->estudante.id << std::endl;
        std::cout << "Nome: " << node->estudante.nome << std::endl;
        std::cout << "Nascimento: " << node->estudante.nascimento << std::endl;
        std::cout << "CPF: " << node->estudante.cpf << std::endl;
        node = node->next;
    }
}

// 3
struct BSTNode {
    DoubleLinkedListNode *node = nullptr;
    BSTNode *left = nullptr;
    BSTNode *right = nullptr;

    void print();
    std::size_t count();
};

// 3
struct BST_NOME {
    BSTNode *root = nullptr;

    BST_NOME(DoubleLinkedList &lista);

    void insert(DoubleLinkedListNode *node);
    DoubleLinkedListNode *search(std::string nome);
    DoubleLinkedListNode *remove(std::string nome);
    std::size_t count();
};

BST_NOME::BST_NOME(DoubleLinkedList &lista) {
    DoubleLinkedListNode *node = lista.head;
    while (node != nullptr) {
        insert(node);
        node = node->next;
    }
}

void BST_NOME::insert(DoubleLinkedListNode *node) {
    BSTNode *new_node = new BSTNode;
    new_node->node = node;
    if (root == nullptr) {
        root = new_node;
        return;
    }

    BSTNode *current = root;
    while (true) {
        if (node->estudante.nome < current->node->estudante.nome) {
            if (current->left == nullptr) {
                current->left = new_node;
                return;
            }
            current = current->left;
        }
        else {
            if (current->right == nullptr) {
                current->right = new_node;
                return;
            }
            current = current->right;
        }
    }
}

DoubleLinkedListNode *BST_NOME::search(std::string nome) {
    BSTNode *current = root;
    while (current != nullptr) {
        if (current->node->estudante.nome == nome) {
            return current->node;
        }
        if (nome < current->node->estudante.nome) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return nullptr;
}

DoubleLinkedListNode *BST_NOME::remove(std::string nome) {
    // Acha o nó pai e o atual
    BSTNode *current = root;
    BSTNode *parent = nullptr;
    while (current != nullptr) {
        if (current->node->estudante.nome == nome) {
            break;
        }
        parent = current;
        if (nome < current->node->estudante.nome) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    if (current == nullptr) {
        return nullptr;
    }

    DoubleLinkedListNode *node = current->node;
    if (current->left == nullptr && current->right == nullptr) {
        if (current == root) {
            root = nullptr;
        }
        else {
            if (parent->left == current) {
                parent->left = nullptr;
            }
            else {
                parent->right = nullptr;
            }
        }
    }
    else if (current->left != nullptr && current->right != nullptr) {
        // Pega o sucessor do nó atual
        BSTNode *successor = current->right;
        parent = nullptr;
        while (successor->left != nullptr) {
            parent = successor;
            successor = successor->left;
        }

        // Copia o sucessor para o nó atual
        current->node = successor->node;
        if (parent != nullptr) {
            if (parent->left == successor) {
                parent->left = successor->right;
            }
            else {
                parent->right = successor->right;
            }
        }
        else {
            current->right = successor->right;
        }
    }
    else {
        BSTNode *child
            = (current->left != nullptr) ? current->left : current->right;
        if (current == root) {
            root = child;
        }
        else {
            if (parent->left == current) {
                parent->left = child;
            }
            else {
                parent->right = child;
            }
        }
    }
    return node;
}

// 6
std::size_t BST_NOME::count() {
    return root->count();
}

// 5
void BSTNode::print() {
    if (left != nullptr) {
        left->print();
    }
    std::cout << "ID: " << node->estudante.id << std::endl;
    std::cout << "Nome: " << node->estudante.nome << std::endl;
    std::cout << "Nascimento: " << node->estudante.nascimento << std::endl;
    std::cout << "CPF: " << node->estudante.cpf << std::endl;
    if (right != nullptr) {
        right->print();
    }
}

// 6
std::size_t BSTNode::count() {
    std::size_t count = 1;
    if (left != nullptr) {
        count += left->count();
    }
    if (right != nullptr) {
        count += right->count();
    }
    return count;
}

int main() {
    DoubleLinkedList lista;
    std::ifstream arquivo("bla.txt");
    lista.le_estudantes_arquivo(arquivo);
    BST_NOME bst(lista);
    DoubleLinkedListNode *node = bst.search("EU NAO EXISTO");
    if (node != nullptr) {
        std::cout << "ID: " << node->estudante.id << std::endl;
        std::cout << "Nome: " << node->estudante.nome << std::endl;
        std::cout << "Nascimento: " << node->estudante.nascimento << std::endl;
        std::cout << "CPF: " << node->estudante.cpf << std::endl;
    }
    else {
        std::cout << "Estudante não encontrado" << std::endl;
    }
    node = bst.search("Kobe Carroll");
    if (node != nullptr) {
        std::cout << "Estudante encontrado!" << std::endl;
        std::cout << "ID: " << node->estudante.id << std::endl;
        std::cout << "Nome: " << node->estudante.nome << std::endl;
        std::cout << "Nascimento: " << node->estudante.nascimento << std::endl;
        std::cout << "CPF: " << node->estudante.cpf << std::endl;
    }
    else {
        std::cout << "Estudante não encontrado" << std::endl;
    }
    std::cout << "Quantidade de estudantes: " << bst.count() << std::endl;
    bst.remove("Kobe Carroll");
    if (bst.search("Kobe Carroll") == nullptr) {
        std::cout << "Estudante removido" << std::endl;
    }
    std::cout << "Quantidade de estudantes: " << bst.count() << std::endl;
    std::string nome = bst.root->node->estudante.nome;
    bst.remove(nome);
    if (bst.search(nome) == nullptr) {
        std::cout << "Estudante removido" << std::endl;
    }
    std::cout << "Quantidade de estudantes: " << bst.count() << std::endl;
    // bst.root->print();
    return 0;
}
