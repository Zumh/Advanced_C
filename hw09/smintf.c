#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include "smintf.h"

// Helper function headers
int _total_num_in_convert_format(int n, int radix, char* prefix); 
void _fill_string_completely(const char* format, va_list args, char* output);
int _total_characters_in_string(const char* format, va_list args);
int _convert_base_in_string(int n, int radix, char* prefix, char* output, int num); 

char* smintf(const char *format, ...) {
	
	// Declare list of arguments and start them
	va_list args, count_args, string_args;
	va_start(args, format);

	// Copy the arguments
	va_copy(count_args, args);
	va_copy(string_args, args);

	// Find the total number of characters
	int num_of_chars = _total_characters_in_string(format, count_args);

	// Allocate memory for the string
	char* output_str = malloc((num_of_chars) * sizeof(*output_str));

	// Fill up the string
	_fill_string_completely(format, string_args, output_str);

	// End the arguments
	va_end(args);
	va_end(count_args);
	va_end(string_args);

	return output_str;
}

void _fill_string_completely(const char* format, va_list args, char* output) {

	int num_char = 0; // total number of char in string

	for(int idx_in_str = 0; format[idx_in_str] != '\0'; idx_in_str++) {
		if(format[idx_in_str] == '%') {
			// Increase index by one to see what comes after %
			if(format[idx_in_str + 1] != '\0') {
				idx_in_str++;
			}

			// Checking for different arguments
			if(format[idx_in_str] == 's') {
				char* str = va_arg(args, char*);
				for(int idx_in_arg = 0; str[idx_in_arg] != '\0'; idx_in_arg++) {
					output[num_char] = str[idx_in_arg];
					num_char++;
				}
			}
			else if(format[idx_in_str] == 'c') {
				int value = va_arg(args, int); // value of char in ASCII
				
				if((value >= 32) && (value <= 127)) {
					output[num_char] = value;
					num_char++;
				}
				else {
					output[num_char] = '%';
					num_char++;
					output[num_char] = 'c';
					num_char++;
				}
			}
			else if(format[idx_in_str] == '%') {
				output[num_char] = '%';
				num_char++;
			}
			else if(format[idx_in_str] == 'd') {
				num_char = _convert_base_in_string(va_arg(args, int), 10, "", output, num_char);
			}
			else if(format[idx_in_str] == 'x') {
				num_char = _convert_base_in_string(va_arg(args, int), 16, "0x", output, num_char);
			}
			else if(format[idx_in_str] == 'b') {
				num_char = _convert_base_in_string(va_arg(args, int), 2, "0b", output, num_char);
			}
			else if(format[idx_in_str] == '$') {
				int number = va_arg(args, int);
				
				if(((number / 100) == 0) && (number < 0)) {
					output[num_char] = '-';
					num_char++;
				}

				num_char = _convert_base_in_string(number / 100, 10, "$", output, num_char);
				output[num_char] = '.';
				num_char++;
				
				if(number == -2147483648) {
					unsigned int n_copy = number;
					int cents = ((n_copy / 10) % 10);
					output[num_char] = ('0' + cents);
					num_char++;
					cents = n_copy % 10;
					output[num_char] = ('0' + cents);
					num_char++;
				}
				else {
					if(number < 0) {
						number *= -1;
					}
					int cents = ((number / 10) % 10);
					output[num_char] = ('0' + cents);
					num_char++;
					cents = number % 10;
					output[num_char] = ('0' + cents);
					num_char++;
				}
			}
			else {
				output[num_char] = '%';
				num_char++;
				output[num_char] = format[idx_in_str];
				num_char++;
			}
		}
		else {
			output[num_char] = format[idx_in_str];
			num_char++;
		}
	}
	output[num_char] = '\0';
}

int _total_characters_in_string(const char* format, va_list args) {
	
	int num_char = 0; // number of characters

	for(int idx_in_str = 0; format[idx_in_str] != '\0'; idx_in_str++) {
		if(format[idx_in_str] == '%') {
			// Increase index by one to see what comes after %
			if(format[idx_in_str + 1] != '\0') {
				idx_in_str++;
			}
			// Checking for different types of arguments
			if(format[idx_in_str] == 's') {
				char* str = va_arg(args, char*);
				for(int idx_in_arg = 0; str[idx_in_arg] != '\0'; idx_in_arg++) {
					num_char++;
				}
			}
			else if(format[idx_in_str] == 'd') {
				int num_dig = _total_num_in_convert_format(va_arg(args, int), 10, "");
				num_char += num_dig;
			}
			else if(format[idx_in_str] == 'c') {
				int value = va_arg(args, int); // ASCII value

				if((value >= 32) && (value <= 127)) {
					num_char++;	
				}
				else {
					num_char += 2;
				}
			}
			else if(format[idx_in_str] == '%') {
				num_char++;
			}
			else if(format[idx_in_str] == 'x') {
				int num_dig = _total_num_in_convert_format(va_arg(args, int), 16, "0x");
				num_char += num_dig;
			}
			else if(format[idx_in_str] == 'b') {
				int num_dig = _total_num_in_convert_format(va_arg(args, int), 2, "0b");
				num_char += num_dig;
			}
			else if(format[idx_in_str] == '$') {
				int number = va_arg(args, int);

				if(((number / 100) == 0) && (number < 0)) {
					num_char++;
				}
				int num_dig = _total_num_in_convert_format(number / 100, 10, "$");
				num_char += num_dig;

				num_char += 3; // There will always be cents
			}
			else {
				num_char += 2;
			}
		}
		else {
			num_char++;
		}
	}
	// Account for null character
	num_char++;

	return num_char;
}

int _convert_base_in_string(int n, int radix, char* prefix, char* output, int num) {
	
	unsigned int n_copy = 0; // copy of n
	int times = 0; // number of times needed to divide

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
		output[num] = '-';
		num++;
	}

	n_copy = n;

	// Code snippet from Q22 in HW 02 to print out a prefix
	char* s = prefix;
	for(int idx_in_s = 0; s[idx_in_s] != '\0'; idx_in_s++) {
		output[num] = s[idx_in_s];
		num++;
	}

	// Converting into any other base
	if((radix >= 2) && (radix <= 36)) {
		int quotient = n_copy / radix;
		while(quotient > 0) {
			quotient /= radix;
			times++;
		}
		while(times >= 0) {
			for(int j = 0; j < times; j++) {
				n_copy = n_copy / radix;
			}
			int remainder = n_copy % radix;
			if(remainder >= 10) {
				output[num] = ('a' + (remainder - 10));
				num++;
			}
			else {
				output[num] = ('0' + remainder);
				num++;
			}
			times--;
			n_copy = n;
		}
	}
	return num;
}

int _total_num_in_convert_format(int n, int radix, char* prefix) {
	
	unsigned int n_copy = 0; // copy of n
	int times = 0; // number of times needed to divide
	int number = 0; // number of digits and characters

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
		number++;
	}

	n_copy = n; // Setting copy of n

	// Code snippet from Q22 in HW 02 to print out a prefix
	char* s = prefix;
	for(int idx_in_s = 0; s[idx_in_s] != '\0'; idx_in_s++) {
		number++;
	}

	// Converting into any other base
	if((radix >= 2) && (radix <= 36)) {
		int quotient = n_copy / radix;
		while(quotient > 0) {
			quotient /= radix;
			times++;
		}
		while(times >= 0) {
			for(int j = 0; j < times; j++) {
				n_copy = n_copy / radix;
			}
			int remainder = n_copy % radix;
			if(remainder >= 10) {
				number++;
			}
			else {
				number++;
			}
			times--;
			n_copy = n;
		}
	}
	return number;
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
