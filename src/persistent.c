#include "include/persistent.h"

serial_book *serialize_book(const booksorter *bsr, const book *b) {
	if (!(bsr && b))
		return NULL;

	serial_book *sb = malloc(sizeof(serial_book));
	if (!sb)
		return NULL;

	sb->title = kh_key(bsr->known_titles, b->title_iter);
	sb->author = kh_key(bsr->known_authors, b->author_iter);
	sb->genre = kh_key(bsr->known_genres, b->genre_iter);
	if (!(sb->title && sb->author && sb->genre)) {
		free(sb);
		return NULL;
	}
	sb->copies = b->copies;

	return sb;
}

const char *serialize_books(const booksorter *bsr) {
	struct json_object *json_arr = json_object_new_array();

	/* JSON serialization. */ {
		book *b_i = NULL;
		int i = 0;
		vec_foreach(&bsr->all_books, b_i, i) {
			struct json_object *json_obj = json_object_new_object();
			json_object_object_add(json_obj, "title",
			                       json_object_new_string(kh_key(
									   bsr->known_titles, b_i->title_iter)));
			json_object_object_add(json_obj, "author",
			                       json_object_new_string(kh_key(
									   bsr->known_authors, b_i->author_iter)));
			json_object_object_add(json_obj, "genre",
			                       json_object_new_string(kh_key(
									   bsr->known_genres, b_i->genre_iter)));
			json_object_array_add(json_arr, json_obj);
		}
	}

	// JSON manages its own memory, so it will invalidate the string after we
	// free the object. Must be copied.
	const char *serial_str = strdup(json_object_to_json_string(json_arr));

	// Free the JSON object.
	json_object_put(json_arr);

	return serial_str;
}

bool serialize_into_file(const char *file_path, const booksorter *bsr) {
	if (!(file_path && bsr))
		return false;

	const char *serial_data = serialize_books(bsr);
	if (!serial_data)
		return false;

	if (!write_file(file_path, serial_data)) {
		free(serial_data);
		return false;
	}

	free(serial_data);
	return true;
}

// serial_data *deserialize_books(const char *persistent);
