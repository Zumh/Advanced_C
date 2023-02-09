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

bool parse_element(Element* a_element, char const** a_pos) {

	bool found_element = false;

	while(isspace(**a_pos)) {
		*a_pos += 1;
	}
	if(isdigit(**a_pos) || ((**a_pos) == '-')) {
		found_element = parse_int(&(a_element -> as_int), a_pos);
		if(found_element) {
			a_element->type = ELEMENT_INT;
		}
	}
	else if(**a_pos == '"') {
		found_element = parse_string(&(a_element -> as_string), a_pos);
		if(found_element) {
			a_element->type = ELEMENT_STRING;
		}
	}
	return found_element;
}

bool parse_string(char** a_string, char const** a_pos) {

	bool found_str = false;
	int str_len = 0;
	int add_shift = 0;
	int escp_char = 0;

	while(((**a_pos) != '\0') && ((**a_pos) != '\n') && (escp_char != 2)) {
		if(**a_pos == '\"') {
			*a_pos += 1;
			escp_char++;
			add_shift++;
		}
		else{
			*a_pos += 1;
			str_len++;
			add_shift++;
		}
	}

	*a_pos -= add_shift;

	if((strchr(*a_pos, '\n') == NULL) && (escp_char % 2 == 0)){
		found_str = true;
		escp_char = 0;
	}
	else{
		*a_pos += add_shift;
	}

	if(found_str == true) {
		*a_string = malloc((str_len + 1) * sizeof(**a_string));
		for(int idx_in_str = 0; (((**a_pos) != '\0') && (escp_char != 2)); idx_in_str++) {
			if(**a_pos != '\"') {
				(*a_string)[idx_in_str] = (**a_pos);
				*a_pos += 1;
			}
			else{
				*a_pos += 1;
				idx_in_str--;
				escp_char++;
			}
		}
		(*a_string)[str_len] = '\0';
	}
	return found_str;
}

void free_element(Element element) {
	if(element.type == ELEMENT_STRING) {
		free(element.as_string);
	}
}

void print_element(Element element) {
	if(element.type == ELEMENT_INT) {
		printf("%d", element.as_int);
	}
	else if(element.type == ELEMENT_STRING) {
		printf("\"%s\"", element.as_string);
	}
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
