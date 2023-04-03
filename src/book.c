#include "include/book.h"

bool book_compare(const book *one, const book *two) {
	// Just ignore NULL books.
	if (!(one && two))
		return false;

	// Check first if they point to the same memory.
	if (one == two)
		return true;

	if (one->title_iter != two->title_iter)
		return false;
	if (one->author_iter != two->author_iter)
		return false;
	if (one->genre_iter != two->genre_iter)
		return false;

	// They are identical copies.
	return true;
}
