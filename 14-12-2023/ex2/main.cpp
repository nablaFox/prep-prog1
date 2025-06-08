#include <iostream>
#include <cstdlib>

using namespace std;

// Scrivere qui sotto la dichiarazione e definizione della funzione "funzione"

int funzione(int n, int prev = 0);

// Scrivere qui sopra la dichiarazione e definizione della funzione "funzione"

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " <positivenum> " << std::endl;
		exit(1);
	}
	int n = atoi(argv[1]);
	std::cout << "The read string is: " << argv[1] << std::endl;
	std::cout << "The converted value is: " << n << std::endl;
	std::cout << "function(" << n << ") = " << funzione(n) << std::endl;
}

int funzione(int n, int prev) {
	if (n < 1)
		return 0;

	const int curr = n % 10;

	return (prev == curr) + funzione(n / 10, curr);
}
