#include <iostream>
#include <string>
#include <set>
#include <vector>
#include "authors.h"

using namespace std;

// Função para dividir a string por ", " e ignorar tudo após ":"
vector<string> splitString(const string& str) {
    vector<string> tokens;
    size_t colonPos = str.find(':'); // Encontra a posição do caractere ':'

    // Trabalha apenas com a substring antes de ':'
    string validPart = (colonPos != string::npos) ? str.substr(0, colonPos) : str;

    size_t start = 0, end;
    const string delimiter = ", ";

    // Divide a string por ", "
    while ((end = validPart.find(delimiter, start)) != string::npos) {
        tokens.push_back(validPart.substr(start, end - start)); // Adiciona o pedaço ao vetor
        start = end + delimiter.length(); // Move o início após o delimitador
    }

    // Adiciona o último pedaço (se houver)
    if (start < validPart.length()) {
        tokens.push_back(validPart.substr(start));
    }

    return tokens;
}

int main() {
    int n; // Número de casos de teste
    cin >> n;
    string line;

    for (int i = 0; i < n; i++) {
        set<Author*> known_authors; // Autores conhecidos neste caso de teste
        int x, y;
        cin >> x >> y; // Quantidade de trabalhos e autores

        // Loop dos trabalhos
        for (int j = 0; j < x; j++) {
            getline(cin, line); // Lê a linha completa do trabalho

            if (line.empty()) {j--; continue;} //Se é lé uma linha vazia ele tenta ler dnv

            set<Author*> paper_authors; // Autores do trabalho
            vector<string> names = splitString(line); // Divide os nomes

            // Processa cada autor do trabalho
            for (size_t k = 0; k < names.size(); k += 2) {
                Author* author = nullptr;

                // Verifica se o autor já é conhecido
                for (auto l : known_authors) {
                    if (l->getLastName() == names[k] && l->getFirstName() == names[k + 1]) {
                        author = l;
                        break;
                    }
                }

                // Se não for conhecido, cria um novo autor
                if (!author) {
                    author = new Author(names[k], names[k + 1]);
                    known_authors.insert(author);
                }

                // Relaciona o autor com outros no mesmo trabalho
                for (auto l : paper_authors) {
                    author->addAuthorToQueue(l);
                    l->addAuthorToQueue(author);
                }

                paper_authors.insert(author);
            }

            
        }

        cout << "Scenario " << (i + 1) << endl;

        // Loop para os autores de interesse
        for (int j = 0; j < y; j++) {
            getline(cin, line);

            if (line.empty()) {j--; continue;} //Se é lé uma linha vazia ele tenta ler dnv

            vector<string> names = splitString(line);

            Author* author = nullptr;
            for (auto l : known_authors) {
                if (l->getLastName() == names[0] && l->getFirstName() == names[1]) {
                    author = l;
                    break;
                }
            }

            if (!author) {
                cout << line << " infinity" << endl;
            } else {
                cout << *author << endl; // Usa o operador `<<` sobrecarregado
            }
        }

        // Libera memória dos autores conhecidos
        for (auto j : known_authors) delete j;

    }

    return 0;
}
