#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>

#include "ArrayStack.h"
#include "ArrayQueue.h"

using namespace std;


class Cenario {
  public:
    Cenario(string& texto, size_t indice_inicial) {
        size_t pos = indice_inicial;
        nome = proxima_tag_conteudo(texto, pos, "nome");
        altura = static_cast<size_t>( stoi( proxima_tag_conteudo(texto, pos, "altura") ) );
        largura = static_cast<size_t>( stoi( proxima_tag_conteudo(texto, pos, "largura") ) );
        x = static_cast<size_t>( stoi( proxima_tag_conteudo(texto, pos, "x") ) );
        y = static_cast<size_t>( stoi( proxima_tag_conteudo(texto, pos, "y") ) );
        matriz = matriz_remove_espacos( proxima_tag_conteudo(texto, pos, "matriz") );
        indice_final = pos;
    }
    ~Cenario() {};
    string nome;
    size_t altura;
    size_t largura;
    size_t x;
    size_t y;
    string matriz;
    size_t indice_final;

  private:
    string proxima_tag(string& texto, size_t& pos) {
        string tag = "";
        for ( ; pos < texto.length(); pos++) {
            if (texto[pos] == '<') {
                pos++;
                while (texto[pos] != '>') {
                    tag += texto[pos];
                    pos++;
                }
                pos++;
                return tag;
            }
        }
        return tag;
    }
    string proximo_conteudo(string& texto, size_t& pos) {
        string txt = "";
        while (texto[pos] != '<') {
            txt += texto[pos];
            pos++;
        }
        while (texto[pos] != '>') {
            pos++;
        }
        pos++;
        return txt;
    }
    string proxima_tag_conteudo(string& texto, size_t& pos, string nome_tag) {
        string tag = "";
        while (tag != nome_tag) {
            tag = proxima_tag(texto, pos);
        }
        return proximo_conteudo(texto, pos);
    }
    string matriz_remove_espacos(string texto) {
        string saida;
        for (int i = 0; i < texto.length(); i++) {
            if (texto[i] == '0' || texto[i] == '1') {
                saida += texto[i];
            }
        }
        return saida;
    }
};


bool verifica_aninhamentos(string texto) {
    int len = texto.length();
    structures::ArrayStack<string> stack_tags(len);

    string tag = "";

    for (int i = 0; i < len; i++) {
        if (texto[i] == '<') {
            bool is_closing_tag = (i + 1 < len && texto[i + 1] == '/');
            if (is_closing_tag) {
                i++;  
            }

            
            for (int j = i + 1; j < len; j++) {
                if (texto[j] == '>') {
                    i = j;  
                    break;
                }
                tag += texto[j];  
            }

            if (is_closing_tag) {
                if (stack_tags.empty() || stack_tags.pop() != tag) {
                    return false;  
                }
            } else {
                stack_tags.push(tag);  
            }
        }
        tag = "";
    }

    return stack_tags.empty();  
}

size_t quantidade_matrizes(const string& texto) {
    size_t count = 0;
    size_t pos = 0;

    while ((pos = texto.find("<matriz>", pos)) != string::npos) {
        count++;
        pos += 8; 
    }

    return count;
}

size_t calcula_area(Cenario& c) {

    string E = c.matriz;
    size_t x = c.x;
    size_t y = c.y;
    size_t altura = c.altura;
    size_t largura = c.largura;

    size_t area = 0;
    vector<pair<int, int>> direcoes = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    // matriz E;

    structures::ArrayQueue<pair<size_t, size_t>> queue(altura*largura); // (x,y)

    string R = "";
    for (int i = 0; i < E.length(); i++) {
        R += "0";
    }

    if (E[x * largura + y] == '1') {
        R[x * largura + y] = '1';
        queue.enqueue(make_pair(x, y));
        area++;
    }

    while (!queue.empty()) {
        pair<size_t, size_t> aux = queue.dequeue();
        
        for (int i = 0; i < direcoes.size(); i++) {
            size_t nx = aux.first + direcoes[i].first;
            size_t ny = aux.second + direcoes[i].second;

            if (nx < altura && ny < largura) {
                size_t idx = nx * largura + ny;
                if (E[idx] == '1' && R[idx] == '0') {
                    queue.enqueue(make_pair(nx, ny));
                    R[idx] = '1';
                    area++;
                }
            }
        }
    }
    return area;
}

/**********************
    FUNÇÃO PRINCIPAL
***********************/
int main() {

    string filename;

    std::cin >> filename;  // nome do arquivo de entrada 
                           // (no 'executar': escrever pelo teclado;
                           //  no 'avaliar' : nome é passado pelos testes)

    // Abertura do arquivo
    ifstream filexml(filename);
    if (!filexml.is_open()) {
        cerr << "Erro ao abrir o arquivo " << filename << endl;
        throw runtime_error("Erro no arquivo XML");
    }

    // Leitura do XML completo para 'texto'
    string texto;
    char character;
    while (filexml.get(character)) {
        texto += character;
    }

    // Problema 1
    bool aninhamentos = verifica_aninhamentos(texto);

    if (!aninhamentos) {
        cout << "erro" << endl;
    } else {
        int num_matrizes = quantidade_matrizes(texto);
         size_t i = 0;
         for (int m = 0; m < num_matrizes; m++) {
            Cenario c(texto, i); 
            int area = calcula_area(c);
            cout << c.nome << " " << area << endl;
            i = c.indice_final;
        }
    }

    return 0;
}
