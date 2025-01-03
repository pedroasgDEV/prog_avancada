#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <cmath>

using namespace std;

set<string> solution(vector<string> in) {
    set<string> results; // Soluções possíveis
    bool is_valid, is_valid_solution; // Se a solução é válida ou não

    // Tenta todas as soluções possíveis
    for (const auto& i : in) {
        for (const auto& j : in) {
            // Se os dois fragmentos forem os mesmos, a solução não é considerada
            if (&i == &j) continue;
            // Caso contrário, a solução é considerada
            results.insert(i + j);
        }
    }

    // Se a quantidade de entradas for ímpar, não é possível formar pares válidos
    if (in.size() % 2 != 0) return results;

    // Seleciona as soluções possíveis
    for (auto i = results.begin(); i != results.end();) {
        is_valid_solution = true;

        for (const auto& fragment_j : in) {
            is_valid = false;

            for (const auto& fragment_k : in) {
                // Verifica se algum par de fragmentos pode formar o resultado atual
                if (&fragment_j == &fragment_k) continue; // Evita usar o mesmo fragmento duas vezes
                if (fragment_j + fragment_k == *i || fragment_k + fragment_j == *i) {
                    is_valid = true;
                    break;
                }
            }

            // Se o resultado não puder ser formado pelo fragmento_j, a solução não é válida
            if (!is_valid) {
                is_valid_solution = false;
                break;
            }
        }

        // Remove o resultado atual se não for válido
        if (!is_valid_solution) {
            i = results.erase(i); // Apaga e avança o iterador
        } else {
            ++i; // Apenas avança o iterador se a solução for válida
        }
    }

    return results;
}

int main() {
    int N; // Quantidade de casos de teste
    string line;

    getline(cin, line); // Lê a quantidade de casos de teste
    N = stoi(line);
    getline(cin, line); // Lê a linha em branco

    // Loop dos casos de teste
    for (int i = 0; i < N; i++) {
        vector<string> files;

        // Armazena os arquivos quebrados
        while (getline(cin, line) && !line.empty()) {
            files.push_back(line);
        }

        // Se não houver arquivos quebrados, pula para o próximo caso
        if (files.empty()) {
            i--;
            continue;
        }

        // Busca pelas soluções
        set<string> result = solution(files);

        // Exibe as soluções
        for (const auto& res : result) {
            cout << res << endl;
        }

        // Adiciona uma linha em branco entre os casos de teste
        if (i < N - 1) cout << endl;
    }

    return 0;
}
