#
#--------------------------------------------------------
# VARIABLES
#
# CURRENT ASSIGNMENT
ASG_NICKNAME = HW10
BASE_NAME = json
#
# EXECUTABLES
EXECUTABLE = test_$(BASE_NAME)
EXECUTABLE_GCOV = $(EXECUTABLE)_gcov
#
# SOURCE FILENAMES
TEST_C = test_$(SRC_C)
SRC_C = $(BASE_NAME).c
SRC_H = $(BASE_NAME).h clog.h miniunit.h
SUBMIT_FILES = $(SRC_C) $(TEST_C) $(SRC_H) Makefile
#
# SYSTEM
SHELL = /bin/bash
CC = gcc
CFLAGS = -g -std=c11 -Wall -Wshadow -Wvla -Werror -pedantic
CFLAGS_GCOV = $(CLFLAGS) -fprofile-arcs -ftest-coverage 

#
#--------------------------------------------------------
# RULES

$(EXECUTABLE): $(SRC_C) $(TEST_C) $(SRC_H) 
	$(CC) -o $(EXECUTABLE) $(SRC_C) $(TEST_C) $(CFLAGS)

test: $(EXECUTABLE)
	./$(EXECUTABLE) 

clean: 
	rm -f $(EXECUTABLE) $(EXECUTABLE_GCOV) *.c.gcov *.gcda *.gcno

pretest: submit
	264test $(ASG_NICKNAME)

submit: $(SUBMIT_FILES)
	264submit $(ASG_NICKNAME) $(SUBMIT_FILES)

valgrind: 
	valgrind ./$(EXECUTABLE)

coverage: $(SRC_C) $(TEST_C)
	$(CC) -o $(EXECUTABLE_GCOV) $(SRC_C) $(TEST_C) $(CFLAGS_GCOV)
	./$(EXECUTABLE_GCOV)
	gcov -f $(SRC_C)

.PHONY: submit test pretest clean valgrind coverage

# vim: set noexpandtab tapstop=4 filetype=make
