#ifndef BOOKSORT_H_
#define BOOKSORT_H_

#define _DEFAULT_SOURCE 1
#include <stdbool.h>
#include <string.h>

#include "khash.h"
KHASH_SET_INIT_STR(str)

#include "book.h"
#include "vec.h"

typedef khash_t(str) attr_table;
typedef vec_t(book *) book_vec_t;

typedef struct booksorter {
	attr_table *known_authors;
	attr_table *known_titles;
	attr_table *known_genres;

	book_vec_t all_books;
} booksorter;

booksorter *booksorter_init(void);
void booksorter_destroy(booksorter *bsr);

// Returns false if `attr` already existed.
bool attr_add(attr_table *attrs, const char *attr);

bool attr_exist(const attr_table *attrs, const char *attr);

// Returns index in `attrs`, or `kh_end(attrs)`.
khint_t attr_try_add(attr_table *attrs, const char *attr);

// Returns match to `b` in `bsr->all_books`, or NULL.
book *find_book(const booksorter *bsr, const book *b);

// Returns created/found book, or NULL.
book *add_book(booksorter *bsr, const char *restrict title,
               const char *restrict author, const char *restrict genre);

// Returns false if book could not be removed (e.g., doesn't exist).
bool remove_known_book(booksorter *bsr, book *copy);
bool remove_book(booksorter *bsr, const char *restrict title,
                 const char *restrict author, const char *restrict genre);

#endif /* BOOKSORT_H_ */
