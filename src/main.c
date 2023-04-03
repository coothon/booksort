#define _DEFAULT_SOURCE 1
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "include/args.h"
#include "include/book.h"
#include "include/booksort.h"

const char *p_name = NULL;

#define MAX_INPUT_SIZE 1024
static const char *get_input(void) {
	char input[MAX_INPUT_SIZE];

	// Replace trailing newline with null-byte.
	fgets(input, MAX_INPUT_SIZE, stdin);
	size_t end = strcspn(input, "\n");
	if (end >= MAX_INPUT_SIZE)
		--end;
	input[end] = '\0';

	return (const char *)strdup(input);
}

int main(int argc, char **argv) {
	p_name = argv[0];

	if (argc < 2) {
		ERR("Expected arguments.");
	}

	config conf = {0};
	if (!process_args(&conf, argc, argv))
		return EXIT_FAILURE;

	booksorter *b = booksorter_init();
	if (!b) {
		ERR("Insufficient memory.");
		return EXIT_FAILURE;
	}

	booksorter_destroy(b);
	return EXIT_SUCCESS;
}
