#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <array>
#include <string>

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
			if(temp >= 100){
				if (temp > 999) temp %= 999;

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
		Interpreter( const array<Word, 1000> RAM ){
			this->RAM = RAM;
			pc = 0;
			count = 0;
		}

		void comp() const;

		int getCount() const { return  count;}

};

#endif