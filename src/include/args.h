#ifndef BOOKSORT_ARGS_H_
#define BOOKSORT_ARGS_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct config {
	bool verbose;
	const char *title;
	const char *author;
} config;

typedef enum flag {
	FLAG_NULL = -1,
	FLAG_HELP = 0,
	FLAG_VERBOSE,
	FLAG_TITLE,
	FLAG_AUTHOR,

	COUNT_FLAGS,
} flag;

static const char *const flags_long[] = {
	[FLAG_HELP] = "--help",
	[FLAG_VERBOSE] = "--verbose",
	[FLAG_TITLE] = "--title",
	[FLAG_AUTHOR] = "--author",
};

// Not quite like how they should be; you can't chain them.
static const char *flags_short[] = {
	[FLAG_HELP] = "-h",
	[FLAG_VERBOSE] = "-v",
	[FLAG_TITLE] = "-t",
	[FLAG_AUTHOR] = "-a",
};

extern const char *p_name;

#define ERR_FMT(fmt, ...) \
	fprintf(stderr, "%s: Error: " fmt "\n", p_name, __VA_ARGS__)

#define ERR(fmt) fprintf(stderr, "%s: Error: " fmt "\n", p_name)

#define shift(arr) ((arr) = &((arr)[1]))

extern inline bool is_short_flag(const char *arg);
extern inline bool is_long_flag(const char *arg);

bool process_args(config *conf, int argc, const char **argv);
bool process_short_flag(config *conf, int *argc, const char ***argv);
bool process_long_flag(config *conf, int *argc, const char ***argv);

#endif /* BOOKSORT_ARGS_H_ */