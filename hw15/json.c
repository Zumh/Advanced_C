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
	else if(**a_pos == '[') {
		found_element = parse_list(&(a_element -> as_list), a_pos);
		if(found_element) {
			a_element->type = ELEMENT_LIST;
		}
	}
	else if(**a_pos == 'n') {
		found_element = parse_null(a_pos);
		if(found_element) {
			a_element->type = ELEMENT_NULL;
			a_element->as_null = NULL;
		}
	}
	else if(**a_pos == 't' || **a_pos == 'f') {
		found_element = parse_bool(&(a_element -> as_bool), a_pos);
		if(found_element) {
			a_element->type = ELEMENT_BOOL;
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
	} else{
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
	else if(element.type == ELEMENT_LIST) {
		while(element.as_list->next != NULL) {
			free_element(element.as_list->element);
			Node* old_node = element.as_list;
			element.as_list = element.as_list->next;
			free(old_node);
		}
		free_element(element.as_list->element);
		free(element.as_list);
	}
}

void print_element_to_file(Element element, FILE* file) {
	if(element.type == ELEMENT_INT) {
		fprintf(file, "%d", element.as_int);
	}
	else if(element.type == ELEMENT_STRING) {
		fprintf(file, "\"%s\"", element.as_string);
	}
	else if(element.type == ELEMENT_LIST) {
		fputc('[', file);
		while((element.as_list->next) != NULL) {
			print_element_to_file(element.as_list->element, file);
			fputc(',', file);
			element.as_list = element.as_list->next;
		}
		print_element_to_file(element.as_list->element, file);
		fputc(']', file);
	}
	else if(element.type == ELEMENT_BOOL) {
		const char* type_bool = (element.as_bool ? "true" : "false");
		fputs(type_bool, file);
	}
	else if(element.type == ELEMENT_NULL) {
		const char* type_null = "null";
		fputs(type_null, file);
	}
}

void print_element(Element element) {
	print_element_to_file(element, stdout);
}

bool parse_list(Node** a_head, char const** a_pos) {

	bool found_list = false;
	int increment = 0;
	int start = 0;
	int end = 0;

	if(**a_pos != '[') {
		return found_list;
	}

	do{
		if(**a_pos == '[') {
			start++;
		}
		else if(**a_pos == ']') {
			end++;
		}
		*a_pos += 1;
		increment++;
	}while((**a_pos != '\0')); 

	if(start == end) {
		found_list = true;
		start = 0;
		end = 0;
		*a_pos -= increment;
	}
	else {
		start = 0;
		end = 0;
		*a_pos -= increment;
		bool unequal = false;
		while(unequal == false && **a_pos != '\0') {
			if(**a_pos == '[') {
				start++;
			}
			else if(**a_pos == ']') {
				end++;
				if(end > start) {
					unequal = true;
				}
			}
			if(unequal == false) {
				*a_pos += 1;
			}
		}
		return found_list;
	}
	
	bool invalid = false;
	while(invalid == false && **a_pos != '\0') {
		if(**a_pos == ',') {
			*a_pos += 1;
			if(**a_pos == ',') {
				invalid = true;
				found_list = false;
			}
			else {
				*a_pos -= 1;
			}
		}
		if(invalid == false) {
			*a_pos += 1;
		}
	}

	if(found_list == true) {
		*a_pos -= increment;
		int entry = 0;
		Node* new_node = *a_head;
		do{
			if(**a_pos == '[') {
				start++;
				*a_pos += 1; 
				if(**a_pos == ']') {
					*a_head = NULL;
				}
				*a_pos -= 1;
			}
			else if(**a_pos == ']') {
				end++;
			}
			else {
				if(entry == 0) {
					*a_head = malloc(sizeof(*(*a_head)));
					new_node = *a_head;
					new_node->next = NULL;
					entry++;
				}
				if(**a_pos == ',') {
					*a_pos += 1;
					new_node->next = malloc(sizeof(*new_node));
					new_node = new_node->next;
					new_node->next = NULL;
				}
				parse_element(&(new_node->element), a_pos);
				*a_pos -= 1;
			}
			*a_pos += 1;
		}while (start != end);
	}
	return found_list;
}

bool read_json(char const* filename, Element* a_element) {
	bool valid_json = false;
	FILE* file = fopen(filename, "r");
	
	// This code has been adapted from lecture snippets
	if(file != NULL) {
		fseek(file, 0, SEEK_END);
		int file_len = ftell(file);
	    rewind(file);	

		char* str = malloc(sizeof(*str) * (file_len + 1));
		int i = 0;
		for (char ch = fgetc(file); !feof(file); ch = fgetc(file)) {
			str[i] = ch;
			i++;
		}
		str[file_len] = '\0';

		char const* pos = str;	
		valid_json = parse_element(a_element, &pos);
		fclose(file);

		if(valid_json == false && pos != str) {
			fprintf(stderr, "JSON has invalid trailing characters.\n");
		}
		else if(valid_json == false && pos == str) {
			fprintf(stderr, "File does not contain valid JSON element.\n");
		}

		free(str);
	}
	else {
		fprintf(stderr, "fopen returned NULL.\n");
	}
	return valid_json;
}

bool parse_null(char const** a_pos) {
	bool found_null = false;
	
	if(**a_pos == 'n') {
		*a_pos += 1;
		if(**a_pos == 'u') {
			*a_pos += 1;
			if(**a_pos == 'l') {
				*a_pos += 1;
				if(**a_pos == 'l') {
					*a_pos += 1;
					found_null = true;
				}
			}
		}
	}
	return found_null;
}

bool parse_bool(bool* a_value, char const** a_pos) {
	bool found_bool = false;

	if(**a_pos == 't') {
		*a_pos += 1;
		if(**a_pos == 'r'){
			*a_pos += 1;
			if(**a_pos == 'u') {
				*a_pos += 1;
				if(**a_pos == 'e') {
					*a_pos += 1;
					found_bool = true;
					*a_value = true;
				}
			}
		}
	}
	else if(**a_pos == 'f') {
		*a_pos += 1;
		if(**a_pos == 'a') {
			*a_pos += 1;
			if(**a_pos == 'l') {
				*a_pos += 1;
				if(**a_pos == 's') {
					*a_pos += 1;
					if(**a_pos == 'e') {
						*a_pos += 1;
						found_bool = true;
						*a_value = true;
					}
				}
			}
		}
	}
	return found_bool;
}

void write_json(char const* filename, Element element) {
	FILE* file = fopen(filename, "w");
	print_element_to_file(element, file);
	fclose(file);
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
