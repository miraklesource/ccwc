#include "util.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static struct option long_options[] = {
    {"bytes", no_argument, 0, 'c'}, {"chars", no_argument, 0, 'm'},
    {"lines", no_argument, 0, 'l'}, {"words", no_argument, 0, 'w'},
    {"help", no_argument, 0, 'h'},  {0, 0, 0, 0},
};

int main(int argc, char *argv[]) {
  int opt;
  const char *filename = NULL;
  long byte_count;
  long line_count;
  long word_count;
  long char_count;
  int long_index = 0;

  while ((opt = getopt_long(argc, argv, "c:l:w:m:h", long_options,
                            &long_index)) != -1) {
    switch (opt) {
    case 'c':
      if (argc == 3) {
        filename = optarg;
        byte_count = count_bytes(filename);
        printf("%ld %s\n", byte_count, filename);

      } else if (argc == 2) {
        char *buffer = read_stdin_into_buffer();
        if (!buffer)
          return EXIT_FAILURE;

        byte_count = count_bytes_buffer(buffer);
        free(buffer);

        printf("%ld\n", byte_count);
      } else {
        fprintf(stderr, "Usage: ./ccwc -c <FILE>\n");
        return EXIT_FAILURE;
      }

      return EXIT_SUCCESS;

    case 'l':
      if (argc == 3) {
        filename = optarg;
        line_count = count_lines(filename);
        printf("%ld %s\n", line_count, filename);
      } else if (argc == 2) {
        char *buffer = read_stdin_into_buffer();
        if (!buffer)
          return EXIT_FAILURE;

        line_count = count_lines_buffer(buffer);
        free(buffer);
        printf("%ld\n", line_count);
      } else {
        fprintf(stderr, "Usage: ./ccwc -l <FILE>\n");
        return EXIT_FAILURE;
      }

      return EXIT_SUCCESS;

    case 'w':
      if (argc == 3) {
        filename = optarg;
        word_count = count_words(filename);
        printf("%ld %s\n", word_count, filename);
      } else if (argc == 2) {
        char *buffer = read_stdin_into_buffer();
        if (!buffer)
          return EXIT_FAILURE;

        word_count = count_words_buffer(buffer);
        free(buffer);

        printf("%ld\n", word_count);
      } else {
        fprintf(stderr, "Usage: ./ccwc -w <FILE>\n");
        return EXIT_FAILURE;
      }

      return EXIT_SUCCESS;

    case 'm':
      if (argc == 3) {
        filename = optarg;
        char_count = count_chars(filename);
        printf("%ld %s\n", char_count, filename);
      } else if (argc == 2) {
        char *buffer = read_stdin_into_buffer();
        if (!buffer)
          return EXIT_FAILURE;

        char_count = count_chars_buffer(buffer);
        free(buffer);

        printf("%ld\n", char_count);
      } else {
        fprintf(stderr, "Usage: ./ccwc -m <FILE>\n");
        return EXIT_FAILURE;
      }

      return EXIT_SUCCESS;

    case 'h':
      printf("Usage: ccwc [OPTION]... [FILE]\n");
      printf("  -c, --bytes   : number of bytes\n");
      printf("  -m, --chars   : number of characters (UTF-8 aware)\n");
      printf("  -l, --lines   : number of lines\n");
      printf("  -w, --words   : number of words\n");
      printf("  -h, --help    : display this help message\n");

      return EXIT_SUCCESS;

    case '?':
      fprintf(stderr, "Unknown option: -%c\n", optopt);
      return EXIT_FAILURE;

    case ':':
      fprintf(stderr, "Missing argument for -%c\n", optopt);
      return EXIT_FAILURE;
    }
  }

  // If there are no arguments, read from stdin
  if (argc == 1) {
    char *buffer = read_stdin_into_buffer();
    if (!buffer) {
      fprintf(stderr, "Error reading from stdin\n");
      return EXIT_FAILURE;
    }

    byte_count = count_bytes_buffer(buffer);
    line_count = count_lines_buffer(buffer);
    word_count = count_words_buffer(buffer);
    printf("  %ld  %ld %ld\n", byte_count, line_count, word_count);
    free(buffer);
    return EXIT_SUCCESS;
  }

  // Handle filename as single argument
  if (optind < argc) {
    filename = argv[optind];
    byte_count = count_bytes(filename);
    line_count = count_lines(filename);
    word_count = count_words(filename);
    printf("  %ld  %ld %ld %s\n", byte_count, line_count, word_count, filename);
    return EXIT_SUCCESS;
  }

  fprintf(stderr, "Usage: ./ccwc [OPTION]... [FILE]\n");
  return EXIT_FAILURE;
}
