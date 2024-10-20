//! Copyright [2024] <LEONARDO DE SOUSA MARQUES>

#ifndef STRUCTURES_STRING_LIST_H
#define STRUCTURES_STRING_LIST_H

#include <cstdint>
#include <cstdio>
#include <stdexcept>  // C++ exceptions
#include <cstring>

namespace structures {

template<typename T>
class ArrayList {
 public:
    ArrayList();
    explicit ArrayList(std::size_t max_size);
    ~ArrayList();

    void clear();
    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool full() const;
    bool empty() const;
    bool contains(const T& data) const;
    std::size_t find(const T& data) const;
    std::size_t size() const;
    std::size_t max_size() const;
    T& at(std::size_t index);
    T& operator[](std::size_t index);
    const T& at(std::size_t index) const;
    const T& operator[](std::size_t index) const;

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};

template<typename T>
structures::ArrayList<T>::ArrayList() {
    max_size_ = DEFAULT_MAX;
    contents = new T[max_size_];
    size_ = 0;
}

template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size) {
    max_size_ = max_size;
    contents = new T[max_size_];
    size_ = 0;
}

template<typename T>
structures::ArrayList<T>::~ArrayList() {
    delete [] contents;
}

template<typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    insert(data, size());
}

template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    insert(data, 0);
}

template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (full()) {
        throw std::out_of_range("Lista Cheia.");
    }
    for (std::size_t i = size(); i > index; i--) {
        contents[i] = contents[i - 1];
    }
    contents[index] = data;
    size_++;
}

template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    if (full()) {
        throw std::out_of_range("Lista Cheia.");
    }
    if (empty()) {
        push_front(data);
    } else {
        for (std::size_t i = 0; i < size(); i++) {
            if (contents[i] > data) {
                insert(data, i);
                return;
            }
        }
        push_back(data);
    }
}

template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("Lista Vazia.");
    }
    if (index >= size()) {
        throw std::out_of_range("Index fora de intervalo.");
    }
    T aux = contents[index];
    for (std::size_t i = index + 1; i < size(); i++) {
        contents[i - 1] = contents[i];
    }
    size_--;
    return aux;
}

template<typename T>
T structures::ArrayList<T>::pop_back() {
    return pop(size() - 1);
}

template<typename T>
T structures::ArrayList<T>::pop_front() {
    return pop(0);
}

template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
    for (std::size_t i = 0; i < size(); i++) {
        if (contents[i] == data) {
            pop(i);
            return;
        }
    }
}

template<typename T>
bool structures::ArrayList<T>::full() const {
    return size() == max_size();
}

template<typename T>
bool structures::ArrayList<T>::empty() const {
    return size() == 0;
}

template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    return find(data) != size();
}

template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    for (std::size_t i = 0; i < size(); i++) {
        if (contents[i] == data) {
            return i;
        }
    }
    return size();
}

template<typename T>
std::size_t structures::ArrayList<T>::size() const {
    return size_;
}

template<typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}

template<typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Índice fora de intervalo.");
    }
    return contents[index];
}

template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    return at(index);
}

template<typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Índice fora de intervalo.");
    }
    return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
    return at(index);
}

class ArrayListString : public ArrayList<char *> {
 public:
    ArrayListString() : ArrayList() {}
    explicit ArrayListString(std::size_t max_size) : ArrayList(max_size) {}
    ~ArrayListString();

    void clear();
    void push_back(const char *data);
    void push_front(const char *data);
    void insert(const char *data, std::size_t index);
    void insert_sorted(const char *data);
    char *pop(std::size_t index);
    char *pop_back();
    char *pop_front();
    void remove(const char *data);
    bool contains(const char *data);
    std::size_t find(const char *data);
};

void ArrayListString::clear() {
    for (std::size_t i = 0; i < size(); ++i) {
        delete[] at(i);
    }
    ArrayList::clear();
}

void ArrayListString::push_back(const char *data) {
    char *copy = new char[strlen(data) + 1];
    std::snprintf(copy, strlen(data)+1, "%s", data);
    ArrayList::push_back(copy);
}

void ArrayListString::push_front(const char *data) {
    char *copy = new char[strlen(data) + 1];
    std::snprintf(copy, strlen(data)+1, "%s", data);
    ArrayList::push_front(copy);
}

void ArrayListString::insert(const char *data, std::size_t index) {
    char *copy = new char[strlen(data) + 1];
    std::snprintf(copy, strlen(data)+1, "%s", data);
    ArrayList::insert(copy, index);
}

void ArrayListString::insert_sorted(const char *data) {
    if (full()) {
        throw std::out_of_range("Lista cheia");
    }
    char *copy = new char[strlen(data) + 1];
    std::snprintf(copy, strlen(data)+1, "%s", data);
    for (std::size_t i = 0; i < size(); ++i) {
        if (std::strcmp(at(i), copy) > 0) {
            insert(copy, i);
            return;
        }
    }
    push_back(copy);
}

char *ArrayListString::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    }
    char *data = at(index);
    ArrayList::pop(index);
    return data;
}

char *ArrayListString::pop_back() {
    return pop(size() - 1);
}

char *ArrayListString::pop_front() {
    return pop(0);
}

void ArrayListString::remove(const char *data) {
    for (std::size_t i = 0; i < size(); ++i) {
        if (std::strcmp(at(i), data) == 0) {
            delete[] pop(i);
            return;
        }
    }
}

bool ArrayListString::contains(const char *data) {
    return find(data) != size();
}

std::size_t ArrayListString::find(const char *data) {
    for (std::size_t i = 0; i < size(); ++i) {
        if (std::strcmp(at(i), data) == 0) {
            return i;
        }
    }
    return size();
}

}  // namespace structures

#endif
