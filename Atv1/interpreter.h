#ifndef INTERPRETER_H
#define INTERPRETER_H

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

		//Overloads
		friend std::istream& operator>>(std::istream& in, Word& word) {
			string temp;

			in >> temp;

			word.wrd[0] = temp[0] - '0';
			word.wrd[1] = temp[1] - '0';
			word.wrd[2] = temp[2] - '0';

			return in;
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
		void storeRegisRegis(const int d, const int s) { registers[d].set(registers[s].getArray()); count++; pc++; }
		void addRegisRegis(const int d, const int s) { registers[d].set(registers[d].getInt() + registers[s].getInt()); count++; pc++; }
		void multRegisRegis(const int d, const int s) { registers[d].set(registers[d].getInt() * registers[s].getInt()); count++; pc++; }
		void setRegisRam(const int d, const int a) { registers[d].set(RAM[registers[a].getInt()].getArray()); count++; pc++; }
		void setRamRegis(const int s, const int a) { RAM[registers[a].getInt()].set(registers[s].getArray()); count++; pc++; }
		void goTo(const int d, const int s) { if(registers[s].getInt() != 0) pc = registers[d].getInt(); count++; }
		void halt() { count++; pc = -1; }

		
		void comp() const;

		int getCount() const { return  count;}
};

#endif