#ifndef BOOKSORT_CONSOLE_H_
#define BOOKSORT_CONSOLE_H_

#define _DEFAULT_SOURCE 1
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024

extern const char *p_name;

const char *get_input(void);

// Inline them because they're so small.
extern inline void error_put(const char *restrict fmt, ...);
extern inline void warn_put(const char *restrict fmt, ...);
extern inline void info_put(const char *restrict fmt, ...);
extern inline void put_usage(void);
extern inline void put_help(void);

#endif /* BOOKSORT_CONSOLE_H_ */
