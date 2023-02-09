#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>
#include "mintf.h"

int main(int argc, char* argv[]) {
	
	// Test 00: empty test
	// Expect: ""
	
	// Test 01: empty string
	mintf("");
	fputc('\n', stdout);
	// Expect: ""
	
	// Test 02: test a single character
	mintf("a");
	fputc('\n', stdout);
	// Expect: ""
	
	// Test 03: test a string
	mintf("Test");	
	fputc('\n', stdout);
	// Expect: "Test"
	
	// Test 04: test with a format string
	mintf("%s with format.", "Test");
	fputc('\n', stdout);
	// Expect: "Test with format."
	
	// Test 05: test an integer format
	mintf("There are about %d students at Purdue!", 49000);
	fputc('\n', stdout);
	// Expect: "There are about 49000 students at Purdue!
	
	// Test 06: test a number converted to hex 
	mintf("Number in hex: %x.", 123);
	fputc('\n', stdout);
	// Expect: "Number in hex: 0x7b.
	
	// Test 07: convert a number to binary
	mintf("Number in binary: %b.", 123);
	fputc('\n', stdout);
	// Expect: Number in binary: 0b1111011.
	
	// Test 08: testing a character in ASCII format
	mintf("%c", 64);
	fputc('\n', stdout);
	// Expect: "@"
	
	// Test 09: convert to currency
	mintf("%$", 2000);
	fputc('\n', stdout);
	// Expect: "$20.00"
	
	// Test 10: test displaying a percent sign
	mintf("50%%");
	fputc('\n', stdout);
	// Expect: "50%"
	
	// Test 11: test a negative number with any prefix ($, 0b, 0x)
	mintf("%b", -123);
	fputc('\n', stdout);
	// Expect: "-0b111101"
	
	// Test 12: test a negative currency
	mintf("%$", -2025);
	fputc('\n', stdout);
	// Expect: "-$20.25"
	
	// Test 13: test a % with nothing after
	mintf("Test for % with nothing after 50%");
	fputc('\n', stdout);
	// Expect: "Test for % with nothin after 50%"
	
	// Test 14: passing multiple parameters with different formats
	mintf("Str: %s Intgr: %d%% Bin: %b Hex: %x Currency: %$ Char: %c", "Hi", 20, 123, 123, 100, 64);
	fputc('\n', stdout);
	// Expect: "Str: Hi Intgr: 20% Bin: 0b111101 Hex: 0x7b Currency: $1.00 Char: @"
	
	// Test 15: Passing an extra parameter
	mintf("Extra %s", "Hello", "Hello2");
	fputc('\n', stdout);
	// Expect: "Extra Hello"
	
	// Test 16: INT_MAX for currency
	mintf("INT_MAX %$", INT_MAX);
	fputc('\n', stdout);
	// Expect: "INT_MAX $21474836.47"
	
	// Test 17: INT_MIN for currency
	mintf("INT_MIN %$", INT_MIN);
	fputc('\n', stdout);
	// Expect: "INT_MIN -$21474836.48"
	
	// Test 18: INT_MIN for integer format
	mintf("%d", INT_MIN);
	fputc('\n', stdout);
	// Expect: "-2147483648"

	// Test 19: Test with the \n
	mintf("Hello New Line!\n");
	// Expect: "Hello New Line!"
	
	// Test 20: Test with % with no format
	mintf("Hello 50%word.");
	fputc('\n', stdout);
	// Expect: "Hello 50%word."
	
	// Test 21: Test %c with wrong value
	mintf("Hello %c.", 128);
	fputc('\n', stdout);
	// Expect: "Hello %c."
	
	// Test 22: %% with a format
	mintf("Does this work? %%d");
	fputc('\n', stdout);
	// Expect: "Does this work? %s"
	
	// Test 23: Extra tests for %$
	mintf("Extra 1: %$", -25);
	fputc('\n', stdout);
	// Expect: "Extra 1: -$0.25"
	
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
