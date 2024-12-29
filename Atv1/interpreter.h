
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <array>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Word {
	private:
		//Atributes
		array<int, 3> wrd;

	public: 
		//Constructors
		Word() { set(0); }
		Word(const int word) { set(word); }
		Word(string word) { set(word); }

		//Destructors
        ~Word(){}

		//Geters
		int getInt() const { return wrd[0] * 100 + wrd[1] * 10 + wrd[2]; }

		//Seters
		void set(const int word) {
			int temp = word % 1000;
			wrd[0] = temp / 100;
			wrd[1] = (temp / 10) % 10;
			wrd[2] = temp % 10;
		}
		void set(const string word) {
			wrd[0] = word[0] - '0';
			wrd[1] = word[1] - '0';
			wrd[2] = word[2] - '0';
		}       
};

class Interpreter {
    private:
		//Atributes
        array<Word, 1000> RAM;
        array<Word, 10> registers;
        int pc = 0;
		int count = 0;
	
	public:
		//Constructor
		void init(const vector<string>& instructions) {
			pc = 0;
			count = 0;

			for (auto& reg : registers) reg.set(0);

			for (size_t i = 0; i < RAM.size(); ++i) {
				if (i < instructions.size()) RAM[i].set(instructions[i]);
				else RAM[i].set(0);
			}
		}

		void execute() {
			 while (pc != -1) {
				int instr = RAM[pc].getInt();
				int op = instr / 100, d = (instr / 10) % 10, n = instr % 10;
				++count;

				switch (op) {
					case 1: // halt
						pc = -1;
						break;
					case 2: // set register d to n
						registers[d].set(n);
						pc++;
						break;
					case 3: // add n to register d
						registers[d].set(registers[d].getInt() + n);
						pc++;
						break;
					case 4: // multiply register d by n
						registers[d].set(registers[d].getInt() * n);
						pc++;
						break;
					case 5: // set register d to the value of register s
						registers[d].set(registers[n].getInt());
						pc++;
						break;
					case 6: // add value of register s to register d
						registers[d].set(registers[d].getInt() + registers[n].getInt());
						pc++;
						break;
					case 7: // multiply register d by the value of register s
						registers[d].set(registers[d].getInt() * registers[n].getInt());
						pc++;
						break;
					case 8: // set register d to value in RAM at address in register a
						registers[d].set(RAM[registers[n].getInt()].getInt());
						pc++;
						break;
					case 9: // set RAM at address in register a to value of register s
						RAM[registers[n].getInt()].set(registers[d].getInt());
						pc++;
						break;
					case 0: // goto location in register d unless register s is 0
						if (registers[n].getInt() != 0) {
							pc = registers[d].getInt();
						} else {
							pc++;
						}
						break;
				}
			}
		}

		int getCount() const { return  count;}
};

#endif
