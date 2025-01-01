#include <iostream>
#include <vector>
#include <string>


using namespace  std;

stri


int main() {
    int N; // Quantidade de casos de teste
    string line;
    getline(cin, line); // Le a quantidade de casos de teste
    N = stoi(line);

    // Loop dos casos de teste
    for(int i = 0; i < N; i++) {
        getline(cin, line); // Le a linha em branco
        vector<string> file;
        

        // Armazenas as intruçõe do caso de teste atual
        while (getline(cin, line) && !line.empty()) {
            file.push_back(line);
        }
    }

    return 0;
}
