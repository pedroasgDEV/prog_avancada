#include <iostream>
#include <ostream>
#include <vector>
#include <set>
#include <string>
#include <cmath>


using namespace  std;

set<string> solution(vector<string> in, string max, string min) {
    int size_in = in.size(); // Tamanho do vetor de entrada
    set<string> result; // Soluções possiveis
    int size_smaller = min.length(); // Tamanho do menor fragmento
    int smaller_position = 0; // Qual a posição do menor fragmento se é no inicio (-1) ou no final (1) ou indefinido (0)
    vector<string> aux; // Vetor auxiliar para armazenar os fragmento opostos a menor fragmento
    int size_aux; // Tamanho do vetor auxiliar
    string init, end; // O inicio e o final de um fragmento


    // Se não for possivel encontrar somente uma solução valida
    if ( size_in % 2 != 0 || size_in == 2) { // Se a quantidae de fragmentos for impar ou igual a 2
        // Imprime todas as soluções possiveis
        for (auto i : in)
            for (auto j : in) {
                //Se a solução for maior que uma solução possivel
                if( i == j || (i + j).length() > (min + max).length() ) continue;
                result.insert(i + j);
            }
        return  result;
    }

    
    for(auto i : in){
        if(i == min) continue; // Pula o menor fragmento achado anteriormente
        
        // Se a posição do menor fragmento for no incio ou indefinida
        if (smaller_position <= 0 ) {
            init = i.substr(0, size_smaller); // Pega o inicio correspondente ao tamanho do menor fragmento
            
            if(init == min){ // Se o inicio do fragmento for igual ao menor fragmento
                smaller_position = -1; // Define a posição do menor fragmento
                continue;
            }
        }

        // Se a posição do menor fragmento for no final ou indefinida
        if (smaller_position >= 0) {
            end = i.substr(i.length() - size_smaller, size_smaller); // Pega o final correspondente ao tamanho do menor fragmento

            if(end == min) { // Se o final do fragmento for igual ao menor fragmento
                smaller_position = 1; // Define a posição do menor fragmento
                continue;
            }
        }

        // Se o fragmento for na posição oposta do menor fragmento adiciona ao vetor auxiliar
        aux.push_back(i);

    }

    size_aux = aux.size(); // Pega o tamanho do vetor auxiliar

    // Se não for possivel encontrar somente uma solução valida
    // Se há fragmentos opostos a mais ou a menos
    if ( size_aux != size_in/2 - 1){
        // Imprime todas as soluções possiveis
        for (auto i : in)
            for (auto j : in) {
                //Se a solução for maior que uma solução possivel
                if( i == j || (i + j).length() > (min + max).length() ) continue;
                result.insert(i + j);
            }
        return  result;
    }

    // Concatena os dois fragmentos com base na posição do menor
    if (smaller_position == -1) result.insert(min + max);
    if (smaller_position == 1) result.insert(max + min);

    return  result;
}


int main() {
    int N; // Quantidade de casos de teste
    string line;
    string min; // Menor fragmento 
    string max; // maior fragmento
    int min_size = 256; // Tamanho do menor fragmento
    int max_size = 0; // Tamanho do maior fragmento


    getline(cin, line); // Le a quantidade de casos de teste
    N = stoi(line);
    getline(cin, line); // Le a linha em branco

    // Loop dos casos de teste
    for(int i = 0; i < N; i++) {
        vector<string> files;

        // Armazenas os arquvios quebrados
        while (getline(cin, line) && !line.empty()) {
            if( (int) line.length() < min_size) { min = line; min_size = min.length(); }
            if( (int) line.length() > max_size) { max = line; max_size = max.length(); }
            files.push_back(line);
        }

        // Se não tiverem aquivos quebrados tenta esse caso de teste novamente
        if(files.empty()) { i--; continue; }

        set<string> result = solution(files, max, min);

        for( auto i : result ) cout << i << endl;
        cout << endl;
    }

    return 0;
}
