#include "include/booksort.h"

booksorter *booksorter_init(void) {
	booksorter *bsr = malloc(sizeof(booksorter));
	if (!bsr)
		return NULL;

	bsr->known_authors = kh_init_str();
	if (!bsr->known_authors)
		return NULL;
	bsr->known_titles = kh_init_str();
	if (!bsr->known_titles)
		return NULL;
	bsr->known_genres = kh_init_str();
	if (!bsr->known_genres)
		return NULL;

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

	free(bsr);
}

bool attr_add(attr_table *attrs, const char *attr, bool allocate) {
	int absent = 0;

	khint_t iter = kh_put_str(attrs, attr, &absent);
	if (!absent || absent == -1)
		return false;

	// Allocate key to ensure validity later.
	if (allocate)
		kh_key(attrs, iter) = strdup(attr);

	return true;
}

bool attr_exist(attr_table *attrs, const char *attr) {
	return kh_end(attrs) != kh_get_str(attrs, attr);
}
