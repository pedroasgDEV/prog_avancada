#include <algorithm>
#include <array>
#include <iostream>
#include <ostream>
#include <vector>
#include <string>

#include "reg.h"

using namespace std;

// Procura uma conta com base na licensa
Account* findAccount(vector<Account*> accounts, string license){
    Account* result = nullptr;
    for(auto i: accounts) if(i->getLicense() == license) {
        result = i;
        break;
    }
    return result;
}

vector<Account*> calcBills( vector<Reg> in, array<int, 24> tolls) {
    vector<Account*> result;
    int in_size = in.size(); // Quantidade de registros
    Account* aux; 

    for(int i = 0; i < in_size - 1;){
        
        // Se forem dois registros diferentes
        if (in[i].getLicense() != in[i+1].getLicense()) { ++i; continue; }
        // Se não for uma entrada precedida de um exit
        else if (in[i].getType() != "enter" || in[i+1].getType() != "exit") { ++i; continue; }

        // Procura a placa nas contas existentes
        aux = findAccount(result, in[i].getLicense());
        
        // Se não for achada cria uma para ela
        if(aux == nullptr) {
            aux = new Account(in[i].getLicense());
            result.push_back(aux);
        }

        // Adiciona do pedagio da viagem atual a fatura total
        aux->addBill(in[i].getKm(), in[i+1].getKm(), tolls[in[i].getHour()]);

        i += 2;
    }

    return result;
}


int main() {
    int N; // Quantidade de casos de teste
    cin >> N;
    cin.ignore(); // Ignorar resto da linha

    // Loop dos casos de teste
    for (int i = 0; i < N; i++) {
        vector<Reg> records;           // Vetor de registros
        array<int, 24> tolls;     // Array com a taxa por km nas 24 horas
        int temp_int;

        // Leitura das taxas por hora
        for (int j = 0; j < 24; j++) {
            cin >> temp_int;
            tolls[j] = temp_int;
        }

        cin.ignore(); // Ignorar o resto da linha

        // Leitura dos registros
        while (true) {
            Reg temp_reg;
            string line;
            getline(cin, line);

            if (line.empty()) break; // Quebra no final do caso de teste

            istringstream lineStream(line);
            lineStream >> temp_reg;
            records.push_back(temp_reg);
        }

        // Ordenar os registros
        stable_sort(records.begin(), records.end());

        // Calcula as faturas de cada conta
        vector<Account*> result = calcBills(records, tolls);

        // Ordena as contas
        stable_sort(result.begin(), result.end());

        // Imprimir os registros ordenados
        for (const auto& r : result) {
            cout << *r << endl;
        }

        cout << endl; // Linha em branco entre os casos de teste
    }

    return 0;
}
