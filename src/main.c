#define _DEFAULT_SOURCE 1
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "include/khash.h"
#include "include/vec.h"

#include "include/args.h"
#include "include/book.h"
#include "include/booksort.h"

#include "include/persistent.h"

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
		return EXIT_FAILURE;
	}

	config conf = {0};
	if (!process_args(&conf, argc, argv))
		return EXIT_FAILURE;

	booksorter *b = booksorter_init();
	if (!b) {
		ERR("Insufficient memory.");
		return EXIT_FAILURE;
	}

	switch (conf.cmd) {
	case CMD_NONE:
	case CMD_LIST_BOOKS:
		break;

	case CMD_NEW_BOOK: {
		if (!(conf.title && conf.author)) {
			ERR("Book title and author must be provided to create a new book.");
			goto destroy_fail;
		}
		book *user_book = add_book(b, conf.title, conf.author, "No genre");
		if (!user_book) {
			ERR("Book creation failed.");
			goto destroy_fail;
		}
	} break;


	default:
		booksorter_destroy(b);
		ERR("Fatal error.");
		return EXIT_FAILURE;
	}

	const char *sb = serialize_books(b);
	if (!sb)
		goto destroy_fail;
	printf("%s\n", sb);
	free(sb);

	booksorter_destroy(b);
	return EXIT_SUCCESS;

destroy_fail:
	booksorter_destroy(b);
	return EXIT_FAILURE;
}
