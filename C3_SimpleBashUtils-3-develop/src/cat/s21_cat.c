#include "s21_cat.h"

int main(int argc, char *argv[]) {
  int count_flags = 0;

  // svbnet
  char possible_flags[] = "000000";
  parse_flags(argc, argv, possible_flags, &count_flags);

  FILE *filepointer;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      continue;
    }
    filepointer = fopen(argv[i], "r");

    if (filepointer == NULL) {
      printf("cat: %s: No such file or directory", argv[i]);
    } else {
      print_file_content(&filepointer, possible_flags);

      fclose(filepointer);
    }

    return 0;
  }
}

void parse_flags(int argc, char *argv[], char *result,
                 int *index_of_last_flag) {
  int getopt_result;
  // check exists long-flags
  static struct option long_options[] = {
      {"nubmer-nonblank", no_argument, 0, 'b'},
      {"number", no_argument, 0, 'n'},
      {"squeeze-blank", no_argument, 0, 's'},
      {0, 0, 0, 0}};

  while ((getopt_result =
              getopt_long(argc, argv, SHORT_FLAGS, long_options, NULL)) != -1) {
    (*index_of_last_flag)++;
    switch (getopt_result) {
      case 's':
        result[0] = '1';
        break;
      case 'v':
        result[1] = '1';
        break;
      case 'b':
        result[2] = '1';
        break;
      case 'n':
        result[3] = '1';
        break;
      case 'e':
        result[4] = '1';
        break;
      case 't':
        result[5] = '1';
        break;
    }
  }
}

void print_file_content(FILE **filepointer, char *possible_flags) {
  int c;
  int prev_was_newline = 0;
  int is_begin = 1;
  int count_lines = 1;
  char prew_char = '\n';
  int flag = 0;
  while ((c = fgetc(*filepointer)) != EOF) {
    if (c == '\n' && possible_flags[0] == '1') {
      prev_was_newline++;
      if (prev_was_newline > 2) {
        continue;
      }
    } else {
      prev_was_newline = 0;
    }
    if (c == '\t' && possible_flags[5] == '1') {
      printf("^I");
      continue;
    }
    if (((c <= 31 || c > 126) && (c != 9 && c != 10)) &&
        possible_flags[1] == '1') {
      printf("^%c",
             c + 64);  // print visible representation of non-printable char
      continue;
    }
    if (possible_flags[2] == '1') {
      flag = 1;
      if (!(prew_char == '\n' && c == '\n')) {
        if (is_begin) {
          printf("%6d\t", count_lines);
          count_lines++;
          is_begin = 0;
        }
        if (c == '\n') {
          is_begin = 1;
        }
      }
      prew_char = c;
    }
    if (possible_flags[4] == '1') {
      if (c == '\n') {
        printf("$");
      }
    }
    if (possible_flags[3] == '1' && (!flag)) {
      if (is_begin) {
        printf("%6d\t", count_lines);
        count_lines++;
        is_begin = 0;
      }
      if (c == '\n') {
        is_begin = 1;
      }
    }
    putchar(c);
  }
}
