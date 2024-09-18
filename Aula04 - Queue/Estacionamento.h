// Copyright [2024] <COLOQUE SEU NOME AQUI...>
#include "ArrayQueue.h"

/*
    *** Importante ***

    O código de fila em vetor está disponível internamente (não precisa de implementação aqui)

*/

void retira_veiculo(structures::ArrayQueue<int> *f, int k) {
    // ... COLOQUE SEU CÓDIGO AQUI ...
    k -= 1;
    int count = 0;
    if (k == 0) {
        f->dequeue();
    } else {
        while (count !=  k) {
            f->enqueue(f->dequeue());
            count++;
        }
        f->dequeue();
    }
}

void mantenha_veiculo(structures::ArrayQueue<int> *f, int k) {
    // ... COLOQUE SEU CÓDIGO AQUI ...
    k -= 1;
    int count = -1;
    int val;
    while (count != k) {
        val = f->dequeue();
        count++;
    }
    f->clear();
    f->enqueue(val);
}


/*
    *** Importante ***

    A função 'main()' não deve ser escrita aqui, pois é parte do código dos testes e já está implementada

*/
