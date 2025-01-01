#ifndef AUTHORS_H 
#define AUTHORS_H

#include <climits>
#include <cmath>
#include <queue>
#include <string>
#include <iostream>

using namespace std;

constexpr int INFINITY_ERDOS = 9999999;

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
        std::priority_queue<Author*, std::vector<Author*>, CompareErdos> collaborators;

    public:
        // Construtor
        Author(const string& last_name = "Erdos", const string& first_name = "P.") 
            : last_name(last_name), first_name(first_name), erdos(INFINITY_ERDOS) {
            if (last_name == "Erdos" && first_name == "P.") {
                erdos = 0;  // O autor "Erdos" tem o número de Erdos igual a 0
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
            int new_erdos = collaborators.top()->getErdos() + 1; // Pega o nuemero de Erdos do menor da lista de prioridade
            if (new_erdos < erdos) { // Verica se é menor que o atual
                erdos = new_erdos; // Se for menor, se torna o novo numero de Erdos
            }
        }

        // Adiciona um autor à fila de prioridade
        void addAuthorToQueue(Author* a) {
            collaborators.push(a);
            updateErdos();  // Atualiza o número de Erdos após adicionar um autor
        }

        //Sobrecarga a saida
        friend ostream& operator<<(ostream& out, const Author& author) {
            // Imprime o nome completo do autor
            out << author.getLastName() << ", " << author.getFirstName() << " ";
            
            // Verifica se o número de Erdos é INT_MAX (não calculado ou não disponível)
            if (author.getErdos() == INFINITY_ERDOS) {
                out << "infinity";  // Se o Erdos não foi calculado, coloca "N/A"
            } else {
                // Caso contrário, imprime o número de Erdos
                out << author.getErdos();
            }

            return out;  // Retorna o fluxo de saída para permitir encadeamento
        }

};

#endif