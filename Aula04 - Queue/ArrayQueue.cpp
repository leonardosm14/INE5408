#include <iostream>
#include "ArrayQueue.h"

int main() {

    structures::ArrayQueue<int> fila(5);

    fila.enqueue(11);
    fila.enqueue(22);
    fila.enqueue(33);
    fila.enqueue(44);
    fila.enqueue(55);

    std::cout << fila.dequeue() << std::endl;
    std::cout << fila.dequeue() << std::endl;
    std::cout << fila.dequeue() << std::endl;
    std::cout << fila.back() << std::endl;

    fila.clear();

    fila.enqueue(66);
    fila.enqueue(77);

    std::cout << fila.dequeue() << std::endl;
    std::cout << fila.dequeue() << std::endl;

    // Está vazia, verificar erro:
    // std::cout << fila.dequeue() << std::endl;

    // Deve ser zero:
    std::cout << fila.size() << std::endl;
}