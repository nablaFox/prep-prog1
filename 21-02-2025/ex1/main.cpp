#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

int leggi_file(const char* fileName, int values[], int size) {
	ifstream inFile(fileName, ios::in);

	if (inFile.fail()) {
		return -1;
	}

	for (int i{0}; i < size; i++) {
		values[i] = 0;
	}

	int count{0};

	while (count < size && !inFile.eof()) {
		inFile >> values[count];
		count++;
	}

	inFile.close();

	return count;
}

bool check(int values[], int size, int inf, int sup) {
	for (int i{0}; i < size; i++) {
		if (values[i] > sup || values[i] < inf) {
			return false;
		}
	}

	return true;
}

int voto(int solutions[], int quiz[], int size) {
	int res{0};

	for (int i{0}; i < size; i++) {
		if (quiz[i] == solutions[i])
			res += 3;

		if (quiz[i] != solutions[i] && quiz[i] != 0)
			res -= 1;
	}

	return res;
}

int main(void) {
	constexpr int QUIZ_SIZE{10};

	int sol[QUIZ_SIZE];

	if (leggi_file("Soluzioni.txt", sol, QUIZ_SIZE) == -1) {
		cerr << "Failed reading solutions file" << endl;
		return -1;
	}

	if (!check(sol, QUIZ_SIZE, 1, 4)) {
		cerr << "A solution to a quiz must be a number between 1 and 4" << endl;
		return -1;
	}

	int numStudents{0};

	cout << "Inserisci il numero di partecipanti a questo appello: ";
	cin >> numStudents;

	for (int i{0}; i < numStudents; i++) {
		char nome[32]{"Studente"};
		int risp[QUIZ_SIZE];

		strcat(nome, to_string(i + 1).c_str());
		strcat(nome, ".txt");

		cout << "Sto elaborando il file " << nome << endl;

		if ((leggi_file(nome, risp, QUIZ_SIZE) == -1)) {
			cerr << "Errore nell'apertura del file!" << endl;
			continue;
		}

		ofstream outFile(nome, ios::app);

		if (outFile.fail()) {
			cerr << "Impossibile scrivere nel file " << nome << endl;
			continue;
		}

		const int score{voto(sol, risp, QUIZ_SIZE)};

		outFile << "\n";

		score < 18 ? outFile << "Insuff" : outFile << score;

		outFile.close();
	}

	return 0;
}
