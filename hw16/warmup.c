#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

typedef struct { 
	int x; 
	int y; 
} Point;

char* read_file(const char* path, const char** a_error) {
	FILE* file = fopen(path, "r");
	char* str_copy;

	if(file != NULL) {
		fseek(file, 0, SEEK_END);
		int len_file = ftell(file);
		rewind(file);

		int num_of_char = len_file / sizeof(char);
		char* str = malloc(sizeof(*str) * (len_file + 1));
		fread(str, len_file + 1, num_of_char, file); 

		str[len_file] = '\0';
		str_copy = str;
		fclose(file);
		*a_error = NULL;
	}
	else {
		*a_error = strerror(errno);
	}
	return str_copy;
}

void write_file(const char* path, const char* contents, const char** a_error) {

	if(contents != NULL) {
		FILE* file = fopen(path, "w");

		int length = sizeof(contents); 
		fwrite(contents, 1, length, file);

		fclose(file);
		*a_error = NULL;
	}
	else {
		*a_error = strerror(errno);
	}
}

void write_point(const char* path, Point p, const char** a_error) {
	FILE* file = fopen(path, "w");

	fwrite(&p, sizeof(p), 1, file);

	fclose(file);
}

Point read_point(const char* path, const char** a_error) {
	FILE* file = fopen(path, "r");

	Point p;
	fread(&p, sizeof(p), 1, file);

	fclose(file);
	return p;
}

int main(int argc, char* argv[]) {

	const char* path = "test_warmup.txt";
	const char* a_error;
	char* read_str = read_file(path, &a_error);
	printf("%s", read_str);
	free(read_str);

	const char* path_fail = "test_failed.txt";
	const char* a_error_two = NULL;
	read_str = read_file(path_fail, &a_error_two);
	printf("%s", a_error_two);

	const char* path_write = "test_write.txt";
	const char* a_error_three = NULL;
	const char* contents = "This is a write test.";
	write_file(path_write, contents, &a_error_three);
	assert(a_error_three == NULL);

	const char* path_point = "test_write_point.txt";
	Point p = { .x = 5, .y = 10 };
	write_point(path_point, p, &a_error_three);

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
