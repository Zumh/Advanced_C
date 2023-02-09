#include <stdio.h>
#include <stdlib.h>
#include "count_words.h"
#include "clog.h"

int main(int argc, char* argv[]) {

	log_int(count_words("My apples are sweet."));

	log_int(count_words("My friend's apples are sweeter."));

	log_int(count_words("A pear is sweeter than an apple.."));

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
