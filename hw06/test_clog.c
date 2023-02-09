#include <stdlib.h>
#include "clog.h"

int main(int argc, char* argv[]) {
	debugf("%d%% of Columbians live in %s.\n", 15, "Bogota");

	// Tests for printf_colors
	printf_red("%s\n", "RED");
	printf_green("%s\n", "GREEN");
	printf_yellow("%s\n", "YELLOW");
	printf_blue("%s\n", "BLUE");
	printf_magenta("%s\n", "MAGENTA");
	printf_cyan("%s\n", "CYAN");

	// Tests for log_int(...)
	log_int(3 + 4);
	int result = 15;
	log_int(result);

	// Tests for log_char(...)
	log_char('A');
	log_char(65);
	char* class_name = "ECE 264";
	log_char(class_name[0]);

	// Tests for log_str(...)
	log_str(class_name);

	// Tests for log_addr(...)
	log_addr(class_name);

	// Tests for log_float(...)
	log_float(1.0 / 8.0);

	// Tests for log_bool(...)
	log_bool(3 > 5);
	log_bool(3 > 1);

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
