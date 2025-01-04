
#ifndef REG_H
#define REG_H

#include <iostream>
#include <istream>
#include <iterator>
#include <sstream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

//Representação de cada registro
class Reg {
	private:
		string license; // Placa do veiculo
		string type; // Se o registro foi de entrada ou saida
		int km; // Km que foi registrado
		int month; // Mês do registo
		int day; // Dia do registro
		int hour; // Hora de registo
		int minute; // Minuto do registro

	public:
		//Geters
		string getLicense () const { return  license; }
		string getType () const { return  type; }
		int getKm () const { return km; }
		int getMonth () const { return month; }
		int getDay () const { return day; }
		int getHour () const { return hour; }
		int getMinute () const { return minute; }

		// Sobrecarga do operador menor que
		bool operator<(const Reg& other) const{
			if(license != other.license) return license < other.license; // Compara as licensas 
			else if(month != other.month) return month < other.month; // Compara os meses
			else if(day != other.day) return day < other.day;  // Compara os dias
			else if(hour != other.hour) return hour < other.hour;  // Compara as horas
			else return minute < other.minute; // Compara os minutos
		}

		// Sobrecarga de entrada
		friend istream& operator>>(istream& in, Reg& r){
			string date;

			// Faz as leituras
			in >> r.license >> date  >> r.type >> r.km;

			// Separa a data e horario do registro
			sscanf(date.c_str(), "%d:%d:%d:%d", &(r.month), &(r.day),  &(r.hour),  &(r.minute));

			return  in;
		}
};

// Representação de cada conta
class Account {
	private:
		string  license; // Placa do veiculo
		float bill; // Fatura

	public:
		// Contructor
		Account(const string license) : license (license), bill(2) {}
		// Destructor
		~Account() {}

		// Geter
		string getLicense() const { return license; }

		// Metodos
		void addBill(const int km_in, const int km_out, int toll) {
			float distance = abs(km_out - km_in); // Calcula a distância
			bill += (toll * distance) / 100.0f + 1.0f; // Calcula a fatura com base no pedágio
		}


		// Sobrecarga do operador menor que
		bool operator<(const Account& other) const { return license < other.license; }

		 // Sobrecarga do operador de saída
		friend ostream& operator<<(ostream& out, const Account& a) {
			out << a.license << " $" << fixed << setprecision(2) << a.bill;
			return out;
		}
};

#endif
