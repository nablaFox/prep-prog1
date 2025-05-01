#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

void print_clauses(int** clauses) {
	int n{0};
	int m{0};

	for (; clauses[n] != nullptr; n++) {
		for (int j = 0; clauses[n][j] != 0; j++) {
			m = max(m, abs(clauses[n][j]));
			cout << clauses[n][j] << " ";
		}

		cout << "0" << endl;
	}

	cout << "p cnf " << n << " " << m << endl;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << "<file.cnf>" << endl;
		return 1;
	}

	fstream cnfFile(argv[1], ios::in);

	if (cnfFile.fail()) {
		cerr << "Error reading: " << argv[1] << endl;
		return 1;
	}

	int numVariables{0}, numClauses{0};
	char prefix[100], cnf[100];

	cnfFile >> prefix >> cnf >> numClauses >> numVariables;

	if (strcmp(prefix, "p") != 0 || strcmp(cnf, "cnf") != 0 ||
		numVariables <= 0 || numClauses <= 0) {
		cerr << "Error reading header of file: " << argv[1] << endl;
		cnfFile.close();
		return 1;
	}

	int** clauses = new int*[numClauses + 1];

	bool error{false};
	int i{0};

	for (; i < numClauses && !error && !cnfFile.eof(); i++) {
		int numLiterals{0};
		cnfFile >> numLiterals;

		clauses[i] = new int[numLiterals + 1];

		for (int j = 0; j < numLiterals; j++) {
			cnfFile >> clauses[i][j];

			if (clauses[i][j] == 0 || abs(clauses[i][j]) > numVariables ||
				cnfFile.eof()) {
				error = true;
				break;
			}
		}

		clauses[i][numLiterals] = 0;
	}

	{
		char c;
		cnfFile >> c;
		if (!cnfFile.eof())
			error = true;
	}

	cnfFile.close();

	if (i != numClauses || error) {
		cerr << "Error eading file: " << argv[1]
			 << "eof or clause out of bound, or 0 encountered, or more clauses "
				"encountered"
			 << endl;

		for (int j = 0; j < i; j++) {
			delete[] clauses[j];
		}

		delete[] clauses;

		return 1;
	}

	clauses[numClauses] = nullptr;

	print_clauses(clauses);

	for (int i = 0; i < numClauses; i++) {
		delete[] clauses[i];
	}

	delete[] clauses;

	return 0;
}
