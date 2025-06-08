#include <iostream>

using namespace std;

bool* init(int size) {
	return new bool[size];
}

void insert(bool* filter, int size, char* word) {
	for (int i = 0; word[i] != '\0'; i++) {
		const int index = (int)word[i] % size;

		filter[index] = true;
	}
}

bool check(bool* filter, int size, char* checked) {
	for (int i = 0; checked[i] != '\0'; i++) {
		const int index = (int)checked[i] % size;

		if (!filter[index])
			return false;
	}

	return true;
}

void deinit(bool* filter) {
	delete[] filter;
}

int main(int argc, char* argv[]) {
	// Se modificate la funzione "main", ricordarsi poi di ripristinare il
	// codice originale
	int n = 255;

	bool* bloom_filter = init(n);

	char ciao[] = {'c', 'i', 'a', 'o', '\0'};
	insert(bloom_filter, n, ciao);
	cout << "Ho inserito la parola 'ciao' nel bloom filter" << endl;

	if (check(bloom_filter, n, ciao)) {
		cout << "La parola 'ciao' è presente nel bloom filter " << endl;
	} else {
		cout << "La parola 'ciao' NON è presente nel bloom filter " << endl;
	}

	char volo[] = {'v', 'o', 'l', 'o', '\0'};
	if (check(bloom_filter, n, volo)) {
		cout << "La parola 'volo' è presente nel bloom filter " << endl;
	} else {
		cout << "La parola 'volo' NON è presente nel bloom filter " << endl;
	}

	deinit(bloom_filter);

	return 0;
}
