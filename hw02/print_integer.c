#include "print_integer.h"
#include <stdio.h>
#include <stdbool.h>

void print_integer(int n, int radix, char* prefix) {
	
	unsigned int nc; // copy of n
	int quotient = 0; // quotient of number
	int times = 0; // number of times needed to divide
	int remainder; // remainder of number

	// Printing a negative sign if the value is negative
	if(n < 0) {
		// Checking if input is INT_MIN
		if(n != -2147483648) {
			n *= -1;
			nc = n;
		}
		else {
			nc = n;
		}
		fputc('-', stdout);
	}

	// Setting copy of n
	nc = n;

	// Code snippet from Q22 in HW 02 to print out a prefix
	char* s = prefix;
	for(int idx_in_s = 0; s[idx_in_s] != '\0'; idx_in_s++) {
	    fputc(s[idx_in_s], stdout);
	}

	// Converting into any other base
	if((radix >= 2) && (radix <= 36)) {
		quotient = nc / radix;
		while(quotient > 0) {
			quotient /= radix;
			times++;
		}
		while(times >= 0) {
			for(int j = 0; j < times; j++) {
				nc = nc / radix;
			}
			remainder = nc % radix;
			if(remainder >= 10) {
				fputc('a' + (remainder - 10), stdout);
			}
			else {
				fputc('0' + remainder, stdout);
			}
			times--;
			nc = n;
		}
	}
}
