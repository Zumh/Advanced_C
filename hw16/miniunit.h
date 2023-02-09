#include <stdbool.h>
#include <string.h>
#include "clog.h"

#ifndef __MINIUNIT_H__
#define __MINIUNIT_H__

#define mu_start() int __mu_first_check = 0

#define mu_end() return __mu_first_check

#define mu_check(condition)						\
	do {										\
		if(__mu_first_check == 0) {				\
			if(((condition) == false)) {		\
				__mu_first_check = __LINE__;	\
			}									\
		} 										\
	}while(false)																	

#define mu_check_strings_equal(str1, str2) mu_check(strcmp(str1, str2) == 0)

#define mu_run(function) 														\
	do {																		\
		int p_or_f = function();												\
		if(!(p_or_f)) {															\
			printf_green("Test passed: %s\n", (#function));						\
		}																		\
		else {																	\
			printf_red("Test failed: %s at line %d\n", (#function), p_or_f);	\
		}																		\
	} while(false)

#endif /* end of include guard: __MINIUNIT_H__ */
