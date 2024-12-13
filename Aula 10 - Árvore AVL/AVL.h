// Copyright [2024] <Leonardo de Sousa Marques>

#include "array_list.h"


namespace structures {

template<typename T>
class AVLTree {
public:
    ~AVLTree();

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    int height() const;

    ArrayList<T> pre_order() const;

    ArrayList<T> in_order() const;

    ArrayList<T> post_order() const;

private:
    struct Node {
        explicit Node(const T& data_) {
            data = data_;
            left = nullptr;
            right = nullptr;
        }

        T data;
        int height_;
        Node* left;
        Node* right;

        void insert(const T& data_) {
            // Inserção recursiva
            if (data_ < data) {
                if (left == nullptr) {
                    left = new Node(data_);
                } else {
                    left->insert(data_);
                }
            } else if (data_ > data) {
                if (right == nullptr) {
                    right = new Node(data_);
                } else {
                    right->insert(data_);
                }
            }

            updateHeight();
        }

        bool remove(const T& data_) {
            // Busca pelo nó
            if (data_ < data) {
                if (left != nullptr) {
                    return left->remove(data_);
                }
            } else if (data_ > data) {
                if (right != nullptr) {
                    return right->remove(data_);
                }
            } else { // Nó encontrado
                if (left == nullptr && right == nullptr) {
                    // Nó sem filhos
                    return false;
                } else if (left == nullptr || right == nullptr) {
                    // Nó com um filho
                    Node* temp = (left != nullptr) ? left : right;
                    data = temp->data;
                    left = temp->left;
                    right = temp->right;
                    delete temp;
                } else {
                    // Nó com dois filhos
                    Node* temp = right;
                    while (temp->left != nullptr) {
                        temp = temp->left;
                    }
                    data = temp->data;
                    right->remove(temp->data);
                }
            }
            updateHeight();
            return true;
        }

         bool contains(const T& data_) const {
            if (data_ == data) {
                return true;
            } else if (data_ < data) {
                return (left != nullptr) ? left->contains(data_) : false;
            } else {
                return (right != nullptr) ? right->contains(data_) : false;
            }
        }
        
        void updateHeight() {
            height_ = std::max((left ? left->height_ : -1), (right ? right->height_ : -1)) + 1;
        }

        Node* simpleLeft(Node* k2) {
            Node* k1;
            k1 = k2->left;
            k2->left = k1->right;
            k1->right = k2;

            k2->height = max(k2->left->height, k2->right->height) + 1;
            k1->height = max(k1->left->height, k2->height) + 1;

            return k1;
        }

        Node* simpleRight(Node* k2) {
            Node* k1;
            k1 = k2->right;
            k2->right = k1->left;
            k1->left = k2;

            k2->height = max(k2->right->height, k2->left->height) + 1;
            k1->height = max(k1->right->height, k2->height) + 1;

            return k1;


        }

        Node* doubleLeft(Node* k3) {
            k3->left = simpleLeft(k3->left);
            return simpleLeft(k3);

        }
        
        Node* doubleRight(Node* k3) {
            k3->right = simpleRight(k3->right);
            return simpleRight(k3);
        }

        void pre_order(ArrayList<T>& v) const {
            v.push_back(data);
            if (left != nullptr)
                left->pre_order(v);
            if (right != nullptr)
                right->pre_order(v);
        }

        void in_order(ArrayList<T>& v) const {
            if (left != nullptr)
                left->in_order(v);
            v.push_back(data);
            if (right != nullptr)
                right->in_order(v);
        }

        void post_order(ArrayList<T>& v) const {
            if (left != nullptr)
                left->post_order(v);
            if (right != nullptr)
                right->post_order(v);
            v.push_back(data);
        }

        int height() {
            return height_;
        }
    };

    Node* root;
    std::size_t size_;
};

}

// -----

template<typename T>
int structures::AVLTree<T>::height() const {
    return root->height();
}

template<typename T>
structures::AVLTree<T>::~AVLTree() {
    // Destrói recursivamente todos os nós
    delete root;
}

// Insere um elemento na árvore
template<typename T>
void structures::AVLTree<T>::insert(const T& data) {
    if (root == nullptr) {
        root = new Node(data);
    } else {
        root->insert(data);
    }
    size_++;
}

// Remove um elemento da árvore
template<typename T>
void structures::AVLTree<T>::remove(const T& data) {
    if (root != nullptr) {
        if (root->remove(data)) {
            size_--;
        }
    }
}

// Verifica se o elemento está presente na árvore
template<typename T>
bool structures::AVLTree<T>::contains(const T& data) const {
    if (root != nullptr) {
        return root->contains(data);
    }
    return false;
}

// Verifica se a árvore está vazia
template<typename T>
bool structures::AVLTree<T>::empty() const {
    return size_ == 0;
}

// Retorna o tamanho da árvore
template<typename T>
std::size_t structures::AVLTree<T>::size() const {
    return size_;
}

// Retorna a altura da árvore
template<typename T>
int structures::AVLTree<T>::height() const {
    return root ? root->height_ : -1;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::pre_order() const {
    ArrayList<T> result;
    if (root != nullptr) {
        root->pre_order(result);  // Chama o método pre_order do Node
    }
    return result;
}

// Retorna a lista com os elementos em ordem
template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::in_order() const {
    ArrayList<T> result;
    if (root != nullptr) {
        root->in_order(result);  // Chama o método in_order do Node
    }
    return result;
}

// Retorna a lista com os elementos em pós-ordem
template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::post_order() const {
    ArrayList<T> result;
    if (root != nullptr) {
        root->post_order(result);  // Chama o método post_order do Node
    }
    return result;
}