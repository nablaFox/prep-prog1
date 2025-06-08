#include <iostream>
#include <fstream>

using namespace std;

constexpr int MAX_WORD_SIZE = 100;

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

	char word[MAX_WORD_SIZE];

	while (inputFile >> word) {
		int i = 0;
		int iCount = 0;
		char lastLetter;

		bool thirdRule = true;
		const bool firstRule = word[0] == 'M' && lastLetter == 'U';
		const bool secondRule = iCount == 0 || iCount % 2 == 1;

		while (word[i] != '\0') {
			iCount += word[i] == 'I';

			if (word[i] == 'I' && word[i + 1] == 'M') {
				thirdRule = false;
			}

			if (word[i + 1] == '\0') {
				lastLetter = word[i];
			}

			i++;
		}

		if (!firstRule || !secondRule || !thirdRule) {
			continue;
		}

		outputFile << word << endl;
	}

	return 0;
}
