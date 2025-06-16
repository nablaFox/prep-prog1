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

	// exercise body
	// ...
	// exercise body

	inputFile.close();
	outputFile.close();
}
