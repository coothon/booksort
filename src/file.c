#include "include/file.h"

bool is_folder(const char *folder_path) {
	struct stat sb;
	return ((stat(folder_path, &sb) == 0) && S_ISDIR(sb.st_mode));
}

bool is_file(const char *file_path) {
	// Check if this file exists. A return value of 0 means yes, so we not it.
	return !access(file_path, F_OK);
}

bool write_file(const char *restrict file_path, const char *restrict content) {
	FILE *file = fopen(file_path, "w");
	if (!file)
		return false;

	fwrite((void *)content, sizeof(char), strlen(content), file);
	fclose(file);

	return true;
}

bool append_file(const char *restrict file_path, const char *restrict content) {
	if (!is_file(file_path))
		return false;

	FILE *file = fopen(file_path, "a");
	if (!file)
		return false;

	fwrite((void *)content, sizeof(char), strlen(content), file);
	fclose(file);

	return true;
}

const char *read_entire_file(const char *file_path) {
	if (!is_file(file_path))
		return NULL;

	FILE *file;

	file = fopen(file_path, "r");
	if (!file)
		return NULL;

	size_t file_size = size_file(file);

	void *file_contents = malloc(file_size + 1);
	if (!file_contents) {
		fclose(file);
		return NULL;
	}

	fseek(file, 0, SEEK_SET);
	fread(file_contents, sizeof(char), file_size, file);
	fclose(file);

	((char *)file_contents)[file_size] = '\0';
	return (const char *)file_contents;
}

size_t size_file(FILE *file) {
	fseek(file, 0, SEEK_END);
	return (size_t)ftell(file);
}
