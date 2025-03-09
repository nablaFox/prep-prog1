#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

constexpr int MONTHS = 12;
constexpr int DAYS = 31;

struct Paziente {
	float kg;
	int age;
	int glicemia[MONTHS][DAYS];
};

int Monitora(Paziente paziente,
			 int n,
			 int ipo,
			 int iper,
			 int& ipoDays,
			 float& mean,
			 float& variance) {
	int* glicemie{paziente.glicemia[n - 1]};
	int iperDays{0};

	for (int d = 0; d < DAYS; d++) {
		iperDays += (glicemie[d] > iper);
		ipoDays += (glicemie[d] < ipo);

		mean += glicemie[d];
		variance += pow(glicemie[d], 2);
	}

	mean /= DAYS;
	variance = (variance - DAYS * pow(mean, 2)) / DAYS;

	return iperDays;
}

int main(int argc, char* argv[]) {
	if (argc != 5) {
		cout << "Il numero di parametri e' diverso da 4. "
				"Error!"
			 << endl;
		return 1;
	}

	const int month = atoi(argv[2]);
	const int ipo = atoi(argv[3]);
	const int iper = atoi(argv[4]);

	if (ipo > iper || ipo < 80 || ipo > 95 || iper < 105 || iper > 120) {
		cout << "I valori di ipoglicemia e iperglicemia non sono corretti. "
				"Errore!"
			 << endl;

		return 1;
	}

	if (month < 1 || month > MONTHS) {
		cout << "Il mese deve essere compreso fra 1 e 12" << endl;
		return 1;
	}

	ifstream file(argv[1], ios::in);

	if (file.fail()) {
		cout << "Il file non esiste. Errore!" << endl;
		return 1;
	}

	Paziente paziente{};

	file >> paziente.kg >> paziente.age;

	for (int m = 0; m < MONTHS; m++) {
		for (int d = 0; d < DAYS; d++) {
			file >> paziente.glicemia[m][d];
		}
	}

	file.close();

	int ipoDays{0};
	float mean{0.f};
	float variance{0.f};

	int iperDays =
		Monitora(paziente, month, ipo, iper, ipoDays, mean, variance);

	cout << "Il numero di giorni di iperglicemia e': " << iperDays << endl;
	cout << "Il numero di giorni di ipoglicemia e': " << ipoDays << endl;
	cout << "La media e': " << mean << endl;
	cout << "La varianza e': " << variance << endl;

	return 0;
}
