#ifndef FILE_H_
#define FILE_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

bool is_folder(const char *folder_path);
bool is_file(const char *file_path);

// Returns true if successful.
bool write_file(const char *restrict file_path, const char *restrict content);
bool append_file(const char *restrict file_path, const char *restrict content);

const char *read_entire_file(const char *file_path);
size_t size_file(FILE *file);
#endif // FILE_H_
