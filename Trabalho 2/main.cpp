#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>

using namespace std;

namespace structures {

    // Definição do nó da Trie
    struct NoTrie {
        NoTrie* filhos[26];       // Ponteiros para filhos (um para cada letra do alfabeto)
        unsigned long posicao;    // Posição no arquivo
        unsigned long comprimento; // Comprimento da linha no arquivo
        bool final_da_palavra;

        NoTrie() : posicao(0), comprimento(0), final_da_palavra(false) {
            for (int i = 0; i < 26; ++i) {
                filhos[i] = nullptr;
            }
        }
    };

    // Classe Trie
    class Trie {
    public:
        NoTrie* raiz;

        Trie() {
            raiz = new NoTrie(); // Cria a raiz da Trie
        }

        ~Trie() {
            deletar(raiz);
        }

        void inserir(const string& palavra, unsigned long posicao, unsigned long comprimento) {
            NoTrie* curr = raiz;
            for (char c : palavra) {
                int index = c - 'a';
                if (curr->filhos[index] == nullptr) {
                    curr->filhos[index] = new NoTrie();
                }
                curr = curr->filhos[index];
            }
            curr->final_da_palavra = true;
            curr->posicao = posicao;
            curr->comprimento = comprimento;
        }

        void buscar(const string& prefixo) {
            NoTrie* curr = raiz;
            for (char c : prefixo) {
                int index = c - 'a';
                if (curr->filhos[index] == nullptr) {
                    cout << prefixo << " is not prefix" << endl;
                    return;
                }
                curr = curr->filhos[index];
            }

            unsigned long count = 0;
            contarPalavras(curr, count);

            cout << prefixo << " is prefix of " << count << " words" << endl;

            if (curr->final_da_palavra) {
                cout << prefixo << " is at (" << curr->posicao << "," << curr->comprimento << ")" << endl;
            }
        }

    private:
        void deletar(NoTrie* no) {
            for (int i = 0; i < 26; i++) {
                if (no->filhos[i]) {
                    deletar(no->filhos[i]);
                }
            }
            delete no;
        }

        void contarPalavras(NoTrie* no, unsigned long& count) {
            if (no->final_da_palavra) {
                count++;
            }
            for (int i = 0; i < 26; i++) {
                if (no->filhos[i]) {
                    contarPalavras(no->filhos[i], count);
                }
            }
        }
    };
}

int main() {
    string filename;
    string palavra;

    cin >> filename;
    
    ifstream filedic(filename);
    if (!filedic.is_open()) {
        cerr << "Erro ao abrir o arquivo " << filename << endl;
        throw runtime_error("Erro no arquivo .dic");
    }

    string linha;
    structures::Trie trie;
    unsigned long posicao = 0;

    while (getline(filedic, linha)) {
        size_t inicio = linha.find('[');
        size_t fim = linha.find(']');
        if (inicio != string::npos && fim != string::npos) {
            string palavra = linha.substr(inicio + 1, fim - inicio - 1);
            unsigned long comprimento = linha.length();
            trie.inserir(palavra, posicao, comprimento);
        }
        posicao += linha.length() + 1; // Inclui o caractere de nova linha
    }
    filedic.close();

    while (1) {  // leitura das palavras ate' encontrar "0"
        cin >> palavra;
        if (palavra.compare("0") == 0) {
            break;
        }
        trie.buscar(palavra);
    }

    return 0;
}
