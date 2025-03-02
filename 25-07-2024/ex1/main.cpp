#include <fstream>
#include <iostream>
#include <cstdlib>

constexpr int MAX_CHARACTERS = 5000;

int ContaParole(char* pText[]) {
	int numWords{0};

	for (; numWords < MAX_CHARACTERS && pText[numWords] != nullptr; numWords++)
		;

	return numWords;
}

void GeneraParole(char* pText[], int wordCount, char* pGeneratedWord) {
	for (int i{0}; i < 6; i++) {
		const int randomIndex = rand() % wordCount;
		pGeneratedWord[i] = *(pText[randomIndex]);
	}

	pGeneratedWord[7] = '\0';
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
		return 1;
	}

	std::ifstream inputFile(argv[1], std::ios::in);

	if (inputFile.fail()) {
		std::cerr << "Cannot open the input file \"" << argv[1] << "\"" << std::endl;
		return 1;
	}

	char text[MAX_CHARACTERS]{0};
	char* pwords[MAX_CHARACTERS]{nullptr};

	int numWords{0};
	char currChar, prevChar = ' ';

	for (int i{0}; i < MAX_CHARACTERS && inputFile.get(currChar) && !inputFile.eof();
		 i++) {
		text[i] = currChar;

		if (prevChar == ' ' && ((currChar >= 'a' && currChar <= 'z') ||
								(currChar >= 'A' || currChar <= 'Z'))) {
			pwords[numWords++] = &text[i];
		}

		prevChar = currChar;
	}

	std::cout << "Text: " << text << std::endl;

	std::cout << "Number of words: " << numWords << std::endl;

	std::cout << "Initials: ";
	for (int i{0}; i < numWords; i++) {
		std::cout << *(pwords[i]);
	}
	std::cout << std::endl;

	char generatedWord[7]{0};
	GeneraParole(pwords, ContaParole(pwords), generatedWord);
	std::cout << "Generated word: " << generatedWord << std::endl;

	inputFile.close();

	return 0;
}
