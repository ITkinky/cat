#include "flags_and_functions.h"

void get_pattern_from_file(char* filename, char* target_to_write_pattern) {
  FILE* filepointer;
  filepointer = fopen(filename, "r");
  if (filepointer == NULL) {
    printf("%s: No such file or directory", filename);
    exit(1);
  }
  fgets(target_to_write_pattern, sizeof(target_to_write_pattern), filepointer);
  fclose(filepointer);
}
int count_occurrenses(char* str, char target) {
  int result = 0;
  int i = 0;
  while (str[i] != '\0') {
    if (str[i] == target) {
      result++;
    }
    i++;
  }
  return result;
}

void print_line(int files_occurences, char* filename, char* line,
                bool is_h_flag) {
  if (files_occurences == 1 || is_h_flag == 1) {
    printf("%s", line);
  } else {
    printf("%s:%s", filename, line);
  }
}

void parse_flags(int argc, char* argv[], struct Flags* passed_flags,
                 char* patterns, char* files) {
  int getopt_result = 0;

  while ((getopt_result = getopt(argc, argv, flags)) != -1) {
    switch (getopt_result) {
      case 'e':
        passed_flags->e = true;
        strcat(patterns, optarg);
        strcat(patterns, "|");
        break;
      case 'i':
        passed_flags->i = true;
        break;
      case 'v':
        passed_flags->v = true;
        break;
      case 'c':
        passed_flags->c = true;
        break;
      case 'l':
        passed_flags->l = true;
        break;
      case 'n':
        passed_flags->n = true;
        break;
      case 'h':
        passed_flags->h = true;
        break;
      case 's':
        passed_flags->s = true;
        break;
      case 'f':
        passed_flags->f = true;
        get_pattern_from_file(optarg, patterns);
        strcat(patterns, "|");
        break;
      case 'o':
        passed_flags->o = true;
        break;
    }
  }
  if (passed_flags->e != true && passed_flags->f != true) {
    strcpy(patterns, argv[optind]);
    optind += 1;
  }
  while (optind < argc) {
    strcat(files, argv[optind++]);
    strcat(files, "|");
  }
}

void find_in_files(char* filename, int files_occurences,
                   struct Flags* passed_flags, char* pattern) {
  FILE* filepointer;
  filepointer = fopen(filename, "r");

  if (filepointer == NULL && passed_flags->s == false) {
    printf("%s: No such file or directory", filename);
    exit(1);
  } else if (passed_flags->s == true && filepointer == NULL) {
    exit(1);
  }

  regex_t regex;
  int regex_flags = REG_EXTENDED;
  if (passed_flags->i) {
    regex_flags |= REG_ICASE;
  }

  if (regcomp(&regex, pattern, regex_flags) != 0) {
    printf("Regex compile error");
    exit(1);
  }

  regmatch_t matches[1];
  char line[4096] = {0};
  int line_counter_for_c = 0;
  int line_counter_for_n = 0;
  int is_l_true = 0;
  while (fgets(line, sizeof(line), filepointer)) {
    line_counter_for_n++;
    if (((regexec(&regex, line, 1, matches, 0) == 0) && passed_flags->v == 0) ||
        ((regexec(&regex, line, 0, NULL, 0) != 0) && passed_flags->v != 0)) {
      if (passed_flags->o) {
        for (int i = matches[0].rm_so; i < matches[0].rm_eo; i++) {
          putchar(line[i]);
        }
        printf("\n");
        continue;
      }
      line_counter_for_c++;
      if (passed_flags->l) {
        is_l_true = true;
        break;
      }
      if (passed_flags->c) {
        continue;
      }
      if (passed_flags->n) {
        printf("%d:", line_counter_for_n);
      }
      print_line(files_occurences, filename, line, passed_flags->h);
    }
  }

  if (passed_flags->c) {
    if (files_occurences == 1) {
      printf("%d\n", line_counter_for_c);
    } else {
      printf("%s:%d\n", filename, line_counter_for_c);
    }
  }
  if (is_l_true) printf("%s\n", filename);

  regfree(&regex);
  fclose(filepointer);
}
