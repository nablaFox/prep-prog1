#include <iostream>
#include <fstream>

using namespace std;

struct Abbonamento {
	int numero;
	char nome[32];
	char cognome[32];
	char tipo;
	float costo;
};

float guadagno(Abbonamento abb[], int n) {
	float total{0};

	for (int i{0}; i < n; i++) {
		total += abb[i].costo * 0.9;
	}

	return total;
}

char elabora(Abbonamento abb[], int n, float r[4]) {
	for (int i{0}; i < 4; i++) {
		r[i] = 0.f;
	}

	char tipoMaxRicavo{'a'};
	float maxRicavo{0};

	for (int i{0}; i < n; i++) {
		char currTipo = abb[i].tipo;
		float currRicavo = abb[i].costo;

		if (currTipo == 'a')
			r[0] += currRicavo;

		if (currTipo == 'm')
			r[1] += currRicavo;

		if (currTipo == 's')
			r[2] += currRicavo;

		if (currTipo == 'g')
			r[3] += currRicavo;

		if (r[1] > maxRicavo) {
			maxRicavo = r[1];
			tipoMaxRicavo = 'm';
		}

		else if (r[2] > maxRicavo) {
			maxRicavo = r[2];
			tipoMaxRicavo = 's';
		}

		else if (r[3] > maxRicavo) {
			maxRicavo = r[3];
			tipoMaxRicavo = 'g';
		}
	}

	return tipoMaxRicavo;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "Utilizzo: " << argv[0] << " <file_abbonamenti>" << endl;
		return 1;
	}

	ifstream inputFile(argv[1], ios::in);

	if (inputFile.fail()) {
		cerr << "Il file non esiste. Errore!" << endl;
		return 1;
	}

	int N{0};
	inputFile >> N;

	Abbonamento abb[N];

	for (int i{0}; !inputFile.eof() && !inputFile.fail() && i < N; i++) {
		inputFile >> abb[i].numero >> abb[i].nome >> abb[i].cognome >>
			abb[i].tipo;

		float costo{0};

		switch (abb[i].tipo) {
			case 'a':
				costo = 500;
				break;
			case 'm':
				costo = 150;
				break;
			case 's':
				costo = 50;
				break;
			case 'g':
				costo = 10;
				break;
			default:
				cerr << "Tipo di abbonamento non valido" << endl;
				return 1;
		}

		abb[i].costo = costo;
	}

	inputFile.close();

	cout << "Guadagno totale: " << guadagno(abb, N) << endl;

	float ricaviParziali[4];
	char tipoMaxRicavo = elabora(abb, N, ricaviParziali);

	ofstream outputFile("risultati.txt", ios::out);

	if (outputFile.fail()) {
		cerr << "Impossibile creare il file di output risultati.txt" << endl;
		return 1;
	}

	for (int i{0}; i < N; i++) {
		if (abb[i].tipo != tipoMaxRicavo)
			continue;

		outputFile << abb[i].numero << " " << abb[i].nome << " "
				   << abb[i].cognome << " " << abb[i].tipo << " " << " "
				   << abb[i].costo << endl;
	}

	outputFile.close();

	return 0;
}
