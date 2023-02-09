#include <stdlib.h>
#include "mintf.h"

int main(int argc, char* argv[]) {

	// Test 00: empty test
	// Expect: ""

	// Test 01: empty string
	mintf("");
	// Expect: ""
	
	// Test 02: test a single character
	mintf("a");
	// Expect: "a"
	
	// Test 03: test a string
	mintf("Test");
	// Expect: "Test"
	
	// Test 04: test a format string
	mintf("%s with format.", "Test");
	// Expect: "Test with format."

	// Test 05: test an integer format
	mintf("There are about %d students at Purdue!", 49000);
	// Expect: "There are about 49000 students at Purdue!
	
	// Test 06: test a number converted to hex 
	mintf("Number in hex: %x.", 123);
	// Expect: "Number in hex: 0x7b.
	
	// Test 07: convert a number to binary
	mintf("%b", 123);
	// Expect: 0b1111011
	
	// Test 08: convert to currency
	mintf("%$", 20000);
	// Expect: "$200.00"

	// Test 09: testing a character in ASCII format
	mintf("%c", 64);
	// Expect: "@"
	
	// Test 10: test displaying a percent sign
	mintf("50%%");
	// Expect: "50%"
	
	// Test 11: test a negative number with any prefix ($, 0b, 0x)
	mintf("%b", -123);
	// Expect: "-0b111101"
	
	// Test 12: passing multiple parameters with different formats
	mintf("Str: %s Intgr: %d%% Bin: %b Hex: %x Currency: %$ Char: %c", "Hi", 20, 123, 123, 100, 64);
	// Expect: "Str: Hi Intgr: 20% Bin: 0b111101 Hex: 0x7b Currency: $1.00 Char: @"

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
