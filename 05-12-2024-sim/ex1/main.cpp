#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

constexpr int MAX_STRING_LENGTH = 101;

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " <file> " << "<corrected_file>"
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

	char buffer[MAX_STRING_LENGTH];

	inputFile >> buffer;

	if (!(buffer[0] >= 'A' && buffer[0] <= 'Z')) {
		buffer[0] += 'A' - 'a';
	}

	while (!inputFile.eof()) {
		outputFile << buffer << " ";

		const char prev = buffer[strlen(buffer) - 1];

		inputFile >> buffer;

		if (prev == '.' || prev == '?' || prev == '!') {
			if (!(buffer[0] >= 'A' && buffer[0] <= 'Z')) {
				buffer[0] += 'A' - 'a';
			}
		}
	}

	outputFile << endl;

	outputFile.close();
	inputFile.close();

	return 0;
}
