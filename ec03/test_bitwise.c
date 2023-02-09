#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "print_bits.h"
#include "bitwise.h"

int main(int argc, char* argv[]) {
	printf("Print 10111010 to demonstrate color (m=magenta, y=yellow)\n");
	printf("expected: mmmyyyyy\nactual:   ");
	print_bits_color(0xba, 3, "magenta", "yellow");
	printf("\n");

	printf("create_string_of_eight_1s()\n");
	printf("expected: 11111111\nactual:   ");
	print_bits_plain(create_string_of_eight_1s());
	printf("\n");

	printf("create_string_of_1s_at_left(3)\n");
	printf("expected: 11100000\nactual:   ");
	print_bits_color(create_string_of_1s_at_left(3), 3, NULL, "green");
	printf("\n");

	printf("create_string_of_1s_at_right(3)\n");
	printf("expected: 00000111\nactual:   ");
	print_bits_color(create_string_of_1s_at_right(3), 5, NULL, "green");
	printf("\n");

	printf("set_left_bits(00000000₂, 2)\n");
	printf("expected: 11000000\nactual:   ");
	print_bits_color(set_left_bits(0x00, 2), 2, "green", NULL);
	printf("\n");

	printf("set_right_bits(00000000₂, 2)\n");
	printf("expected: 00000011\nactual:   ");
	print_bits_color(set_right_bits(0x00, 2), 6, NULL, "green");
	printf("\n");

	printf("unset_left_bits(11111111₂, 2)\n");
	printf("expected: 00111111\nactual:   ");
	print_bits_color(unset_left_bits(0xff, 2), 2, "green", NULL);
	printf("\n");

	printf("unset_right_bits(11111111₂, 2)\n");
	printf("expected: 11111100\nactual:   ");
	print_bits_color(unset_right_bits(0xff, 2), 6, NULL, "green");
	printf("\n");

	printf("toggle_left_bits(10101010₂, 4)\n");
	printf("expected: 01011010\nactual:   ");
	print_bits_color(toggle_left_bits(0xaa, 4), 4, "green", NULL); // 0xaa is 10101010₂
	printf("\n");

	printf("toggle_left_bits(11111111₂, 2)\n");
	printf("expected: 00111111\nactual:   ");
	print_bits_color(toggle_left_bits(0xff, 2), 4, "green", NULL); 
	
	printf("\n");

	printf("toggle_right_bits(10101010₂, 4)\n");
	printf("expected: 10100101\nactual:   ");
	print_bits_color(toggle_right_bits(0xaa, 4), 4, NULL, "green"); // 0xaa is 10101010₂
	printf("\n");

	printf("create_string_of_0s_at_left(1)\n");
	printf("expected: 01111111\nactual:   ");
	print_bits_plain(create_string_of_0s_at_left(1)); 
	
	printf("\n");

	printf("create_string_of_0s_at_right(2)\n");
	printf("expected: 11111110\nactual:   ");
	print_bits_plain(create_string_of_0s_at_right(1)); 
	
	printf("\n");

	printf("print_bits(0xaa)\n");
	printf("expected: 10101010\nactual:   ");
	print_bits(0xaa);

	return EXIT_SUCCESS;
}
#define __WARMUP_C_V2__
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
