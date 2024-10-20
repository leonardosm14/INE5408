namespace structures {


template<typename T>
class LinkedQueue {
public:
    LinkedQueue();

    ~LinkedQueue();

    void clear(); // limpar

    void enqueue(const T& data); // enfilerar

    T dequeue(); // desenfilerar

    T& front() const; // primeiro dado

    T& back() const; // último dado

    bool empty() const; // fila vazia

    std::size_t size() const; // tamanho

private:
    class Node {  // Elemento
    public:
        //! Construtor usando apenas o dado.
        explicit Node(const T &data) :
                data_{data} {}

        //! Construtor de um nodo completo.
        explicit Node(const T &data, Node *next) :
                data_{data},
                next_{next} {}

        //! Retorna o dado armazenado.
        T &data() {
            return data_;
        }

        //! Retorna o dado armazenado.
        const T &data() const {
            return data_;
        }

        //! Retorna ponteiro para próximo nodo.
        Node *next() {  // getter: próximo
            return next_;
        }

        //! Retorna ponteiro para o o próximo node.
        const Node *next() const {  // getter const: próximo
            return next_;
        }

        //! Altera o ponteiro para o próximo.
        void next(Node *node) {  // setter: próximo
            next_ = node;
        }

        private:
            T data_;  // data_
            Node *next_{nullptr};  // next_
        };

    Node* head; // nodo-cabeça
    Node* tail; // nodo-fim
    std::size_t size_; // tamanho
};

}

template<typename T>
structures::LinkedQueue<T>::LinkedQueue() {
    head = nullptr;
    tail = nullptr;
    size_ = 0;
}

template<typename T>
structures::LinkedQueue<T>::~LinkedQueue() {
    clear();
}

template<typename T>
void structures::LinkedQueue<T>::clear() {
    while (!empty()) {
        dequeue();
    }
}

template<typename T>
void structures::LinkedQueue<T>::enqueue(const T& data) {
    
    if (empty()) {
            head = new Node(data);
        } else {
            Node *ultimo = head;
            while (ultimo->next() != nullptr) {
                ultimo = ultimo->next();
            }
            ultimo->next(new Node(data));
        } size_++;
        
}

template<typename T>
T structures::LinkedQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("Fila vazia");
    }

    Node *val = head;
    T data = val->data();
    head = head->next();

    delete val;
    size_--;

    return data;
    
}

template<typename T>
T& structures::LinkedQueue<T>::front() const {
    if (empty) {
        throw std::out_of_range("Fila vazia");
    }

    T data = head->data();
    return data;
}

template<typename T>
T& structures::LinkedQueue<T>::back() const {
    if (empty) {
        throw std::out_of_range("Fila vazia");
    }

    T data = head->tail();
    return data;
}



template<typename T>
bool structures::LinkedQueue<T>::empty() const {
    return size() == 0;
}

template<typename T>
std::size_t structures::LinkedQueue<T>::size() const {
    return size_;
}




