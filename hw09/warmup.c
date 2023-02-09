 /* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
#include <stdio.h>
#include <stdlib.h>

char* my_strdup(const char* original) {
	
	int num_char = 0; // number of characters needed

	while(original[num_char] != '\0') {
		num_char++;
	}

	// Allocating memory for a copy of the string
	char* copy_str = malloc((num_char + 1) * sizeof(*copy_str));

	for(int idx_in_str = 0; original[idx_in_str] != '\0'; idx_in_str++) {
		copy_str[idx_in_str] = original[idx_in_str];
	}

	// Adding the null terminator
	copy_str[num_char] = '\0';

	return copy_str;
}

int main(int argc, char *argv[]) {
	char s[] = "abc\n";
	fputs(s, stdout);  // Should print "abc" followed by a newline ('\n')

	char* t = my_strdup(s);
	fputs(t, stdout);  // Should print "abc" followed by a newline ('\n')
	free(t);

	return EXIT_SUCCESS;
}
