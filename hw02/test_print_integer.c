#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>
#include "print_integer.h"

int main(int argc, char* argv[]) {

	// zero in base 10
	print_integer(0, 10, "");
	fputc('\n', stdout);

	// one digit in base 16
	print_integer(10, 16, "");
	fputc('\n', stdout);

	// double digit in base 10
	print_integer(42, 10, "");
	fputc('\n', stdout);

	// negative number in base 10
	print_integer(-9, 10, "");
	fputc('\n', stdout);

	// double digit with prefix in base 10
	print_integer(-9, 10, "hello");
	fputc('\n', stdout);
	
	// double digit in base 16
	print_integer(123, 16, "");
	fputc('\n', stdout);

	// single digit in base 2 with prefix
	print_integer(3, 2, "papaya");
	fputc('\n', stdout);

	// three digit in base 10
	print_integer(123, 10, "");
	fputc('\n', stdout);

	// greater than 3 digit in base 10
	print_integer(12345, 10, "");
	fputc('\n', stdout);
	
	// greater than 3 digit in base 10 with prefix
	print_integer(2345, 10, "word");
	fputc('\n', stdout);

	// greater than 3 digit in base with negative and prefix
	print_integer(-2342, 10, "tester");
	fputc('\n', stdout);

	// zero in base 16
	print_integer(0, 16, "");
	fputc('\n', stdout);

	// three digit in base 16
	print_integer(1235, 16, "");
	fputc('\n', stdout);

	// decimal to binary
	print_integer(123, 2, "");
	fputc('\n', stdout);

	// decimal to base 3
	print_integer(683, 3, "");
	fputc('\n', stdout);

	// decimal to base 4
	print_integer(683, 4, "");
	fputc('\n', stdout);

	// decimal to base 5
	print_integer(683, 5, "");
	fputc('\n', stdout);

	// decimal to base 6
	print_integer(683, 6, "");
	fputc('\n', stdout);

	// decimal to base 7
	print_integer(683, 7, "");
	fputc('\n', stdout);

	// decimal to base 8
	print_integer(683, 8, "");
	fputc('\n', stdout);

	// decimal to base 9
	print_integer(683, 9, "");
	fputc('\n', stdout);

	// decimal to base 25
	print_integer(683, 25, "");
	fputc('\n', stdout);

	// decimal to base 36
	print_integer(683, 36, "");
	fputc('\n', stdout);

	// edge cases
	// biggest and smallest possible integer
	print_integer(INT_MAX, 10, "");
	fputc('\n', stdout);
	print_integer(INT_MIN, 10, "");
	fputc('\n', stdout);

	// biggest and smallest possible integer with prefix
	print_integer(INT_MAX, 10, "hello");
	fputc('\n', stdout);
	print_integer(INT_MIN, 10, "hello");
	fputc('\n', stdout);

	// biggest and smallest possible radix with negative and non-negative
	print_integer(292, 2, "");
	fputc('\n', stdout);
	print_integer(-292, 2, "");
	fputc('\n', stdout);
	print_integer(292, 36, "");
	fputc('\n', stdout);
	print_integer(-292, 36, "");
	fputc('\n', stdout);

	// longest and smallest prefix
	print_integer(10, 16, "");
	fputc('\n', stdout);
	print_integer(10, 16, "hellohowareyoudoingtoday");
	fputc('\n', stdout);

	// corner cases
	// transition from positive to negative
	print_integer(1, 3, "");
	fputc('\n', stdout);
	print_integer(0, 3, "");	
	fputc('\n', stdout);
	print_integer(-1, 3, "");
	fputc('\n', stdout);

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
