// Copyright [2022] <COLOQUE SEU NOME AQUI...>
#include "./array_stack.h"

bool verificaChaves(std::string trecho_programa) {
    //bool resposta = true;
    int  tamanho  = trecho_programa.length();
    structures::ArrayStack<char> pilha(500);
    
    for (int i = 0; i < tamanho; i++) {
        // condições de parada dor 'for' podem ser adicionadas...
        // COLOCAR SEU CÓDIGO AQUI...

        char c = trecho_programa[i];
        if (c == '(' || c == '{' || c = '[') {
            pilha.push(c);
        } else if (c == ')') {
            if ('(' != pilha.pop()) 
                return false;
        } else if (c == '}') {
            if ('{' != pilha.pop()) 
                return false;
        } else if (c == ']') {
            if ('[' != pilha.pop()) 
                return false;
        }

        return true;

         
    }
    
}
