// Copyright [2022] <COLOQUE SEU NOME AQUI...>
#include <string>


class Aluno {
 public:
    Aluno() {}  // construtor
    ~Aluno() {}  // destrutor
    std::string devolveNome() {
        return nome;
    }
    int devolveMatricula() {
        return matricula;
    }
    void escreveNome(std::string nome_) {
        nome = nome_;
    }
    void escreveMatricula(int matricula_) {
        matricula = matricula_;
    }
 private:
    std::string nome;
    int matricula;
};

/*
(4) cria um novo vetor somente com matrículas maiores ou iguais a menor_matr, 
a partir de um vetor de N objetos do tipo Aluno:

t de entrada: [{'Fulano',1010}, {'Beltrano',2020}, {'Fulana',7070}, {'Cicrana':1515}, {'Beltrana',8080}]; 
N = 5, menor_matr = 2020
tf de saída: [{'Beltrano',2020}, {'Fulana',7070}, {'Beltrana',8080}]

*/

Aluno *turma_filtra(Aluno t[], int N, int menor_matr) {
    Aluno *tf;
    int contador = 0;

    for (int i = 0; i < N; i++) {
        int m = t[i].devolveMatricula();
        if (m >= menor_matr) {
            contador += 1;
        }
    }

    tf = new Aluno[contador];

    int c = 0;
    for (int i = 0; i < N; i++) {
        int menor = t[i].devolveMatricula();

        if (menor >= menor_matr) {
            tf[c].escreveNome(t[i].devolveNome());
            tf[c].escreveMatricula(menor);
            c++;
        }

    }
    return tf;
}

/*
(5) crie um vetor de inteiros com 26 posições, na qual cada posição corresponda a 
contagem de alunos com a respectiva primeira letra do nome em maiúsculo ('A' na posição 0, 
'B' na posição 1, ..., 'Z' na posição 25):
int *turma_conta(Aluno t[], int N);

Exemplo:

t de entrada: [{'Fulano',1010}, {'Beltrano',2020}, {'Fulana',7070}, {'Cicrana':1515}, {'Beltrana',8080}], N = 5
vetor de saída: [0,2,1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]

*/

int *turma_conta(Aluno t[], int N) {
    int *c;
    // c = nullptr;  // retirar e alocar (com new)
    c = new int[26];

    for (int i = 0; i < 26; i++) {
        c[i] = 0;
    }
    
    for (int i = 0; i < N; i++) {
        char primeira_letra = t[i].devolveNome()[0];
        int v = primeira_letra - 'A';
        c[v] += 1;
        
        }
    return c;
}
/*
    *** Importante ***

    A função 'main()' não deve ser escrita aqui, pois é parte do código dos testes e já está implementada

*/
