#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>

namespace structures {

template<typename T>
class CircularList {
public:
    CircularList();
    ~CircularList();

    void clear(); // limpar lista

    void push_back(const T& data); // inserir no fim
    void push_front(const T& data); // inserir no início
    void insert(const T& data, std::size_t index); // inserir na posição
    void insert_sorted(const T& data); // inserir em ordem

    T& at(std::size_t index); // acessar em um indice (com checagem de limites)
    const T& at(std::size_t index) const; // versão const do acesso ao indice

    T pop(std::size_t index); // retirar da posição
    T pop_back(); // retirar do fim
    T pop_front(); // retirar do início
    void remove(const T& data); // remover dado específico

    bool empty() const; // lista vazia
    bool contains(const T& data) const; // lista contém determinado dado?
    std::size_t find(const T& data) const; // posição de um item na lista

    std::size_t size() const; // tamanho da lista

private:
    class Node {  // Elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* before_index(std::size_t index) {  // nó anterior ao 'index'
        auto it = sentinela->next();
        for (auto i = 1u; i < index; ++i) {
            it = it->next();
        }
        return it;
    }

    Node* sentinela;  // Nó sentinela
    std::size_t size_{0u};
};

}

#endif

// Implementação:

//! Construtor
template<typename T>
structures::CircularList<T>::CircularList() {
    sentinela = new Node(T{});  // Nó sentinela sem valor relevante
    sentinela->next(sentinela); // Circular, apontando para si mesmo
    size_ = 0u;
}

//! Destrutor
template<typename T>
structures::CircularList<T>::~CircularList() {
    clear();
    delete sentinela;
}

//! Esvazia
template<typename T>
void structures::CircularList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

//! Inserção no início
template<typename T>
void structures::CircularList<T>::push_front(const T& data) {
    Node *novo = new Node(data, sentinela->next());
    if (novo == nullptr) {
        throw std::out_of_range("memória insuficiente");
    }
    sentinela->next(novo);
    if (size_ == 0) {
        novo->next(novo);  // Lista circular, primeiro elemento aponta para si
    }
    size_++;
}

//! Inserção no fim
template<typename T>
void structures::CircularList<T>::push_back(const T& data) {
    if (empty()) {
        return push_front(data);
    }
    Node *novo = new Node(data, sentinela);
    Node *tail = before_index(size_);  // Último elemento
    tail->next(novo);
    size_++;
}

//! Acesso ao índice
template<typename T>
T& structures::CircularList<T>::at(std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("posição inválida");
    }
    Node *it = sentinela->next();
    for (std::size_t i = 0; i < index; ++i) {
        it = it->next();
    }
    return it->data();
}

//! Inserção na posição 'index'
template<typename T>
void structures::CircularList<T>::insert(const T& data, std::size_t index) {
    if (index > size()) {
        throw std::out_of_range("index fora de intervalo.");
    }
    if (index == 0) {
        return push_front(data);
    }
    Node *anterior = before_index(index);
    Node *novo = new Node(data, anterior->next());
    anterior->next(novo);
    size_++;
}

//! Inserção ordenada
template<typename T>
void structures::CircularList<T>::insert_sorted(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        Node *anterior = sentinela;
        Node *atual = sentinela->next();
        std::size_t position = 0;

        while (atual != sentinela && data > atual->data()) {
            anterior = atual;
            atual = atual->next();
            position++;
        }
        insert(data, position);
    }
}

//! Remoção do início
template<typename T>
T structures::CircularList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    Node *remover = sentinela->next();
    sentinela->next(remover->next());
    T dado = remover->data();
    delete remover;
    size_--;
    return dado;
}

//! Remoção do fim
template<typename T>
T structures::CircularList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    if (size() == 1) {
        return pop_front();
    }
    Node *penultimo = before_index(size_ - 1);
    Node *ultimo = penultimo->next();
    penultimo->next(sentinela);
    T dado = ultimo->data();
    delete ultimo;
    size_--;
    return dado;
}

//! Remoção da posição 'index'
template<typename T>
T structures::CircularList<T>::pop(std::size_t index) {
    if (index >= size()) {
        throw std::out_of_range("index fora de intervalo.");
    }
    if (index == 0) {
        return pop_front();
    }
    Node *anterior = before_index(index);
    Node *remover = anterior->next();
    T dado = remover->data();
    anterior->next(remover->next());
    delete remover;
    size_--;
    return dado;
}

//! Verificação de vazia
template<typename T>
bool structures::CircularList<T>::empty() const {
    return size_ == 0;
}

//! Quantidade atual de elementos
template<typename T>
std::size_t structures::CircularList<T>::size() const {
    return size_;
}
