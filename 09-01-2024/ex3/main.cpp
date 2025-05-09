#include <cstring>
#include <iostream>
#include "lista.h"

using namespace std;

const int POS_AL_SECONDO = 2;
const int DIM_COLORI = 4;
const int MAX_BAMBINI = 10;

const char* nomi[18] = {
	"Marco",	"Luca",		"Anna",	   "Sabrina",	"Veronica", "Simone",
	"Mario",	"Luigi",	"Antonio", "Francesca", "Giovanni", "Letizia",
	"Lucrezia", "Carolina", "Luca",	   "Annalisa",	"Susanna",	"Licia"};
const color colori[DIM_COLORI] = {rosso, verde, blu, giallo};

// Inserire QUI sotto la dichirazione delle funzioni coloraPartecipante e cerca.

lista cerca(lista, const char* nome);

lista coloraPartecipante(lista, int k, int i);

// Inserire QUI sopra la dichirazione delle funzioni coloraPartecipante e cerca.

int main() {
	lista cerchio = NULL;

	unsigned int seed = time(NULL);
	// Commentare la riga sotto per non avere sempre lo stesso seed
	seed = 1703945587;
	std::cout << "Seed: " << seed << std::endl;
	srand(seed);

	int numero_bambini = rand() % MAX_BAMBINI + 2;
	for (int i = 0; i < numero_bambini; i++) {
		char* nome = (char*)nomi[rand() % 18];
		if (cerca(cerchio, nome) == NULL) {
			insert_in(cerchio, nome, 0);
		} else {
			i--;
		}
	}

	cout << "Ci sono " << size(cerchio) << " bambini nella lista." << endl;
	print(cerchio);

	int i = 0;
	int durata;
	bool finished = false;

	while (!empty(cerchio) && !finished) {
		cout << "-------------------------------------------------------------"
			 << endl;
		cout << "Giro numero " << ++i << endl;

		cout << "La canzone durerà per " << (durata = rand() % 60 + 10)
			 << " secondi." << endl;

		int sedia_rimossa = rand() % size(cerchio);
		cout << "Fermo il bambino alla sedia numero " << sedia_rimossa << "."
			 << endl;

		lista eliminato = coloraPartecipante(cerchio, durata, sedia_rimossa);

		if (eliminato != NULL) {
			cout << eliminato->nome << " ha ricevuto il colore "
				 << eliminato->colore << endl;
		} else {
			cout << "Tutti i bambini hanno un colore. Ho finito." << endl;
			finished = true;
		}
		print(cerchio);
	}

	cout << "-------------------------------------------------------------"
		 << endl;
	cout << "Tutti i bambini hanno un colore. Ho finito." << endl;

	return 0;
}

// Inserire QUI la definizione delle funzioni coloraPartecipante e cerca.

lista cerca(lista l, const char* nome) {
	lista curr = l;

	while (curr != NULL && curr->next != l) {
		if (strcmp(curr->nome, nome) == 0)
			return curr;

		curr = curr->next;
	}

	return NULL;
}

lista coloraPartecipante(lista l, int k, int i) {
	if (l == NULL) {
		return NULL;
	}

	lista curr = l;

	const int scroll = (k * POS_AL_SECONDO + i) % size(l);

	for (int j = 0; j < scroll - 1; j++) {
		curr = curr->next;
	}

	color colore = colori[rand() % DIM_COLORI];
	cout << "Colore: " << colore << endl;

	lista prev = curr;
	lista eliminated = curr->next;

	while (eliminated->colore != nero) {
		prev = eliminated;
		eliminated = eliminated->next;

		if (prev == curr) {
			return NULL;
		}
	}

	while (prev->colore == colore || eliminated->next->colore == colore) {
		colore = colori[rand() % DIM_COLORI];
	}

	eliminated->colore = colore;

	cout << "Scelto il colore " << colore << " per il partecipante "
		 << eliminated->nome << endl;

	return eliminated;
}
