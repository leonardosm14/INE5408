//! Copyright [2024] <LEONARDO DE SOUSA MARQUES>

#include <stdexcept>  // C++ exceptions

namespace structures {

template<typename T>
//! Classe DoublyLinkedList
class DoublyLinkedList {
 public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    //! Método para limpar dados
    void clear();
    //! Método para inserir no fim
    void push_back(const T& data);  // insere no fim
    //! Método para inserir no início
    void push_front(const T& data);  // insere no início
    //! Método para inserir no índice
    void insert(const T& data, std::size_t index);  // insere na posição
    //! Método para inserir ordenado
    void insert_sorted(const T& data);  // insere em ordem
    //! Método para remover no índice
    T pop(std::size_t index);  // retira da posição
    //! Método para remover no fim
    T pop_back();  // retira do fim
    //! Método para remover no início
    T pop_front();  // retira do início
    //! Método para remover um dado específico
    void remove(const T& data);  // retira específico
    //! Método para verificar se está vazio
    bool empty() const;  // lista vazia
    //! Método para verificar se contém um dado
    bool contains(const T& data) const;  // contém
    //! Método para acessar um elemento no índice
    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    //! Método para acessar um elemento no índice (const)
    const T& at(std::size_t index) const;  // getter constante a um elemento
    //! Método para encontrar a posição de um dado
    std::size_t find(const T& data) const;  // posição de um dado
    //! Método para obter o tamanho da lista
    std::size_t size() const;  // tamanho

 private:
    class Node {
     public:
        //! Construtor com dado
        explicit Node(const T& data):
            data_{data},
            prev_{nullptr},
            next_{nullptr}
        {}
        //! Construtor com dado e próximo
        Node(const T& data, Node* next):
            data_{data},
            next_{next},
            prev_{nullptr}
        {}
        //! Construtor com dado, anterior e próximo
        Node(const T& data, Node* prev, Node* next):
            data_{data},
            prev_{prev},
            next_{next}
        {}
        //! Getter para dado
        T& data() {  // getter: dado
            return data_;
        }
        //! Getter const para dado
        const T& data() const {  // getter const: dado
            return data_;
        }
        //! Getter para anterior
        Node* prev() {  // getter: anterior
            return prev_;
        }
        //! Getter const para anterior
        const Node* prev() const {  // getter const: anterior
            return prev_;
        }
        //! Setter para anterior
        void prev(Node* node) {  // setter: anterior
            prev_ = node;
        }
        //! Getter para próximo
        Node* next() {  // getter: próximo
            return next_;
        }
        //! Getter const para próximo
        const Node* next() const {  // getter const: próximo
            return next_;
        }
        //! Setter para próximo
        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    //! Posicionamento do ponteiro pelo caminho mais curto
    Node* position(std::size_t index) const {
        Node* p;
        if (index < size_ / 2) {  // do início para o fim
            p = head;
            for (std::size_t i = 0; i < index; i++) {
                p = p->next();
            }
        } else {  // do fim para o início
            p = tail;
            for (std::size_t i = size_ - 1; i > index; i--) {
                p = p->prev();
            }
        }
        return p;
    }

    //! Ponteiro para o início da lista
    Node* head;  // primeiro da lista
    //! Ponteiro para o fim da lista
    Node* tail;  // último da lista
    //! Tamanho da lista
    std::size_t size_;
};

}  // namespace structures

template<typename T>
structures::DoublyLinkedList<T>::DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
    size_ = 0;
}

template<typename T>
structures::DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

template<typename T>
void structures::DoublyLinkedList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template<typename T>
void structures::DoublyLinkedList<T>::push_back(const T& data) {
    Node* p = new Node(data);
    if (p != nullptr) {
        if (empty()) {
            head = p;
            tail = p;
        } else {
            tail->next(p);
            p->prev(tail);
            tail = p;
        }
        size_++;
    } else {
        throw std::out_of_range("memória insuficiente");
    }
}

template<typename T>
void structures::DoublyLinkedList<T>::push_front(const T& data) {
    Node* p = new Node(data);
    if (p != nullptr) {
        if (empty()) {
            head = p;
            tail = p;
        } else {
            p->next(head);
            head->prev(p);
            head = p;
        }
        size_++;
    } else {
        throw std::out_of_range("memória insuficiente");
    }
}

template<typename T>
void structures::DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
    if (index > size_)
        throw std::out_of_range("índice fora de intervalo.");

    if (index == 0) {
        push_front(data);
    } else if (index == size_) {
        push_back(data);
    } else {
        Node* p = new Node(data);
        Node* previous = position(index - 1);
        Node* next = previous->next();
        p->prev(previous);
        p->next(next);
        previous->next(p);
        if (next != nullptr) {
            next->prev(p);
        }
        size_++;
    }
}

template<typename T>
void structures::DoublyLinkedList<T>::insert_sorted(const T& data) {
    if (empty()) {
        push_back(data);
    } else {
        Node* p = head;
        std::size_t index = 0;
        while (p != nullptr && p->data() < data) {
            p = p->next();
            index++;
        }
        insert(data, index);
    }
}

template<typename T>
T structures::DoublyLinkedList<T>::pop(std::size_t index) {
    if (index >= size_)
        throw std::out_of_range("índice fora de intervalo.");

    Node* p = position(index);
    T data = p->data();
    if (p == head) {
        pop_front();
    } else if (p == tail) {
        pop_back();
    } else {
        Node* previous = p->prev();
        Node* next = p->next();
        previous->next(next);
        next->prev(previous);
        delete p;
        size_--;
    }
    return data;
}

template<typename T>
T structures::DoublyLinkedList<T>::pop_back() {
    if (empty())
        throw std::out_of_range("lista vazia");

    T data = tail->data();
    if (size_ == 1) {
        delete tail;
        head = nullptr;
        tail = nullptr;
    } else {
        Node* prev = tail->prev();
        prev->next(nullptr);
        delete tail;
        tail = prev;
    }
    size_--;
    return data;
}

template<typename T>
T structures::DoublyLinkedList<T>::pop_front() {
    if (empty())
        throw std::out_of_range("lista vazia");

    T data = head->data();
    if (size_ == 1) {
        delete head;
        head = nullptr;
        tail = nullptr;
    } else {
        Node* next = head->next();
        next->prev(nullptr);
        delete head;
        head = next;
    }
    size_--;
    return data;
}

template<typename T>
void structures::DoublyLinkedList<T>::remove(const T& data) {
    if (empty())
        return;

    Node* p = head;
    while (p != nullptr && p->data() != data) {
        p = p->next();
    }
    if (p != nullptr) {
        if (p == head) {
            pop_front();
        } else if (p == tail) {
            pop_back();
        } else {
            Node* previous = p->prev();
            Node* next = p->next();
            previous->next(next);
            if (next != nullptr) {
                next->prev(previous);
            }
            delete p;
            size_--;
        }
    }
}

template<typename T>
bool structures::DoublyLinkedList<T>::empty() const {
	return size() == 0;
}

template<typename T>
bool structures::DoublyLinkedList<T>::contains(const T& data) const {
	Node *p = head;
	for (size_t i = 0; i < size_; i++) {
		if (p->data() == data) {
			return true;
		}
		p = p->next();
	}
	return false;
}

template<typename T>
T& structures::DoublyLinkedList<T>::at(std::size_t index) {
	if (index < size_) {
		Node *p = posicao(index);
		return p->data();
	}
	throw std::out_of_range("indice inexistente");
}

template<typename T>
const T& structures::DoublyLinkedList<T>::at(std::size_t index) const {
	if (index < size_) {
		Node *p = posicao(index);
		return p->data();
	}
	throw std::out_of_range("indice inexistente");
}

template<typename T>
std::size_t structures::DoublyLinkedList<T>::find(const T& data) const {
	Node *p = head;
	for (size_t i = 0; i < size_; i++) {
		if (p->data() == data) {
			return i;
		}
		p = p->next();
	}
	return size();
}

template<typename T>
std::size_t structures::DoublyLinkedList<T>::size() const {
	return size_;
}
