#include <iostream>
#include <vector>
#include <string>

#include "interpreter.h"

using namespace  std;


int main() {
    int testCases;
    string line;
    getline(cin, line);
    testCases = stoi(line);
    getline(cin, line); // Linha em branco

    Interpreter interpreter;

    while (testCases--) {
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
