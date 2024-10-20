namespace structures {

template<typename T>
class LinkedStack {
public:
    LinkedStack();

    ~LinkedStack();

    void clear(); // limpa pilha

    void push(const T& data); // empilha

    T pop(); // desempilha

    T& top() const; // dado no topo

    bool empty() const; // pilha vazia

    std::size_t size() const; // tamanho da pilha

private:
    class Node {
    public:
        Node(const T& data);
        Node(const T& data, Node* next);

        T& data(); // getter: info
        const T& data() const; // getter-constante: info

        Node* next(); // getter: próximo
        const Node* next() const; // getter-constante: próximo

        void next(Node* next); // setter: próximo
    private:
        T data_;
        Node* next_;
    };

    Node* top_; // nodo-topo
    std::size_t size_; // tamanho
};

}

template<typename T>
structures::LinkedStack<T>::LinkedStack() {
    top_ = nullprt;
    size_ = 0;
}

template<typename T>
structures::LinkedStack<T>::~LinkedStack() {
    clear();
}

template<typename T>
void structures::LinkedStack<T>::clear() {
    while (!empty()) {
        pop();
    }
}

template<typename T>
bool structures::LinkedStack<T>::empty() const {
    return (size() == 0);
}

template<typename T>
T structures::LinkedStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("Pilha vazia");
        }
    Node* out = top_;
    top_ = top_->next();
    size_--;
    T data = out->data();
    delete out;
    return data;
}

template<typename T>
void structures::LinkedStack<T>::push(const T& data) {
    Node* new_node = new Node(data, top_);
    if (new_node == nullptr) {
        throw std::out_of_range("Pilha cheia");
    }
    top_ = new_node;
    size_++;
}

template<typename T>
T& structures::LinkedStack<T>::top() const {
    return top_->data();
}

template<typename T>
std::size_t structures::LinkedStack<T>::size() const {
    return size_;
}