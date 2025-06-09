#include <iostream>

/* Inserire qui sotto la dichiarazione della funzione extract */

char* extract(const char* str, int curr = 0, int len = 0);

/* Inserire qui sopra la dichiarazione della funzione extract */

/* Solo di esempio, non fate assunzioni su questo valore */
const int DIM = 255;

int main(int argc, char** argv) {
	char input_string[DIM + 1];
	char* extracted;
	char answer;

	do {
		std::cout << "Inserire la stringa da controllare: ";
		std::cin >> input_string;

		extracted = extract(input_string);
		std::cout << "La stringa estratta e': " << extracted << std::endl;

		delete[] extracted;
		std::cout << "Si vuole inserire un'altra stringa? [*/n]";
		std::cin >> answer;
	} while (answer != '\0' && answer != 'N' && answer != 'n');
	return 0;
}

/* Inserire qui sotto la definizione della funzione estract */

char* extract(const char* input, int curr, int len) {
	char* output;

	if (input[curr] == '\0') {
		output = new char[len + 1];
		output[len] = '\0';
	} else if (input[curr] == '@') {
		output = extract(input, curr + 1, len + 1);
		output[len] = '@';
	} else {
		output = extract(input, curr + 1, len);
	}

	return output;
}

/* Inserire qui sopra la definizione della funzione estract */
