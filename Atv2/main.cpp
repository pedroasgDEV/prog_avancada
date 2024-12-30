#include <iostream>
#include <string>
#include <vector>

#include "authors.h"

using namespace std;

vector<Author*> know_authors;



// Função para dividir a string por ", " e ignorar tudo após ":"
vector<string> splitString(const string& str) {
    vector<string> tokens;
    int colonPos = str.find(':'); // Encontra a posição do caractere ':'

    // Trabalha apenas com a substring antes de ':'
    string validPart = (colonPos != string::npos) ? str.substr(0, colonPos) : str;

    int start = 0, end;
    string delimiter = ", ";

    // Divide a string por ", "
    while ((end = validPart.find(delimiter, start)) != string::npos) {
        tokens.push_back(validPart.substr(start, end - start)); // Adiciona o pedaço ao vetor
        start = end + delimiter.length(); // Move o início após o delimitador
    }

    // Adiciona o último pedaço (se houver)
    if (start < validPart.length()) {
        tokens.push_back(validPart.substr(start));
    }

    return tokens;
}

int main(){
    return 0;
}