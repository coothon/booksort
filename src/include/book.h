#ifndef BOOKSORT_BOOK_H_
#define BOOKSORT_BOOK_H_

#include <stdbool.h>
#include <stdlib.h>

#include "khash.h"

typedef struct book {
	// Iterator in `booksorter.known_titles`.
	khint_t title_iter;
	// Iterator in `booksorter.known_authors`.
	khint_t author_iter;
	// Iterator in `booksorter.known_genres`.
	khint_t genre_iter;

	// In case there are multiple copies, just "fold" them.
	size_t copies;
} book;

// Returns true if they contain the same data.
bool book_compare(const book *one, const book *two);

#endif /* BOOKSORT_BOOK_H_ */
