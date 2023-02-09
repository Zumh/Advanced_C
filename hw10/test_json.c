#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include "miniunit.h"
#include "json.h"

static int _test_parse_int_zero() {
	mu_start();
	//----------------------------------
	int   result; // will be initialized in parse_int(...)
	char* input = "0";
	char const* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(is_success); // because the input is valid
	mu_check(pos == input + 1);
	mu_check(result == 0);
	//----------------------------------
	mu_end();
}

static int _test_parse_int_invalid() {
	mu_start();
	//----------------------------------
	// Letter
	int   result; // will be initialized in parse_int(...)
	char* input = "A";
	char const* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(!is_success);
	mu_check(pos == input);

	// Invalid negative
	input = "-";
	pos = input;
	is_success = parse_int(&result, &pos);
	mu_check(!is_success);
	mu_check(pos == input + 1);

	// Double negative
	input = "--1";
	pos = input;
	is_success = parse_int(&result, &pos);
	mu_check(!is_success);
	mu_check(pos == input + 1);

	// Negative with letter
	input = "-ABCD";
	pos = input;
	is_success = parse_int(&result, &pos);
	mu_check(!is_success);
	mu_check(pos == input + 1);
	//----------------------------------
	mu_end();
}

static int _test_parse_int_valid() {
	mu_start();
	//----------------------------------
	// One digit
	int   result; // will be initialized in parse_int(...)
	char* input = "9";
	char const* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(is_success); // because the input is valid
	mu_check(pos == input + 1);
	mu_check(result == 9);

	// Double digit
	input = "15";
	pos = input;
	is_success = parse_int(&result, &pos);
	mu_check(is_success); // because the input is valid
	mu_check(pos == input + 2);
	mu_check(result == 15);

	// Digits with letters
	input = "123ABC";
	pos = input;
	is_success = parse_int(&result, &pos);
	mu_check(is_success); // because the input is valid
	mu_check(pos == input + 3);
	mu_check(result == 123);

	// Negative with letters
	input = "-123-BC";
	pos = input;
	is_success = parse_int(&result, &pos);
	mu_check(is_success); // because the input is valid
	mu_check(pos == input + 4);
	mu_check(result == -123);

	// More tests
	input = "-99A";
	pos = input;
	is_success = parse_int(&result, &pos);
	mu_check(is_success); // because the input is valid
	mu_check(pos == input + 3);
	mu_check(result == -99);
	//----------------------------------
	mu_end();
}

int main(int argc, char* argv[]) {
	
	mu_run(_test_parse_int_zero);
	mu_run(_test_parse_int_invalid);
	mu_run(_test_parse_int_valid);

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
