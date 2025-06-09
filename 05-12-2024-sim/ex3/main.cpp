#include <iostream>
#include "pila.h"

using namespace std;

/**
 * Ricordare che il file "pila.h" contiene la definizione della struct "cella"
 * (qui sotto riportata)
 *
 * struct cella {
 *   int indiceRiga;
 *   int indiceColonna;
 * };
 */
void risolviLabirinto(int[][5], int, int);

int main(int argc, char* argv[]) {
	// Se modificate la funzione "main", ricordarsi poi di ripristinare il
	// codice originale

	// E' possibile modificare la matrice per effettuare dei test
	int labirinto[5][5] = {{1, 0, 1, 1, 0},
						   {1, 1, 1, 0, 1},
						   {0, 1, 0, 1, 1},
						   {1, 1, 1, 1, 1},
						   {1, 1, 1, 1, 1}};

	// E' possibile modificare la cella di arrivo per effettuare dei test (la
	// cella di partenza invece è sempre [0,0])
	cout << "Percorso: ";
	risolviLabirinto(labirinto, 4, 2);

	return 0;
}

void getOptions(cella options[4],
				int& count,
				int m[][5],
				bool visited[][5],
				int row,
				int col) {
	count = 0;

	const int left = col - 1;
	const int right = col + 1;
	const int up = row - 1;
	const int down = row + 1;

	if (left >= 0 && m[row][left] && !visited[row][left]) {
		options[count++] = {row, left};
	}

	if (right < 5 && m[row][right] && !visited[row][right]) {
		options[count++] = {row, right};
	}

	if (up >= 0 && m[up][col] && !visited[up][col]) {
		options[count++] = {up, col};
	}

	if (down < 5 && m[down][col] && !visited[down][col]) {
		options[count++] = {down, col};
	}
}

bool risolviLabirintoHelper(int m[][5],
							bool visited[5][5],
							cella curr,
							cella target) {
	const int row = curr.indiceRiga;
	const int col = curr.indiceColonna;

	visited[row][col] = true;

	push(curr);

	if (target.indiceRiga == row && target.indiceColonna == col) {
		return true;
	}

	cella options[4];
	int nOpts;
	getOptions(options, nOpts, m, visited, row, col);

	for (int i = 0; i < nOpts; i++) {
		const cella& next = options[i];

		if (risolviLabirintoHelper(m, visited, options[i], target)) {
			return true;
		}
	}

	pop();
	return false;
}

void risolviLabirinto(int m[][5], int x, int y) {
	cout << endl;

	bool visited[5][5]{false};

	init();

	risolviLabirintoHelper(m, visited, {0, 0}, {x, y});

	while (!vuota()) {
		cella c;
		top(c);

		cout << "[" << c.indiceRiga << "," << c.indiceColonna << "]";

		pop();
	}

	cout << endl;
}
