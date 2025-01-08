#include <cmath>
#include <iostream>
#include <array>
#include <vector>

using namespace std;

array<unsigned long, 12> fatorial_cash;

unsigned long dinamic_fatorial(int n){
    if (n == 0) return 1; // Se for igual a 0
    if (!fatorial_cash[n - 1]) 
        fatorial_cash[n - 1] = n * dinamic_fatorial(n - 1); // Se não foi calculado ainda, é calculado
    return fatorial_cash[n - 1];
}

// coeficiente = n! / (n1! * n2! * ... * nk!)
unsigned long multinomial_theorem(int n, int k, vector<int> integers){
    // Se houver só um inteiro, como n1 + n2 + ... + nk = n, retorna 1
    if (k == 1) return 1;
    
    fatorial_cash.fill(0); // Inicia todos os valores como 0

    unsigned long div = 1, num;

    // Calcula o divisor
    for (int i : integers) 
        div *= dinamic_fatorial(i);

    // Calcula o numerador
    num = dinamic_fatorial(n);

    // Retorna o coeficiente
    return num / div;
}

int main() {
    int n, k;

    // Lê o n e o k
    while (cin >> n >> k) {
        vector<int> integers(k);

        // Lê os inteiros
        for (int i = 0; i < k; i++) cin >> integers[i];

        // Calcula o coeficiente
        unsigned long result = multinomial_theorem(n, k, integers);

        cout << result << endl;
    }

    return 0;
}
