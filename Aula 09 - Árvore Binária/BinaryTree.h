// Copyright [2024] - LEONARDO MARQUES
#include "./array_list.h"


namespace structures {

template<typename T>
class BinaryTree {
 public:
    BinaryTree();

    ~BinaryTree();

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

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
        Node* left;
        Node* right;

        void insert(const T& data_) {
            if (data_ < data) {
                if (left == nullptr) {
                    left = new Node(data_);
                } else {
                    left->insert(data_);
                }
            } else {
                if (right == nullptr) {
                    right = new Node(data_);
                } else {
                    right->insert(data_);
                }
            }
        }

        bool remove(const T& data_) {
            if (data_ < data) {
                if (left != nullptr) {
                    if (left->remove(data_)) {
                        left = nullptr;  // Limpa o ponteiro após a remoção
                        return true;
                    }
                    return false;
                }
                return false;
            } else if (data_ > data) {
                if (right != nullptr) {
                    if (right->remove(data_)) {
                        right = nullptr;  // Limpa o ponteiro após a remoção
                        return true;
                    }
                    return false;
                }
                return false;
            } else {  // Encontramos o nó a ser removido
                if (left == nullptr && right == nullptr) {  // Nó folha
                    return true;  // Pai irá deletar este nó
                } else if (left == nullptr) {
                    Node* temp = right;
                    data = temp->data;
                    right = temp->right;
                    left = temp->left;
                    temp->right = nullptr; 
                    temp->left = nullptr;  
                    delete temp;
                    return false;  // Não delete este nó
                } else if (right == nullptr) {
                    Node* temp = left;
                    data = temp->data;
                    right = temp->right;
                    left = temp->left;
                    temp->right = nullptr; 
                    temp->left = nullptr;  
                    delete temp;
                    return false;  // Não delete este nó
                } else {  // Dois filhos
                    Node* successor = right;
                    while (successor->left != nullptr) {
                        successor = successor->left;
                    }
                    data = successor->data;
                    right->remove(successor->data);
                }
            }
            return true;
        }

        bool contains(const T& data_) const {
            if (data_ == data) {
                return true;
            } else if (data_ < data) {
                if (left != nullptr) {
                    return left->contains(data_);
                } else {
                    return false;
                }
            } else {  // data_ > data
                if (right != nullptr) {
                    return right->contains(data_);
                } else {
                    return false;
                }
            }
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
    };

    Node* root;
    std::size_t size_;
};

template<typename T>
BinaryTree<T>::BinaryTree() : root{nullptr}, size_{0} {}

template<typename T>
BinaryTree<T>::~BinaryTree() {
    delete root;
    size_ = 0;
}

template<typename T>
void BinaryTree<T>::insert(const T& data) {
    if (root == nullptr) {
        root = new Node(data);
    } else {
        root->insert(data);
    }
    size_++;
}

template<typename T>
void BinaryTree<T>::remove(const T& data) {
    if (root->remove(data)) {
        size_--;
    }
}

template<typename T>
bool BinaryTree<T>::contains(const T& data) const {
    return root->contains(data);
}

template<typename T>
bool BinaryTree<T>::empty() const {
    return size() == 0;
}

template<typename T>
std::size_t BinaryTree<T>::size() const {
    return size_;
}

template<typename T>
ArrayList<T> BinaryTree<T>::pre_order() const {
    ArrayList<T> list;
    if (root != nullptr) {
        root->pre_order(list);
    }
    return list;
}

template<typename T>
ArrayList<T> BinaryTree<T>::in_order() const {
    ArrayList<T> list;
    if (root != nullptr) {
        root->in_order(list);
    }
    return list;
}

template<typename T>
ArrayList<T> BinaryTree<T>::post_order() const {
    ArrayList<T> list;
    if (root != nullptr) {
        root->post_order(list);
    }
    return list;
}

}  // namespace structures
