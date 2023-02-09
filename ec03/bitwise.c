#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdint.h>
#include "print_bits.h"
#include "bitwise.h"

/******************************************************************************************\
 * Instructions:
 *
 * Fill in each function, according to the description following the restrictions below.
 *
 * To compile this file use this command:
 * gcc -o warmup warmup.c print_bits.o
 *
 * RESTRICTIONS:
 * ∙ The body of every function must be exactly one statement, except for print_bits(…)
 *   which must be exactly 3 statements.
 * ∙ Do not use the constant 0xff in create_string_of_eight_1s().  Other functions are fine.
 *   In fact, you *should* use it in other functions.
 *
 * The comments in this file write numbers in bits like this:  11111111₂ or 10111010₂.
 *
 * C11 does not actually accept constants like that. When writing code that uses bit
 * manipulations, always write constants in hexadecimal notation (e.g., 0xff for 11111111₂,
 * 0xBA for 10111010₂), except zero, which you can write as either 0 or 0x00 (your choice).
 *
 * Note:  The last file ends with ".o" not ".c".  It is a compiled "object file".  We are
 * giving you code you can use to diagnose the correctness of your other code, while also
 * asking you to implement the print_bits(…)  function.
 * 
 * The two functions provided by print_bits.o are described in print_bits.h.
 *
 * You may add anything you like to the main(…) function.  If you do not want to use
 * the functions in print_bits.o, you may remove the #include "print_bits.h".
\******************************************************************************************/

uint8_t create_string_of_eight_1s() {
	return (~0x00);  
}

uint8_t create_string_of_0s_at_left(uint8_t num_0s) {
	return (0xff >> num_0s);
}

uint8_t create_string_of_0s_at_right(uint8_t num_0s) {
	return (0xff << num_0s);
}

uint8_t create_string_of_1s_at_left(uint8_t num_1s) {
	return (0xff << (8 - num_1s)); 
}

uint8_t create_string_of_1s_at_right(uint8_t num_1s) {
	return (0xff >> (8 - num_1s)); 
}

uint8_t set_left_bits(uint8_t byte, uint8_t num_bits_to_set) {
	return (byte | (0xff << (8 - num_bits_to_set)));  
}

uint8_t set_right_bits(uint8_t byte, uint8_t num_bits_to_set) {
	return (byte | (0xff >> (8 - num_bits_to_set)));
}

uint8_t unset_left_bits(uint8_t byte, uint8_t num_bits_to_unset) {
	return (byte & (0xff >> num_bits_to_unset));   
}

uint8_t unset_right_bits(uint8_t byte, uint8_t num_bits_to_unset) {
	return (byte & (0xff << num_bits_to_unset)); 
}

uint8_t toggle_left_bits(uint8_t byte, uint8_t num_bits_to_toggle) {
	return (byte ^ (0xff << (8 - num_bits_to_toggle)));
}

uint8_t toggle_right_bits(uint8_t byte, uint8_t num_bits_to_toggle) {
	return (byte ^ (0xff >> (8 - num_bits_to_toggle)));
}

void print_bits(uint8_t bits) {
	for(int i = 0; i < 8; i++) {
		fputc('0' + (bits % 2 ? 0 : 1), stdout);
		bits /= 2;
	}
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
