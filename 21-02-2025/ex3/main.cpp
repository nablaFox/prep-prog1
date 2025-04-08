#include <iostream>
#include <fstream>
#include <cstdlib>

#include "stack.h"
#include "queue.h"

using namespace std;

// Insert here after the declarations of the functions check

bool check(ifstream&);

// Insert here above the declaration of the function check

int main(int argc, char** argv) {
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <input_file>" << endl;
		exit(1);
	}

	ifstream in(argv[1]);
	if (in.fail()) {
		cerr << "Cannot open input file " << argv[1] << endl;
		exit(2);
	}

	bool balanced = check(in);

	if (balanced) {
		cout << "The function check returns true" << endl;
	} else {
		cout << "The function check returns false" << endl;
	}

	in.close();

	return 0;
}

// Insert here after the definition of the functions check

bool check(ifstream& in) {
	Stack stack{init_stack()};

	char curr;
	while (in.get(curr)) {
		const bool isOpener = curr == '(' || curr == '[' || curr == '{';
		const bool isCloser = curr == ')' || curr == ']' || curr == '}';

		if (isOpener) {
			push(stack, curr);
		}

		if (isCloser && stack_is_empty(stack)) {
			return false;
		}

		else if (isCloser) {
			char top = pop(stack);

			if ((curr == ')' && top != '(') || (curr == ']' && top != '[') ||
				(curr == '}' && top != '{')) {
				return false;
			}
		}
	}

	bool res = stack_is_empty(stack);

	delete_stack(stack);

	return res;
}

// Insert here above the definition of the function check
