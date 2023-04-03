#include "include/booksort.h"

booksorter *booksorter_init(void) {
	booksorter *bsr = malloc(sizeof(booksorter));
	if (!bsr)
		return NULL;

	bsr->known_authors = kh_init_str();
	if (!bsr->known_authors) {
		free(bsr);
		return NULL;
	}
	bsr->known_titles = kh_init_str();
	if (!bsr->known_titles) {
		kh_destroy_str(bsr->known_authors);
		free(bsr);
		return NULL;
	}
	bsr->known_genres = kh_init_str();
	if (!bsr->known_genres) {
		kh_destroy_str(bsr->known_authors);
		kh_destroy_str(bsr->known_titles);
		free(bsr);
		return NULL;
	}

	vec_init(&bsr->all_books);

	return bsr;
}

static void attrs_free_keys(attr_table *attrs) {
	if (!attrs)
		return;

	for (khint_t i = kh_begin(attrs); i != kh_end(attrs); ++i) {
		if (!kh_exist(attrs, i))
			continue;
		free(kh_key(attrs, i));
	}
}

// Assume all keys are heap-allocated (as they should be).
void booksorter_destroy(booksorter *bsr) {
	if (!bsr)
		return;

	attrs_free_keys(bsr->known_authors);
	kh_destroy_str(bsr->known_authors);

	attrs_free_keys(bsr->known_titles);
	kh_destroy_str(bsr->known_titles);

	attrs_free_keys(bsr->known_genres);
	kh_destroy_str(bsr->known_genres);


	book *b_i = NULL;
	int i = 0;
	// Free all books.
	vec_foreach(&bsr->all_books, b_i, i) {
		if (b_i)
			free(b_i);
	}

	vec_deinit(&bsr->all_books);

	free(bsr);
}

bool attr_add(attr_table *attrs, const char *attr) {
	if (!(attrs && attr))
		return false;

	int absent = 0;

	khint_t iter = kh_put_str(attrs, attr, &absent);
	if (!absent || absent == -1)
		return false;

	// Allocate key to ensure validity later.
	kh_key(attrs, iter) = strdup(attr);

	return true;
}

bool attr_exist(const attr_table *attrs, const char *attr) {
	if (!(attrs && attr))
		return NULL;

	return kh_end(attrs) != kh_get_str(attrs, attr);
}

khint_t attr_try_add(attr_table *attrs, const char *attr) {
	if (!(attrs && attr))
		return 0;

	khint_t i = kh_get_str(attrs, attr);

	// Already existed.
	if (i != kh_end(attrs))
		return i;

	int absent = 0;
	i = kh_put_str(attrs, attr, &absent);

	// Error.
	if (absent == -1)
		return kh_end(attrs);

	// Allocate on the heap, for consistency.
	kh_key(attrs, i) = strdup(attr);

	return i;
}

book *find_book(const booksorter *bsr, const book *b) {
	if (!(bsr && b))
		return NULL;

	book *b_i = NULL;
	int i = 0;

	// Scan for copies.
	vec_foreach(&bsr->all_books, b_i, i) {
		if (book_compare(b, b_i))
			return b_i;
	}

	return NULL;
}

book *add_book(booksorter *bsr, const char *restrict title,
               const char *restrict author, const char *restrict genre) {
	if (!(bsr && title && author && genre))
		return NULL;

	khint_t title_i = attr_try_add(bsr->known_titles, title);
	if (title_i == kh_end(bsr->known_titles))
		return NULL;

	khint_t author_i = attr_try_add(bsr->known_authors, author);
	if (author_i == kh_end(bsr->known_authors))
		return NULL;

	khint_t genre_i = attr_try_add(bsr->known_genres, genre);
	if (genre_i == kh_end(bsr->known_genres))
		return NULL;

	// For comparing.
	book tmp = {
		.title_iter = title_i,
		.author_iter = author_i,
		.genre_iter = genre_i,
		1,
	};

	// Search for the book.
	book *find = find_book(bsr, &tmp);
	if (find) {
		++find->copies;
		return find;
	}

	// Copy `tmp` to the heap.
	book *new_book = malloc(sizeof(book));
	if (!new_book)
		return NULL;
	memcpy(new_book, &tmp, sizeof(book));

	vec_push(&bsr->all_books, new_book);

	return new_book;
}

bool remove_book(booksorter *bsr, book *copy) {
	if (!(bsr && copy))
		return false;

	book *found = find_book(bsr, copy);
	if (!found)
		return false;

	// Remove only one.
	if (found->copies > 1) {
		--found->copies;
		return true;
	}

	free(found);
	vec_remove(&bsr->all_books, found);
	return true;
}
