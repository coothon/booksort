#define _DEFAULT_SOURCE 1
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "include/khash.h"
#include "include/vec.h"

#include "include/console.h"

#include "include/args.h"
#include "include/book.h"
#include "include/booksort.h"

#include "include/persistent.h"

const char *p_name = NULL;

int main(int argc, char **argv) {
	p_name = argv[0];

	if (argc < 2) {
		error_put("Expected arguments.");
		put_usage();
		return EXIT_FAILURE;
	}

	config conf = {0};
	if (!process_args(&conf, argc, argv))
		return EXIT_FAILURE;

	booksorter *b = NULL;
	if (is_file(DATABASE_FILE_PATH)) {
		const char *database = read_entire_file(DATABASE_FILE_PATH);
		if (!database) {
			warn_put(
				"JSON database corrupted. Proceeding with empty database.");
			goto skip_db;
		}

		// JSON requires at least the enclosing square brackets.
		if (strlen(database) < 2) {
			warn_put(
				"JSON database corrupted. Proceeding with empty database.");
			goto skip_db;
		}

		b = deserialize_books(database);
		free(database);

		if (!b) {
			warn_put(
				"JSON database corrupted. Proceeding with empty database.");
			goto skip_db;
		}
	} else {
	skip_db:
		if (!(b = booksorter_init())) {
			error_put("Insufficient memory.");
			return EXIT_FAILURE;
		}
	}

	switch (conf.cmd) {
	case CMD_LIST_BOOKS:
		break;

	case CMD_NEW_BOOK: {
		if (!(conf.title && conf.author && conf.genre)) {
			error_put("Book title, author, and genre must be provided to "
			          "create a new book.");
			put_usage();
			goto destroy_fail;
		}
		book *user_book = add_book(b, conf.title, conf.author, conf.genre);
		if (!user_book) {
			error_put("Book creation failed.");
			goto destroy_fail;
		}
	} break;

	case CMD_REMOVE_BOOK: {
		if (!(conf.title && conf.author && conf.genre)) {
			error_put("Book title, author, and genre must be provided to "
			          "remove a book.");
			put_usage();
			goto destroy_fail;
		}
		if (!remove_book(b, conf.title, conf.author, conf.genre)) {
			error_put("Book does not exist in database.");
			goto destroy_fail;
		}
	} break;

	case CMD_NONE:
	default:
		error_put("Fatal error.");
		goto destroy_fail;
	}

	serialize_into_file(DATABASE_FILE_PATH, b);
	booksorter_destroy(b);
	return EXIT_SUCCESS;

destroy_fail:
	booksorter_destroy(b);
	return EXIT_FAILURE;
}
