#ifndef __CLOG_H__
#define __CLOG_H__

#include <stdio.h>
#include <stdbool.h>

#define debugf(...)												\
	do {														\
		printf("[%s:%d] ", __FILE__,  __LINE__); 				\
		printf(__VA_ARGS__);									\
	} while(false)												\

#define printf_red(...) 	__mu_printf_any_color("\x1b[31m", __VA_ARGS__)	
#define printf_green(...) 	__mu_printf_any_color("\x1b[32m", __VA_ARGS__)
#define printf_yellow(...) 	__mu_printf_any_color("\x1b[33m", __VA_ARGS__)
#define printf_blue(...) 	__mu_printf_any_color("\x1b[34m", __VA_ARGS__)
#define printf_magenta(...) __mu_printf_any_color("\x1b[35m", __VA_ARGS__)
#define printf_cyan(...) 	__mu_printf_any_color("\x1b[36m", __VA_ARGS__)

#define __mu_printf_any_color(ansi_color_code, ...)				\
	do {														\
		printf("%s", ansi_color_code); 							\
		printf(__VA_ARGS__);									\
		printf("\x1b[0m");										\
	} while(false)												\

#define log_int(n) 		printf("%s == %d\n", (#n), (n))
#define log_char(chr)	printf("%s == '%c'\n", (#chr), (chr))
#define log_str(str) 	printf("%s == \"%s\"\n", (#str), (str))
#define log_addr(addr) 	printf("%s == %p\n", (#addr), (addr))
#define log_float(flt)	printf("%s == %.016f\n", (#flt), (flt))
#define log_bool(stmt) 	printf("%s == %s\n", (#stmt), (stmt) ? "true" : "false")

#endif /* end of include guard: __CLOG_H__ */
