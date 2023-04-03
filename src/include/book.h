#ifndef BOOKSORT_BOOK_H_
#define BOOKSORT_BOOK_H_

#include <stdlib.h>

#include "booksort.h"

typedef struct book {
	khint_t title_iter;
	khint_t author_iter;
	khint_t genre_iter;
} book;

#endif /* BOOKSORT_BOOK_H_ */
