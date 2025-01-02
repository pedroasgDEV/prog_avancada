#include <iostream>
#include <vector>
#include <string>


using namespace  std;

string solution(vector<string> in) {
    int size_in = in.size(); // Tamanho do vetor de entrada
    string result = ""; // Resultado final
    string smaller = in[0]; // Menor arquivo
    string bigger; // Maior arquivo oposto ao menor arquivo
    int size_smaller; // Tamanho da menor palavra
    int smaller_position = 0; // Qual a posição da menor palavra se é no inicio (-1) ou no final (1) ou indefinido (0)
    vector<string> aux; // Vetor auxiliar para armazenar os strings opostas a menor
    int size_aux; // Tamanho do vetor auxiliar
    string init, end; // O inicio e o final de uma string


    // Se só tiverem dois arquivos quebrados
    if ( size_in == 2 ) return in[0] + in[1] + '\n' + in[1] + in[0] + '\n';

    //Encontra o menor arquivo
    for(int i = 1; i < size_in; i++)
        if ( in[i].length() < smaller.length() ) smaller = in[i];

    size_smaller = smaller.length();

    
    for(auto i : in){
        if(i == smaller) continue; // Pula a menor palavra achada anteriormente
        
        // Se a posição da menor palavra for no incio ou indefinida
        if (smaller_position <= 0 ) {
            init = i.substr(0, size_smaller); // Pega o inicio correspondente ao tamanho do menor arquivo
            
            if(init == smaller){ // Se o inicio do arquivo for igual ao menor arquivo
                smaller_position = -1; // Define a posição da menor palavra
                continue;
            }
        }

        // Se a posição da menor palavra for no final ou indefinida
        if (smaller_position >= 0) {
            end = i.substr(i.length() - size_smaller, size_smaller); // Pega o final correspondente ao tamanho do menor arquivo

            if(end == smaller) { // Se o final do arquivo for igual ao menor arquivo
                smaller_position = 1; // Define a posição da menor palavra
                continue;
            }
        }

        // Se o arquivo for na posição oposta do menor arquivo adiciona ao vetor auxiliar
        aux.push_back(i);

    }

    size_aux = aux.size(); // Pega o tamanho do vetor auxiliar
    bigger = aux[0];

    // Encontra o maior arquivo oposto ao menor arquivo
    for(int i = 1; i < size_aux; i++)
        if ( aux[i].length() > bigger.length() ) bigger = aux[i];

    // Concatena os dois arquivos com base na posição do menor
    if (smaller_position == -1) result = smaller + bigger + '\n';
    if (smaller_position == 1) result = bigger + smaller + '\n';

    return  result;
}


int main() {
    int N; // Quantidade de casos de teste
    string line;
    getline(cin, line); // Le a quantidade de casos de teste
    N = stoi(line);
    getline(cin, line); // Le a linha em branco

    // Loop dos casos de teste
    for(int i = 0; i < N; i++) {
        vector<string> files;

        // Armazenas os arquvios quebrados
        while (getline(cin, line) && !line.empty()) {
            files.push_back(line);
        }

        // Se não tiverem aquivos quebrados tenta esse caso de teste novamente
        if(files.empty()) { i--; continue; }

        cout << solution(files) << endl;
    }

    return 0;
}
