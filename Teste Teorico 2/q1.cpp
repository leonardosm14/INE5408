#include <stdio.h>
#include <iostream>

using namespace std;

struct No {
    int Dado;
    No* Prox;
};

int main() {


    No *L, *i;
    int n;
    cin >> n;
    if (n == 0) {
        L = NULL;
    } else {
        L = new No;
        L->Dado = n--;
        L->Prox = NULL;
        for ( ; n > 0 ; ) {
            i = new No;
            i->Dado = n--;
            i->Prox = L;
            L = i;
        }
    }

    while ( L != NULL ) {
        cout << L->Dado << " ";
        L = L->Prox;
    }

    return 0;

}