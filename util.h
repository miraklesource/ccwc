#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

long count_bytes(const char* filename);
long count_lines(const char* filename);
long count_words(const char* filename);
long count_chars(const char* filename);

long count_bytes_file(FILE* file);
long count_lines_file(FILE* file);
long count_words_file(FILE* file);
long count_chars_file(FILE* file);

long count_bytes_buffer(const char* buffer);
long count_lines_buffer(const char* buffer);
long count_words_buffer(const char* buffer);
long count_chars_buffer(const char* buffer);

char* read_stdin_into_buffer(void);

#endif
