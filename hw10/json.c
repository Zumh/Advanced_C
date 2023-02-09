#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include "clog.h"
#include "json.h"

bool parse_int(int* a_value, char const** a_pos) {
	
	char value = **a_pos;
	bool found_int = false; 
	int power = 0; // to determine if its multiple digits
	bool is_negative = false;

	if(value == '-') {
		*a_pos += 1;
		is_negative = true;
	}

	if(isdigit(**a_pos)) {
		found_int = true;
		*a_value = 0;
	}

	while(isdigit(**a_pos)) {
		value = **a_pos;
		*a_pos += 1;
		if(power > 0) {
			*a_value *= 10;
		}
		*a_value += value - '0';
		value = **a_pos;
		power = 1;
	}

	if(is_negative == true) {
		*a_value *= -1;
	}

	return found_int;
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
