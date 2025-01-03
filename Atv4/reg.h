
#ifndef REG_H
#define REG_H

#include <iostream>
#include <istream>
#include <sstream>
#include <string>

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
			if(month != other.month) return month < other.month; // Compara os meses
			else if(day != other.day) return day < other.day;  // Compara os dias
			else if(hour != other.hour) return hour < other.hour;  // Compara as horas
			else if(minute != other.minute) return minute < other.minute; // Compara os minutos
			else return license < other.license; // Compara as licensas
		}

		// Sobrecarga de entrada
		friend istream& operator>>(std::istream& in, Reg& r){
			string date;

			// Faz as leituras
			cin >> r.license;
			cin >> date;
			cin >> r.type;
			cin >> r.km;

			istringstream stream(date);
			string part;

			// Separa o mes
			getline(stream, part, ':');
			r.month = stoi(part);

			// Separa o dia
			getline(stream, part, ':');
			r.day = stoi(part);

			// Separa a hora
			getline(stream, part, ':');
			r.hour = stoi(part);
			
			// Separa o minuto
			getline(stream, part, ':');
			r.minute = stoi(part);

			return  cin;
		}
};

#endif
