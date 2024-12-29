#include <iostream>
#include <vector>
#include <string>

#include "interpreter.h"

using namespace  std;


int main() {
    int N;
    string line;
    getline(cin, line);
    N = stoi(line);
    getline(cin, line); // Linha em branco

    Interpreter interpreter;

    for(int i = 0; i < N; i++) {
        vector<string> instructions;
        while (getline(cin, line) && !line.empty()) {
            instructions.push_back(line);
        }

        interpreter.init(instructions);
        interpreter.execute();

        cout << interpreter.getCount() << endl;
    }

    return 0;
}
