#ifndef __JSON_H__
#define __JSON_H__
#include <stdbool.h>

typedef struct {
	enum  { ELEMENT_INT, ELEMENT_STRING, ELEMENT_LIST,
			ELEMENT_NULL, ELEMENT_BOOL } type;
	union {
		int    as_int;
		char*  as_string;
		struct _Node* as_list;
		void*  as_null;
		bool   as_bool;
	}; // ANONYMOUS union (C11).
} Element;


typedef struct _Node {
	struct _Node* next;
	Element element;
} Node;


bool parse_int(int* a_value, char const** a_pos);
bool parse_string(char** a_s, char const** a_pos);
bool parse_element(Element* a_element, char const** a_pos);
bool parse_list(Node** a_head, char const** a_pos);
void print_element(Element element);
void free_element(Element element);
bool parse_bool(bool* a_value, char const** a_pos);
bool parse_null(char const** a_pos);
bool parse_element(Element* a_element, char const** a_pos);
void print_element_to_file(Element element, FILE* file);
void write_json(char const* filename, Element element);
bool read_json(char const* filename, Element* a_element);

#endif

#define JSON_H_VERSION_2
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
