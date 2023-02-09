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

	input = "-123, 456]";
	pos = input;
	is_success = parse_int(&result, &pos);
	mu_check(is_success);
	mu_check(pos == input + 4);
	mu_check(result == -123);
	mu_check(*pos == ',');
	//----------------------------------
	mu_end();
}

static int _test_parse_element_int_plain() {
	mu_start();
	//----------------------------------
	// Plain integer
	Element element; // will be initialized by parse_element
	char const* input = "1";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(element.as_int == 1);
	mu_check(element.type == ELEMENT_INT);
	mu_check(pos == input + 1); // pos should now refer to byte after '1'. 
	mu_check(*pos == '\0');  	// That byte should be the null terminator.
	
	// Negative digit
	input = "-2";
	pos = input;
	is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(element.as_int == -2);
	mu_check(element.type == ELEMENT_INT);
	mu_check(pos == input + 2);
	mu_check(*pos == '\0');
	//----------------------------------
	mu_end();
}

static int _test_parse_element_with_leading_whitespace() {
	mu_start();
	//----------------------------------
	Element element;
	char const* input = "  1";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(element.as_int == 1);
	mu_check(element.type == ELEMENT_INT);
	mu_check(pos == input + 3);
	mu_check(*pos == '\0');
	//----------------------------------
	mu_end();
}

static int _test_parse_element_int_oddballs() {
	mu_start();
	//----------------------------------
	Element element;
	char const* input = " 4 A";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(element.as_int == 4);
	mu_check(element.type == ELEMENT_INT);
	mu_check(pos == input + 2);
	mu_check(*pos == ' ');

	// More tests
	input = "  -2A";
	pos = input;
	is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(element.as_int == -2);
	mu_check(element.type == ELEMENT_INT);
	mu_check(pos == input + 4);
	mu_check(*pos == 'A');

	input = "  1234-";
	pos = input;
	is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(element.as_int == 1234);
	mu_check(element.type == ELEMENT_INT);
	mu_check(pos == input + 6);
	mu_check(*pos == '-');
	//----------------------------------
	mu_end();
}

static int _test_parse_element_invalid() {
	mu_start();
	//----------------------------------
	Element element;
	char const* input = "--4";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(!is_success);
	mu_check(pos == input + 1);
	mu_check(*pos == '-');

	// More test
	input = "-";
	pos = input;
	is_success = parse_element(&element, &pos);
	mu_check(!is_success);
	mu_check(pos == input + 1);
	mu_check(*pos == '\0');

	input = "-ABC";
	pos = input;
	is_success = parse_element(&element, &pos);
	mu_check(!is_success);
	mu_check(pos == input + 1);
	mu_check(*pos == 'A');
	//----------------------------------
	mu_end();
}

static int _test_parse_string_valid_empty() {
	mu_start();
	//----------------------------------
	char* result;
	char const* input = "\"\"";
	char const* pos = input;
	bool is_success = parse_string(&result, &pos);
	mu_check(is_success);
	mu_check_strings_equal("", result);
	mu_check(pos == input + 2);
	mu_check(*pos == '\0');
	free(result);
	//----------------------------------
	mu_end();
}

static int _test_parse_string_valid_one_char() {
	mu_start();
	//----------------------------------
	char* result;
	char const* input = "\"A\"";
	char const* pos = input;
	bool is_success = parse_string(&result, &pos);
	mu_check(is_success);
	mu_check_strings_equal("A", result);
	mu_check(pos == input + 3);
	mu_check(*pos == '\0');
	free(result);
	//----------------------------------
	mu_end();
}

static int _test_parse_string_valid_multiple_chars() {
	mu_start();
	//----------------------------------
	char* result;
	char const* input = "\"ABC\"";
	char const* pos = input;
	bool is_success = parse_string(&result, &pos);
	mu_check(is_success);
	mu_check_strings_equal("ABC", result);
	mu_check(pos == input + 5);
	mu_check(*pos == '\0');
	free(result);

	input = "ABC";
	pos = input;
	is_success = parse_string(&result, &pos);
	mu_check(is_success);
	mu_check(pos == input + 3);
	mu_check(*pos == '\0');
	free(result);
	//----------------------------------
	mu_end();
}

static int _test_parse_string_invalid() {
	mu_start();
	//----------------------------------
	char* result;
	char const* input = "\"A";
	char const* pos = input;
	bool is_success = parse_string(&result, &pos);
	mu_check(! is_success);
	mu_check(pos = input + 2);
	mu_check(*pos == '\0');
	// We do not call free(...) if the string was invalid.

	input = "\"A\nB\"";
	pos = input;
	is_success = parse_string(&result, &pos);
	mu_check(! is_success);
	mu_check(pos == input + 2);
	mu_check(*pos == '\n');
	//----------------------------------
	mu_end();
}

static int _test_parse_element_string() {
	mu_start();
	//----------------------------------
	Element element;
	char const* input = "\"ABC\"";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check_strings_equal("ABC", element.as_string);
	mu_check(element.type == ELEMENT_STRING);
	mu_check(pos == input + 5);
	mu_check(*pos == '\0');
	free_element(element);

	input = "\"ABC\"123";
	pos = input;
	is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check_strings_equal("ABC", element.as_string);
	mu_check(element.type == ELEMENT_STRING);
	mu_check(pos == input + 5);
	mu_check(*pos == '1');
	free_element(element);
	//----------------------------------
	mu_end();
}

static void _test_print_element() {
	Element element;
	char const* input = "123";
	parse_element(&element, &input);
	printf("Testing parse_element(&element, \"123\")\n");
	printf(" - Expected: 123\n");
	printf(" - Actual:   ");
	print_element(element);
	fputc('\n', stdout);
	free_element(element);

	input = "\"ABC\"";
	parse_element(&element, &input);
	printf("Testing parse_element(&element, \"\\\"ABC\\\"\")\n");
	printf(" - Expected: \"ABC\"\n");
	printf(" - Actual:   ");
	print_element(element);
	fputc('\n', stdout);
	free_element(element);
}

static int _test_parse_list_trivial() {
	mu_start();
	//----------------------------------
	Node* head;
	char const* input = "[]";
	char const* pos = input;
	bool is_success = parse_list(&head, &pos);
	mu_check(is_success);
	mu_check(pos == input + 2);
	mu_check(*pos == '\0');
	mu_check(head == NULL);
	free(head);

	input = "[0]";
	pos = input;
	is_success = parse_list(&head, &pos);
	mu_check(is_success);
	mu_check(pos == input + 3);
	mu_check(*pos == '\0');
	mu_check(head != NULL);
	mu_check(head->element.type == ELEMENT_INT);
	mu_check(head->element.as_int == 0);
	mu_check(head->next == NULL);
	free(head);

	input = "[1234]";
	pos = input;
	is_success = parse_list(&head, &pos);
	mu_check(is_success);
	mu_check(pos == input + 6);
	mu_check(*pos == '\0');
	mu_check(head != NULL);
	mu_check(head->element.type == ELEMENT_INT);
	mu_check(head->element.as_int == 1234);
	mu_check(head->next == NULL);
	free(head);

	input = "[12,34]";
	pos = input;
	is_success = parse_list(&head, &pos);
	mu_check(is_success);
	mu_check(pos == input + 7);
	mu_check(*pos == '\0');
	mu_check(head != NULL);
	mu_check(head->element.type == ELEMENT_INT);
	mu_check(head->element.as_int == 12);
	mu_check(head->next != NULL);
	mu_check(head->next->element.type == ELEMENT_INT);
	mu_check(head->next->element.as_int == 34);
	mu_check(head->next->next == NULL);
	free(head->next);
	free(head);

	input = "[12,34,54]";
	pos = input;
	is_success = parse_list(&head, &pos);
	mu_check(is_success);
	mu_check(pos == input + 10);
	mu_check(*pos == '\0');
	mu_check(head != NULL);
	mu_check(head->element.type == ELEMENT_INT);
	mu_check(head->element.as_int == 12);
	mu_check(head->next != NULL);
	mu_check(head->next->element.type == ELEMENT_INT);
	mu_check(head->next->element.as_int == 34);
	mu_check(head->next->next != NULL);
	mu_check(head->next->next->element.type == ELEMENT_INT);
	mu_check(head->next->next->element.as_int == 54);
	mu_check(head->next->next->next == NULL);
	free(head->next->next);
	free(head->next);
	free(head);

	input = "[\"Hello\",34]";
	pos = input;
	is_success = parse_list(&head, &pos);
	mu_check(is_success);
	mu_check(pos == input + 12);
	mu_check(*pos == '\0');
	mu_check(head != NULL);
	mu_check(head->element.type == ELEMENT_STRING);
	mu_check_strings_equal(head->element.as_string, "Hello");
	mu_check(head->next != NULL);
	mu_check(head->next->element.type == ELEMENT_INT);
	mu_check(head->next->element.as_int == 34);
	mu_check(head->next->next == NULL);
	free(head->next);
	free(head->element.as_string);
	free(head);
	//----------------------------------
	mu_end();
}

void _test_parse_element_list() {
	Element element;
	char const* input = "[123,345,\"Hello\"]";
	parse_element(&element, &input);
	printf("Testing parse_element(&element, \"[123,345,\"Hello\"]\")\n");
	printf(" - Expected: [123,345,\"Hello\"]\n");
	printf(" - Actual:   ");
	print_element(element);
	fputc('\n', stdout);
	free_element(element);
}

static int _test_parse_list_invalid() {
	mu_start();
	//----------------------------------
	Node* head;
	char const* input = "[";
	char const* pos = input;
	bool is_success = parse_list(&head, &pos);
	mu_check(!is_success);
	mu_check(pos == input + 1);
	mu_check(*pos == '\0');

	input = "A[]";
	pos = input;
	is_success = parse_list(&head, &pos);
	mu_check(!is_success);
	mu_check(pos == input);
	mu_check(*pos == 'A');

	input = "[1,,1]";
	pos = input;
	is_success = parse_list(&head, &pos);
	mu_check(!is_success);	
	mu_check(pos == input + 3);
	mu_check(*pos == ',');

	input = "[1,1]]";
	pos = input;
	is_success = parse_list(&head, &pos);
	mu_check(!is_success);
	mu_check(pos == input + 5);
	mu_check(*pos == ']');
	//----------------------------------
	mu_end();
}

static void _test_print_element_to_file() {
	//---------------------------------
	FILE* file_test = fopen("test.json", "w");
	Element element;
	char const* input = "[123,345,\"Hello\",null,true]";
	parse_element(&element, &input);
	print_element_to_file(element, file_test);
	fclose(file_test);
	free_element(element);
	//---------------------------------
}

static int _test_read_json() {
	mu_start();
	//---------------------------------
	char const* filename = "test_json_read.json";
	Element element;
	bool is_success = read_json(filename, &element);
	mu_check(is_success);
	free_element(element);
	//---------------------------------
	mu_end();
}

static int _test_read_json_invalid() {
	mu_start();
	//---------------------------------
	char const* filename = "test_read.json";
	Element element;
	bool is_success = read_json(filename, &element);
	mu_check(!is_success);

	filename = "test_json_invalid.json";
	is_success = read_json(filename, &element);
	mu_check(!is_success);

	filename = "test_json_invalid_two.json";
	is_success = read_json(filename, &element);
	mu_check(!is_success);
	//---------------------------------
	mu_end();
}

static int _test_parse_null_valid() {
	mu_start();
	//---------------------------------
	char const* input = "null";
	char const* pos = input;
	bool is_success = parse_null(&pos);
	mu_check(is_success);
	mu_check(*pos == '\0');

	input = "nullity";
	pos = input;
	is_success = parse_null(&pos);
	mu_check(is_success);
	mu_check(*pos == 'i');
	//---------------------------------
	mu_end();
}

static int _test_parse_null_element() {
	mu_start();
	//---------------------------------
	Element element;
	char const* input = "null";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(pos == input + 4);
	mu_check(*pos == '\0');
	//---------------------------------
	mu_end();
}

static int _test_parse_null_invalid() {
	mu_start();
	//---------------------------------
	char const* input = "nll";
	char const* pos = input;
	bool is_success = parse_null(&pos);
	mu_check(!is_success);
	mu_check(*pos == 'l');

	input = "nil";
	pos = input;
	is_success = parse_null(&pos);
	mu_check(!is_success);
	mu_check(*pos == 'i');
	//---------------------------------
	mu_end();
}

static int _test_parse_bool_valid() {
	mu_start();
	//---------------------------------
	bool a_value = false;
	char const* input = "true";
	char const* pos = input;
	bool is_success = parse_bool(&a_value, &pos);
	mu_check(is_success);
	mu_check(a_value);
	mu_check(*pos == '\0');

	a_value = false;
	input = "false";
	pos = input;
	is_success = parse_bool(&a_value, &pos);
	mu_check(is_success);
	mu_check(a_value);
	mu_check(*pos == '\0');

	a_value = false;
	input = "falsehello";
	pos = input;
	is_success = parse_bool(&a_value, &pos);
	mu_check(is_success);
	mu_check(a_value);
	mu_check(*pos == 'h');
	//---------------------------------
	mu_end();
}

static int _test_parse_bool_element() {
	mu_start();
	//---------------------------------
	Element element;
	char const* input = "true";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(pos == input + 4);
	mu_check(*pos == '\0');

	input = "false";
	pos = input;
	is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(pos == input + 5);
	mu_check(*pos == '\0');
	//---------------------------------
	mu_end();
}

static int _test_write_json() {
	mu_start();
	//---------------------------------
	char const* filename = "test_json_read.json";
	Element element;
	bool is_success = read_json(filename, &element);
	mu_check(is_success);

	char const* filename_two = "test_json_write.json";
	write_json(filename_two, element);
	free_element(element);
	//---------------------------------
	mu_end();
}

int main(int argc, char* argv[]) {
	
	mu_run(_test_parse_int_zero);
	mu_run(_test_parse_int_invalid);
	mu_run(_test_parse_int_valid);
	mu_run(_test_parse_element_int_plain);
	mu_run(_test_parse_element_with_leading_whitespace);
	mu_run(_test_parse_element_int_oddballs);
	mu_run(_test_parse_element_invalid);
	mu_run(_test_parse_string_valid_empty);
	mu_run(_test_parse_string_valid_one_char);
	mu_run(_test_parse_string_valid_multiple_chars);
	mu_run(_test_parse_string_invalid);
	mu_run(_test_parse_element_string);
	_test_print_element();
	mu_run(_test_parse_list_trivial);
	_test_parse_element_list();
	mu_run(_test_parse_list_invalid);
	_test_print_element_to_file();
	mu_run(_test_read_json);
	mu_run(_test_read_json_invalid);
	mu_run(_test_parse_null_valid);
	mu_run(_test_parse_null_element);
	mu_run(_test_parse_null_invalid);
	mu_run(_test_parse_bool_valid);
	mu_run(_test_parse_bool_element);
	mu_run(_test_write_json);

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
