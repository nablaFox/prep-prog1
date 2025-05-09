#include <fstream>
#include <iostream>

using namespace std;

constexpr int MAX_LINE_LENGTH{127};
constexpr int MAX_NUMS{13};
constexpr int MAX_BITS{8};

int converti(int b[], int n) {
	int num{0};

	for (int i = 0; i < n; i++) {
		num = 2 * num + b[i];
	}

	return num;
}

int somma(int arr[], int n) {
	int res{0};

	for (int i{0}; i < n; i++) {
		res += arr[i];
	}

	return res;
}

void elaborariga(const char* str, int num[], int& ris) {
	int b[MAX_BITS]{0};
	int i{0}, j{0}, n{0};

	for (int i = 0; i < MAX_NUMS; i++) {
		num[i] = 0;
	}

	while (str[j] != '\0') {
		if (str[j] == ';') {
			ris = converti(b, n);
			j++;
			continue;
		}

		if (str[j] == '+' || str[j] == '=') {
			num[i] = converti(b, n);

			for (int k{0}; k < MAX_BITS; k++) {
				b[k] = 0;
			}

			n = 0;
			i++;
			j++;

			continue;
		}

		b[n] = str[j] == '1' ? 1 : 0;

		n++;
		j++;
	}
}

int main(int argc, char* argv[]) {
	ifstream finput("inputdati.txt");

	if (finput.fail()) {
		cerr << "Impossibile aprire il file inputdati.txt" << endl;
		return -1;
	}

	ofstream foutput("outputcheck.txt");

	if (foutput.fail()) {
		cerr << "Impossibile aprire il file outputcheck.txt" << endl;
		return -1;
	}

	char line[MAX_LINE_LENGTH];

	while (finput >> line) {
		int num[MAX_NUMS];
		int res;

		elaborariga(line, num, res);

		if (res == somma(num, MAX_NUMS)) {
			foutput << res << endl;
		} else {
			foutput << "Errore" << endl;
		}
	}

	foutput.close();
	finput.close();

	return 0;
}
