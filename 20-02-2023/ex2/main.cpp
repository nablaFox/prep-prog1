#include <iostream>
#include <cstdlib>
#include <ctime>

#define MAXVALUE 100
#define MAXSIZE 100

// NON MODIFICARE IL CODICE SOTTO FINO A "NON MODIFICARE IL CODICE SOPRA"
struct list {
	int info;
	list* next;
};

struct tree {
	int info;
	tree* left;
	tree* right;
};

void insert(tree*& result, const int num) {
	if (result == NULL) {
		result = new tree;
		*result = {num, NULL, NULL};
	} else if (result->info > num) {
		insert(result->left, num);
	} else {
		insert(result->right, num);
	}
}

tree* crea_tree(const int num) {
	tree* result = NULL;
	for (int i = 0; i < num; i++) {
		insert(result, rand() % MAXVALUE);
	}
	return result;
}

void print_tree(const tree* root) {
	if (root != NULL) {
		print_tree(root->right);
		std::cout << " " << root->info;
		print_tree(root->left);
	}
}

void delete_tree(tree*& root) {
	if (root != NULL) {
		delete_tree(root->left);
		delete_tree(root->right);
		delete root;
		root = NULL;
	}
}

void print_array(const int l[], const int l_size) {
	for (int i = 0; i < l_size; i++)
		std::cout << " " << l[i];
	std::cout << std::endl;
}

// NON MODIFICARE IL CODICE SOPRA

// Add hereafter the declaration of estrai

void estrai(const tree*, int*& l1, int& l1_size, int*& l2, int& l2_size);

// Add here above the declaration of estrai

// NON MODIFICARE IL MAIN
int main(int argc, char** argv) {
	srand(unsigned(time(0)));
	//
	// Commentare la linea seguente per avere comportamento
	// non-deterministico
	//
	srand(0);
	tree* root = crea_tree(rand() % MAXSIZE);
	std::cout << "Initial tree content: ";
	print_tree(root);
	std::cout << std::endl;
	int* l1;
	int l1_size;
	int* l2;
	int l2_size;
	estrai(root, l1, l1_size, l2, l2_size);
	delete_tree(root);
	std::cout << "L1 =";
	print_array(l1, l1_size);
	std::cout << "L2 =";
	print_array(l2, l2_size);
	delete[] l1;
	delete[] l2;
}
// NON MODIFICARE IL MAIN

// Add hereafter the definition of estrai

void get_sizes(const tree* tree, int& even_size, int& odd_size) {
	if (tree == nullptr)
		return;

	even_size += (tree->info % 2 == 0);
	odd_size += (tree->info % 2 != 0);

	get_sizes(tree->right, even_size, odd_size);
	get_sizes(tree->left, even_size, odd_size);
}

void estrai_helper(const tree* tree,
				   int*& l1,
				   int*& l2,
				   int& even_index,
				   int& odd_index) {
	if (tree == nullptr)
		return;

	estrai_helper(tree->left, l1, l2, even_index, odd_index);

	if (tree->info % 2 == 0) {
		l1[even_index++] = tree->info;
	} else {
		l2[odd_index++] = tree->info;
	}

	estrai_helper(tree->right, l1, l2, even_index, odd_index);
}

void estrai(const tree* tree, int*& l1, int& l1_size, int*& l2, int& l2_size) {
	l1_size = 0;
	l2_size = 0;

	get_sizes(tree, l1_size, l2_size);

	if (l1_size) {
		l1 = new int[l1_size];
	}

	if (l2_size) {
		l2 = new int[l2_size];
	}

	l2 = l2_size ? new int[l2_size] : nullptr;

	int even_index{0}, odd_index{0};

	estrai_helper(tree, l1, l2, even_index, odd_index);
}

// Add here above the definition of estrai
