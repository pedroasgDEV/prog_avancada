#include <iostream>
#include <vector>
#include <string>

#include "interpreter.h"

using namespace  std;


int main() {
    int N; // Quantidade de casos de teste
    string line;
    getline(cin, line); // Le a quantidade de casos de teste
    N = stoi(line);
    getline(cin, line); // Le a linha em branco

    Interpreter interpreter;

    // Loop dos casos de teste
    for(int i = 0; i < N; i++) {
        vector<string> instructions;

        // Armazenas as intruçõe do caso de teste atual
        while (getline(cin, line) && !line.empty()) {
            instructions.push_back(line);
        }

        // Inicia e execulta o interpretador
        interpreter.init(instructions);
        interpreter.execute();

        // Imprime a contagem de execuções
        cout << interpreter.getCount() << endl;
    }

    return 0;
}
