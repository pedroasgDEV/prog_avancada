#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <cassert>
#include <iostream>
#include <array>
#include <string>
#include <type_traits>

using namespace std;

class Word {
	private:
		//Atributes
		array<int, 3> wrd;

	public: 
		//Constructors
		Word() { set(0); }
		Word(const int word) { set(word); }
		Word(const array<int, 3> word) { set(word); }
		Word(string word) { set(word); }

		//Destructors
        ~Word(){}

		//Geters
		int getInt() const { return wrd[0] * 100 + wrd[1] * 10 + wrd[2]; }
		array<int, 3> getArray() const { return  wrd; }

		//Seters
		void set(const int word) {
			int temp = word;
			if (temp > 999) temp %= 1000;
			
			if(temp >= 100){
				wrd[0] = temp / 100;
				wrd[1] = (temp / 10) % 10;
				wrd[2] = temp % 10;
			}

			else if(temp >= 10){
				wrd[0] = 0;
				wrd[1] = (temp / 10) % 10;
				wrd[2] = temp % 10;
			}

			else {
				wrd[0] = 0;
				wrd[1] = 0;
				wrd[2] = temp % 10;
			}
		}
		void set(const array<int, 3> word) { wrd = word; }
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
        int pc;
		int count;
	
	public:
		//Constructor
		Interpreter(const array<Word, 1000> RAM){
			this->RAM = RAM;
			pc = 0;
			count = 0;
		}

		//Destructor
		~Interpreter(){}

		//Operations
		void setRegisInt(const int d, const int n) { registers[d].set(n); count++; count++; pc++; }
		void addRegisInt(const int d, const int n) { registers[d].set(registers[d].getInt() + n); count++; pc++; }
		void multRegisInt(const int d, const int n) { registers[d].set(registers[d].getInt() * n); count++; pc++; }
		void setRegisRegis(const int d, const int s) { registers[d].set(registers[s].getArray()); count++; pc++; }
		void addRegisRegis(const int d, const int s) { registers[d].set(registers[d].getInt() + registers[s].getInt()); count++; pc++; }
		void multRegisRegis(const int d, const int s) { registers[d].set(registers[d].getInt() * registers[s].getInt()); count++; pc++; }
		void setRegisRam(const int d, const int a) { registers[d].set(RAM[registers[a].getInt()].getArray()); count++; pc++; }
		void setRamRegis(const int s, const int a) { RAM[registers[a].getInt()].set(registers[s].getArray()); count++; pc++; }
		void goTo(const int d, const int s) { if(registers[s].getInt() != 0) pc = registers[d].getInt(); count++; }
		void halt() { count++; pc = -1; }

		//Instructors process
		void comp() {
			array<int, 3> input;
			
			while (pc == -1) {
				input = RAM[pc].getArray();

				switch (input[0]) {
					case 0:
						goTo(input[1], input[2]);
						break;
					case 1:
						halt();
						break;
					case 2:
						setRegisInt(input[1], input[2]);
						break;
					case 3:
						addRegisInt(input[1], input[2]);
						break;
					case 4:
						multRegisInt(input[1], input[2]);
						break;
					case 5:
						setRegisRegis(input[1], input[2]);
						break;
					case 6:
						addRegisRegis(input[1], input[2]);
						break;
					case 7:
						multRegisRegis(input[1], input[2]);
						break;
					case 8:
						setRegisRam(input[1], input[2]);
						break;
					case 9:
						setRamRegis(input[1], input[2]);
						break;
				}
			}
		}

		int getCount() const { return  count;}
};

#endif