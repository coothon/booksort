#ifndef BOOKSORT_PERSISTENT_H_
#define BOOKSORT_PERSISTENT_H_

#define _DEFAULT_SOURCE 1
#include <string.h>

#include <json-c/json.h>

#include "vec.h"

#include "book.h"
#include "booksort.h"
#include "file.h"

#define DATABASE_FILE_PATH "./persistent.json"

// Serialized representation of `book`.
typedef struct serial_book {
	const char *title;
	const char *author;
	const char *genre;
	size_t copies;
} serial_book;

typedef vec_t(serial_book *) sbook_vec_t;

const char *serialize_books(const booksorter *bsr);
bool serialize_into_file(const char *file_path, const booksorter *bsr);
booksorter *deserialize_books(const char *json_data);

#endif /* BOOKSORT_PERSISTENT_H_ */
