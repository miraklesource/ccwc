#include "util.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long count_bytes(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening %s\n", filename);
        return -1;
    }
    
    long count = count_bytes_file(file);
    fclose(file);
    return count;
}

long count_lines(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening %s\n", filename);
        return -1;
    }
    long count = count_lines_file(file);
    fclose(file);
    return count;
}

long count_words(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening %s\n", filename);
        return -1;
    }

    long count = count_words_file(file);
    fclose(file);
    return count;
}

long count_chars(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening %s\n", filename);
        return -1;
    }
    long count = count_chars_file(file);
    fclose(file);
    return count;
}

long count_bytes_file(FILE* file) {
    long count = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }
    return count;
}

long count_lines_file(FILE* file) {
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    long count = 0;
    
    while ((read = getline(&line, &len, file)) != -1) {
        count++;
    }
    
    free(line);
    return count;
}

long count_words_file(FILE* file) {
    int last_was_whitespace = 1;
    long count = 0;
    int ch;
    
    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch)) {
            last_was_whitespace = 1;
        } else {
            if (last_was_whitespace)
                count++;
            last_was_whitespace = 0;
        }
    }
    return count;
}

long count_chars_file(FILE* file) {
    long count = 0;
    int ch;
    
    while ((ch = fgetc(file)) != EOF) {
        // Only count a new character if it is not a UTF-8 continuation byte
        if ((ch & 0xC0) != 0x80)
            count++;
    }
    
    return count;
}

long count_bytes_buffer(const char* buffer) {
    return strlen(buffer);
}

long count_lines_buffer(const char* buffer) {
    long count = 0;
    for (const char* p = buffer; *p; p++) {
        if (*p == '\n')
            count++;
    }
    
    return count;
}

long count_words_buffer(const char* buffer) {
    int in_word = 0;
    long count = 0;
    
    for (const char* p = buffer; *p; p++) {
        if (isspace((unsigned char) *p)) {
            in_word = 0;
        } else if (!in_word) {
            count++;
            in_word = 1;
        }
    }
    
    return count;
}

long count_chars_buffer(const char* buffer) {
    long count = 0;
    for (const unsigned char* p = (const unsigned char*) buffer; *p; p++) {
        if ((*p & 0xC0) != 0x80)
            count++;
    }
    
    return count;
}

char* read_stdin_into_buffer(void) {
    size_t size = 0;
    size_t capacity = 1024;
    char* buffer = malloc(capacity);
    if (!buffer)
        return NULL;

    int ch;
    
    while ((ch = fgetc(stdin)) != EOF) {
        if (size + 1 >= capacity) {
            capacity *= 2;
            char* new_buf = realloc(buffer, capacity);
            if (!new_buf) {
                free(buffer);
                return NULL;
            }
            buffer = new_buf;
        }
        
        buffer[size++] = ch;
    }

    buffer[size] = '\0';
    return buffer;
}
