#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <stdarg.h>
#include "smintf.h"
#include "miniunit.h"

int _test_empty() {
	mu_start();
	//----------------------------
	mu_check_smintf("", "");
	//----------------------------
	mu_end();
}

int _test_char() {
	mu_start();
	//----------------------------
	mu_check_smintf("a", "a");
	mu_check_smintf("b", "b");
 	mu_check_smintf("c", "c");	
	//----------------------------
	mu_end();
}

int _test_string() {
	mu_start();
	//----------------------------
	mu_check_smintf("Hello", "Hello");
	mu_check_smintf("World", "World");
	//----------------------------
	mu_end();
} 

int _test_number() {
	mu_start();
	//----------------------------
	mu_check_smintf("1", "1");
	mu_check_smintf("123", "123");
	//----------------------------
	mu_end();
}

int _test_format_string() {
	mu_start();
	//----------------------------
	mu_check_smintf("Hello", "%s", "Hello");
	mu_check_smintf("Hello Format", "%s", "Hello Format");
	mu_check_smintf("Hello World", "Hello %s", "World");
	//----------------------------
	mu_end();
}

int _test_format_char() {
	mu_start();
	//----------------------------
	mu_check_smintf("@", "%c", 64);
	mu_check_smintf("@", "%c", '@');
	mu_check_smintf("Follow me @hello", "Follow me %chello", '@');
	//----------------------------
	mu_end();
}

int _test_format_percent() {
	mu_start();
	//----------------------------
	mu_check_smintf("Testing the % sign.", "Testing the %% sign.");
	mu_check_smintf("More % tests.", "More %% tests.");
	//----------------------------
	mu_end();
}

int _test_format_not_valid() {
	mu_start();
	//----------------------------
	mu_check_smintf("%h", "%h");
	mu_check_smintf("Random %r", "Random %r");
	//----------------------------
	mu_end();
}

int _test_format_integer() {
	mu_start();
	//----------------------------
	mu_check_smintf("123", "%d", 123);
	mu_check_smintf("Testing Number 123", "Testing Number %d", 123);
	mu_check_smintf("Two Numbers 123 456", "Two Numbers %d %d", 123, 456);
	mu_check_smintf("Negative: -123", "Negative: %d", -123);
	//----------------------------
	mu_end();
}

int _test_format_hex() {
	mu_start();
	//----------------------------
	mu_check_smintf("0x7b", "%x", 123);
	mu_check_smintf("Format Hex: 0x237", "Format Hex: %x", 567);
	mu_check_smintf("More Hex: 0x58f", "More Hex: %x", 1423); 
	mu_check_smintf("-0x7b", "%x", -123);
	//----------------------------
	mu_end();
}

int _test_format_binary() {
	mu_start();
	//----------------------------
	mu_check_smintf("0b1111011", "%b", 123);
	mu_check_smintf("Format Binary: 0b1000110111", "Format Binary: %b", 567);
	mu_check_smintf("More Binary: 0b10110001111", "More Binary: %b", 1423); 
	mu_check_smintf("Negative -0b1111011", "Negative %b", -123);
	//----------------------------
	mu_end();
}

int _test_format_currency() {
	mu_start();
	//----------------------------
	mu_check_smintf("$3.00", "%$", 300);
	mu_check_smintf("$0.25", "%$", 25);
	mu_check_smintf("$0.05", "%$", 5);
	mu_check_smintf("$30.00", "%$", 3000);
	mu_check_smintf("$30.25", "%$", 3025);
	mu_check_smintf("-$5.45", "%$", -545);
	mu_check_smintf("-$0.40", "%$", -40);
	mu_check_smintf("-$0.01", "%$", -1);
	mu_check_smintf("-$100.25", "%$", -10025);
	//----------------------------
	mu_end();
}

int _test_special() {
	mu_start();
	//----------------------------
	mu_check_smintf("INT_MAX $21474836.47", "INT_MAX %$", INT_MAX);
	mu_check_smintf("INT_MIN -$21474836.48", "INT_MIN %$", INT_MIN);
	mu_check_smintf("INT_MAX 2147483647", "INT_MAX %d", INT_MAX);
	mu_check_smintf("INT_MIN -2147483648", "INT_MIN %d", INT_MIN);
	mu_check_smintf("Hello %c.", "Hello %c.", 128);
	mu_check_smintf("Does this work? %d", "Does this work? %%d");
	mu_check_smintf("Test for % with nothing after 50%", "Test for % with nothing after 50%");
	mu_check_smintf("123 0b1111011", "%d %b", 123, 123);
	mu_check_smintf("Extra Hello", "Extra %s", "Hello", "Hello");
	//----------------------------
	mu_end();
}

int main(int argc, char* argv[]) {
	
	mu_run(_test_empty);
	mu_run(_test_char);
	mu_run(_test_string);
	mu_run(_test_number);
	mu_run(_test_format_string);
	mu_run(_test_format_char);
	mu_run(_test_format_percent);
	mu_run(_test_format_not_valid);
	mu_run(_test_format_integer);
	mu_run(_test_format_hex);
	mu_run(_test_format_binary);
	mu_run(_test_format_currency);
	mu_run(_test_special);

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
