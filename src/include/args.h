#ifndef BOOKSORT_ARGS_H_
#define BOOKSORT_ARGS_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "console.h"

typedef enum flag {
	FLAG_NULL = -1,
	FLAG_HELP = 0,
	FLAG_VERBOSE,
	FLAG_TITLE,
	FLAG_AUTHOR,
	FLAG_GENRE,
	FLAG_NEW_BOOK,
	FLAG_REMOVE_BOOK,
	FLAG_LIST_BOOKS,

	COUNT_FLAGS,
} flag;

typedef enum command {
	CMD_NONE = 0,
	CMD_NEW_BOOK,
	CMD_REMOVE_BOOK,
	CMD_LIST_BOOKS,
} command;

typedef struct config {
	bool verbose;
	command cmd;
	const char *title;
	const char *author;
	const char *genre;
} config;

static const char *const flags_long[] = {
	[FLAG_HELP] = "--help",          [FLAG_VERBOSE] = "--verbose",
	[FLAG_TITLE] = "--title",        [FLAG_AUTHOR] = "--author",
	[FLAG_GENRE] = "--genre",        [FLAG_NEW_BOOK] = "--new",
	[FLAG_REMOVE_BOOK] = "--remove", [FLAG_LIST_BOOKS] = "--list",
};

extern const char *p_name;

#define shift(arr) ((arr) = &((arr)[1]))

extern inline bool is_long_flag(const char *arg);

bool process_args(config *conf, int argc, const char **argv);
bool process_long_flag(config *conf, int *argc, const char ***argv);

#endif /* BOOKSORT_ARGS_H_ */
