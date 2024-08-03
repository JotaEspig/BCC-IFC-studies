#include <fstream>
#include <iostream>

// 2-a
struct Estudante {
    unsigned int id;
    std::string nome;
    std::string nascimento;
    std::string cpf;
};

// 2-c
struct DoubleLinkedListNode {
    Estudante estudante;
    DoubleLinkedListNode *next;
    DoubleLinkedListNode *prev;
};

// 2-c
struct DoubleLinkedList {
    DoubleLinkedListNode *head;
    DoubleLinkedListNode *tail;
    std::size_t next_id;

    // 2-d
    void insert(Estudante e);
    // 2-e
    DoubleLinkedListNode *search(unsigned int id);
    // 2-f
    DoubleLinkedListNode *remove(unsigned int id);
    // 2-g
    void le_estudantes_arquivo(std::ifstream &arquivo);
    std::size_t count();
    // 2-b
    void print();
};

// 2-d
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
        // Insira o novo nó no começo da lista
        node->next = head;
        head->prev = node;
        head = node;
    }
}

// 2-e
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

// 2-f
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

// 6
std::size_t DoubleLinkedList::count() {
    std::size_t count = 0;
    DoubleLinkedListNode *node = head;
    while (node != nullptr) {
        ++count;
        node = node->next;
    }
    return count;
}

// 2-b
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

int main() {
    DoubleLinkedList lista;
    std::ifstream arquivo("bla.txt");
    lista.le_estudantes_arquivo(arquivo);
    // lista.print();
    std::cout << "\n\nProcurando estudante com ID 42" << std::endl;
    DoubleLinkedListNode *node = lista.search(42);
    if (node != nullptr) {
        std::cout << "Estudante encontrado!" << std::endl;
        std::cout << "Nome: " << node->estudante.nome << std::endl;
        std::cout << "Nascimento: " << node->estudante.nascimento << std::endl;
        std::cout << "CPF: " << node->estudante.cpf << std::endl;
    }
    else {
        std::cout << "Estudante não encontrado!" << std::endl;
    }
    std::cout << "Quantidade de estudantes: " << lista.count() << std::endl;

    std::cout << "\n\nRemovendo estudantes com ID de 1 a 100" << std::endl;
    for (int i = 1; i <= 100; ++i) {
        lista.remove(i);
    }

    std::cout << "Removendo os primeiros 100 estudantes" << std::endl;
    for (int i = 0; i < 100; ++i) {
        lista.remove(lista.head->estudante.id);
    }

    // lista.print();

    std::cout << "Quantidade de estudantes: " << lista.count() << std::endl;
    return 0;
}
