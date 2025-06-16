#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

constexpr int MAX_WORD_SIZE = 100;

bool is_letter(char c) {
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

const char* shift_word(char word[], int shift, int start, int end) {
	const int len = end - start + 1;

	char* temp = new char[len];

	for (int i = 0; i < len; i++) {
		temp[i] = word[start + (i + shift) % len];

		if (temp[i] >= 'A' && temp[i] <= 'Z') {
			temp[i] += 'a' - 'A';
		}
	}

	for (int i = 0; i < len; i++) {
		word[start + i] = temp[i];
	}

	delete[] temp;

	return word;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " <input_file> " << "<output_file>"
			 << endl;
		return -1;
	}

	ifstream inputFile(argv[1]);

	if (inputFile.fail()) {
		cerr << "Impossibile aprire il file di input" << endl;
		return -1;
	}

	ofstream outputFile(argv[2]);

	if (outputFile.fail()) {
		cerr << "Impossibile aprire il file di output" << endl;
		return -1;
	}

	int shift;

	std::cout << "Shift: ";
	std::cin >> shift;

	char word[MAX_WORD_SIZE];

	while (inputFile >> word) {
		int startBodyIndex{-1};
		int endBodyIndex{-1};

		for (int i = 0; word[i] != '\0' && endBodyIndex < 0; i++) {
			if (is_letter(word[i]) && startBodyIndex == -1) {
				startBodyIndex = i;
			}

			else if (!is_letter(word[i]) && !is_letter(word[i + 1])) {
				endBodyIndex = i - 1;
			}

			else if (word[i + 1] == '\0' && endBodyIndex == -1) {
				endBodyIndex = i;
			}
		}

		outputFile << shift_word(word, shift, startBodyIndex, endBodyIndex)
				   << " ";
	}

	outputFile << endl;

	inputFile.close();
	outputFile.close();
}
