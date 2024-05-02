#ifndef FLAGS_AND_FUNCTIONS
#define FLAGS_AND_FUNCTIONS

#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define flags "e:ivclnhsf:o"

struct Flags {
  bool e;
  bool i;
  bool v;
  bool c;
  bool l;
  bool n;
  bool h;
  bool s;
  bool f;
  bool o;
};

void parse_flags(int argc, char* argv[], struct Flags* passed_flags,
                 char* patterns, char* files);
void find_in_files(char* filename, int files_occurences,
                   struct Flags* passed_flags, char* pattern);
int count_occurrenses(char* str, char target);

#endif
