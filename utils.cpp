bool is_letter(char c) {
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

char lowercase(char c) {
	return c + ('a' - 'A');
}

char uppercase(char c) {
	return c - ('a' - 'A');
}

// TODO: some sorting algorithms and recursive versions

// TODO: some lists methods
