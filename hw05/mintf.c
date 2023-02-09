#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "mintf.h"

void mintf(const char *format, ...) {

	// Declare list of arguments and start them
	va_list args;
	va_start(args, format);

	for(int idx_in_str = 0; format[idx_in_str]  != '\0'; idx_in_str++) {
		if(format[idx_in_str] == '%') {
			// Increase index by one to see what comes after %
			if(format[idx_in_str + 1] != '\0') {
				idx_in_str++;
			}

			// Checking for different types of arguments
			if(format[idx_in_str] == 's') {
				char* str = va_arg(args, char*);
				for(int idx_in_arg = 0; str[idx_in_arg] != '\0'; idx_in_arg++) {
					fputc(str[idx_in_arg], stdout);
				}
			}
			// If format is in integer
			else if(format[idx_in_str] == 'd') {
				print_integer(va_arg(args, int), 10, "");
			}
			// If format is in hex
			else if(format[idx_in_str] == 'x') {
				print_integer(va_arg(args, int), 16, "0x");
			}
			// If format is in binary
			else if(format[idx_in_str] == 'b') {
				print_integer(va_arg(args, int), 2, "0b");
			}
			// If format is in character
			else if(format[idx_in_str] == 'c') {
				int value = va_arg(args, int); // value of the character in ASCII

				if((value >= 32) && (value <= 127)) {
					fputc(0 + value, stdout);
				}
				else {
					fputc('%', stdout);
					fputc('c', stdout);
				}
			}
			// If format is %
			else if(format[idx_in_str] == '%') {
				fputc('%', stdout);
			}
			// If format is $
			else if(format[idx_in_str] == '$') {
				int cents = 0; // number of the cents
				int number = va_arg(args, int); // value of the currency
				
				// Check if currency is negative but print_integer won't catch it
				if(((number / 100) == 0) && (number < 0)) {
					fputc('-', stdout);
				}

				print_integer(number / 100, 10, "$");

				// Calculating value of cents
				cents += ((number / 10) % 10) * 10;
				cents += number % 10;

				fputc('.', stdout);
				// Check if cents is a negative value
				if(cents < 0) {
					cents *= -1;
				}
				// Types of cent values to display
				if(cents == 0) {
					fputc('0', stdout);
					fputc('0', stdout);
				}
				else if(cents < 10){
					fputc('0', stdout);
					print_integer(cents, 10, "");
				}
				else {
					print_integer(cents, 10, "");
				}
			}
			else {
				fputc('%', stdout);
				fputc(format[idx_in_str], stdout);
			}
		}
		else {
			fputc(format[idx_in_str], stdout);
		}
	}
	// End the arguments
	va_end(args);
}

void print_integer(int n, int radix, char* prefix) {
	
	unsigned int n_copy; // copy of n
	int quotient; // quotient of number
	int times = 0; // number of times needed to divide
	int remainder; // remainder of number

	// Printing a negative sign if the value is negative
	if(n < 0) {
		// Checking if input is INT_MIN
		if(n != -2147483648) {
			n *= -1;
			n_copy = n;
		}
		else {
			n_copy = n;
		}
		fputc('-', stdout);
	}

	// Setting copy of n
	n_copy = n;

	// Code snippet from Q22 in HW 02 to print out a prefix
	char* s = prefix;
	for(int idx_in_s = 0; s[idx_in_s] != '\0'; idx_in_s++) {
	    fputc(s[idx_in_s], stdout);
	}

	// Converting into any other base
	if((radix >= 2) && (radix <= 36)) {
		quotient = n_copy / radix;
		while(quotient > 0) {
			quotient /= radix;
			times++;
		}
		while(times >= 0) {
			for(int j = 0; j < times; j++) {
				n_copy = n_copy / radix;
			}
			remainder = n_copy % radix;
			if(remainder >= 10) {
				fputc('a' + (remainder - 10), stdout);
			}
			else {
				fputc('0' + remainder, stdout);
			}
			times--;
			n_copy = n;
		}
	}
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
