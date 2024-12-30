
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <array>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

//Representação de cada palavra dos registradores e da RAM
class Word {
	private:
		// Atributos
		int wrd;

	public: 
		// Constructores
		Word() { set(0); } // Construtor sem entrada
		Word(const int word) { set(word); } // Construtor a partir de um inteiro como entrada
		Word(string word) { set(word); } // Construtor a partir de uma sting como entrada

		// Destructores
        ~Word(){}

		// Geters
		int getInt() const { return wrd; } //Retorna o valor em inteiro

		// Seters
		// Define um valor a partir de um inteiro
		void set(const int word) {
			int temp = word % 1000; // Se o valor for maior que 999
			wrd = temp;
		}

		// Define um valor a partir de uma string
		void set(const string word) {
			wrd = stoi(word);
		}       
};

//Representação de um Interpretador
class Interpreter {
    private:
		// Atributos
        array<Word, 1000> RAM;
        array<Word, 10> registers;
        int pc = 0; // Program Counter
		int count = 0; // Contagem de execuções
	
	public:
		// Inicia o interpretador
		void init(const vector<string>& instructions) {
			// Inicia os contadores
			pc = 0;
			count = 0;

			// Inicia os registradores
			for (auto& reg : registers) reg.set(0);

			// Inicia a RAM
			for (size_t i = 0; i < RAM.size(); ++i) {
				if (i < instructions.size()) RAM[i].set(instructions[i]); // Coloca as instruções no inicio da RAM
				else RAM[i].set(0); // Atribui 0 aos outras posições da RAM
			}
		}

		// Execulta o interpretador
		void execute() {
			// Inicia um loop até pc for -1
			 while (pc != -1) {
				int instr = RAM[pc].getInt(); // Pega a instrução atual
				int op = instr / 100, d = (instr / 10) % 10, n = instr % 10; // Separa as centenas, dezenas e unidades
				++count; //Aumenta a contagem

				switch (op) {
					case 1: // halt - para parar a execução
						pc = -1; // Transforma pc = -1
						break;
					case 2: // Coloca o valor N no registro d
						registers[d].set(n); 
						pc++;
						break;
					case 3: // Soma n ao valor do registro D
						registers[d].set(registers[d].getInt() + n);
						pc++;
						break;
					case 4: // Multiplica N ao valor do registro D
						registers[d].set(registers[d].getInt() * n);
						pc++;
						break;
					case 5: // Coloca o valor do registro N ao registro D
						registers[d].set(registers[n].getInt());
						pc++;
						break;
					case 6: // Soma o valor do registro N ao registro D
						registers[d].set(registers[d].getInt() + registers[n].getInt());
						pc++;
						break;
					case 7: // Multiplica o valor do registro N ao registro D
						registers[d].set(registers[d].getInt() * registers[n].getInt());
						pc++;
						break;
					case 8: // Coloca o valor da posição N da RAM ao registro D
						registers[d].set(RAM[registers[n].getInt()].getInt());
						pc++;
						break;
					case 9: // Coloca o valor do registro D para posição N da RAM
						RAM[registers[n].getInt()].set(registers[d].getInt());
						pc++;
						break;
					case 0: // Vai para a posição do valor do registrador D, se o valor do registrador N for 0
						if (registers[n].getInt() != 0) {
							pc = registers[d].getInt();
						} else {
							pc++;
						}
						break;
				}
			}
		}

		// Retorna a contagens de execuções
		int getCount() const { return  count;}
};

#endif
