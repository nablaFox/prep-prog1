#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

float Percentuale(int m, int n) {
	return 100.f * static_cast<float>(m) / static_cast<float>(n);
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cerr << "Utilizzo: " << argv[0] << " <temp_1> " << "<temp_2>" << endl;
		return -1;
	}

	ifstream temp1(argv[1]);

	if (temp1.fail()) {
		cerr << "Impossibile aprire: " << argv[1] << endl;
		return -1;
	}

	ifstream temp2(argv[2]);

	if (temp2.fail()) {
		cerr << "Impossibile apire: " << argv[2] << endl;
		return -1;
	}

	int n{0}, m{0};
	float read1{0}, read2{0};

	while (temp1 >> read1 && temp2 >> read2) {
		m += read1 > read2;
		n++;
	}

	if (n == 0) {
		cerr << "Il numero delle misurazioni è uguale a zero, per cui non "
				"posso calcolare la percentuale"
			 << endl;
		return -1;
	}

	cout << "La percentuale di misurazioni in cui la tempearatura del motore1 "
			"ha superato quella del motore2 e' del "
		 << Percentuale(m, n) << "%." << endl;

	temp1.close();
	temp2.close();

	return 0;
}
