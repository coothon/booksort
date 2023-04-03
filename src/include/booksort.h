#ifndef BOOKSORT_H_
#define BOOKSORT_H_

#define _DEFAULT_SOURCE 1
#include <stdbool.h>
#include <string.h>

#include "khash.h"
KHASH_SET_INIT_STR(str)

typedef khash_t(str) attr_table;

typedef struct booksorter {
	attr_table *known_authors;
	attr_table *known_titles;
	attr_table *known_genres;
} booksorter;

booksorter *booksorter_init(void);
void booksorter_destroy(booksorter *bsr);

// Returns false if `attr` already existed.
bool attr_add(attr_table *attrs, const char *attr, bool allocate);

// Returns false if no.
bool attr_exist(attr_table *attrs, const char *attr);

#endif /* BOOKSORT_H_ */
