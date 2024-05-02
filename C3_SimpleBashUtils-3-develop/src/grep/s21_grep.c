#include "flags_and_functions.h"

int main(int argc, char* argv[]) {
  if (argc == 1) {
    return 0;
  }
  struct Flags all_flags = {0};

  char* patterns = (char*)calloc(1024, sizeof(char));
  char* files = (char*)calloc(1024, sizeof(char));
  parse_flags(argc, argv, &all_flags, patterns, files);

  int files_occured = count_occurrenses(files, '|');

  if (all_flags.e || all_flags.f) {
    patterns[strlen(patterns) - 1] = '\0';
  }
  // passed each file to find_in_file
  char delimetr[] = "|";
  char* filename = strtok(files, delimetr);

  while (filename != NULL) {
    find_in_files(filename, files_occured, &all_flags, patterns);
    filename = strtok(NULL, delimetr);
  }

  free(patterns);
  free(files);
  return 0;
}
