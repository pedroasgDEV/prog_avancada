#ifndef AUTHORS_H 
#define AUTHORS_H

#include <climits>
#include <cmath>
#include <queue>
#include <string>
#include <iostream>

using namespace std;

class Author {
    private:
        // Atributos
        string last_name;
        string first_name;
        int erdos;

        // Comparação para a fila de prioridade
        struct CompareErdos {
            bool operator()(Author* a, Author* b) const {
                return a->erdos > b->erdos; // O autor com menor número de Erdos deve ter maior prioridade
            }
        };

        // Fila de prioridade
        std::priority_queue<Author*, std::vector<Author*>, CompareErdos> author_queue;

    public:
        // Construtor
        Author(const string& last_name = "Erdos", const string& first_name = "P.") 
            : last_name(last_name), first_name(first_name), erdos(0) {
            if (last_name == "Erdos" && first_name == "P.") {
                erdos = 0;  // O autor "Erdos" tem o número de Erdos igual a 0
            } else {
                erdos = INT_MAX;  // Outros autores têm um número de Erdos alto inicialmente
            }
        }

        // Destrutor
        ~Author() {}

        // Getters
        string getLastName() const { return last_name; } // Retorna o ultimo nome
        string getFirstName() const { return first_name; } // Retorna o primeiro nome
        int getErdos() const { return erdos; } // Retorna o numero de erdos do autor

        // Atualiza o número de Erdos baseado na fila de prioridade
        void updateErdos() {
            if (author_queue.empty()) return;
            erdos = author_queue.top()->getErdos() + 1; // O Erdos de um autor é o de seu maior colaborador + 1
        }

        // Adiciona um autor à fila de prioridade
        void addAuthorToQueue(Author* a) {
            author_queue.push(a);
            updateErdos();  // Atualiza o número de Erdos após adicionar um autor
        }

        // Verifica se um autor está na fila de prioridade com base no sobrenome
        bool findAuthorInQueue(const string& last_name) const {
            // Percorre a fila para procurar o autor
            priority_queue<Author*, vector<Author*>, CompareErdos> temp_queue = author_queue;
            while (!temp_queue.empty()) {
                if (temp_queue.top()->last_name == last_name) {
                    return true;  // Retorna verdadeiro se o autor for encontrado
                }
                temp_queue.pop();
            }
            return false;  // Retorna falso se o autor não for encontrado
        }

        //Sobrecarga a saida
        friend ostream& operator<<(ostream& out, const Author& author) {
            // Imprime o nome completo do autor
            out << author.getLastName() << ", " << author.getFirstName() << " ";
            
            // Verifica se o número de Erdos é INT_MAX (não calculado ou não disponível)
            if (author.getErdos() == INT_MAX) {
                out << "infinity";  // Se o Erdos não foi calculado, coloca "N/A"
            } else {
                // Caso contrário, imprime o número de Erdos
                out << author.getErdos();
            }

            return out;  // Retorna o fluxo de saída para permitir encadeamento
        }

};

#endif
