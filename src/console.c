#include "include/console.h"

const char *get_input(void) {
	char input[MAX_INPUT_SIZE];

	// Replace trailing newline with null-byte.
	fgets(input, MAX_INPUT_SIZE, stdin);
	size_t end = strcspn(input, "\n");
	if (end >= MAX_INPUT_SIZE)
		--end;
	input[end] = '\0';

	return (const char *)strdup(input);
}

inline void error_put(const char *restrict fmt, ...) {
	va_list args;

	fprintf(stderr, "%s: Error: ", p_name);

	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	fputc('\n', stderr);
}

inline void warn_put(const char *restrict fmt, ...) {
	va_list args;

	fprintf(stderr, "%s: Warning: ", p_name);

	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	fputc('\n', stderr);
}

inline void info_put(const char *restrict fmt, ...) {
	va_list args;

	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	fputc('\n', stderr);
}

inline void put_usage(void) {
	printf("Usage: %s --new --title '<book title>' --author '<book author>' "
	       "--genre '<book genre>'\n",
	       p_name);
}

inline void put_help(void) {
	put_usage();
	puts("help");
}
