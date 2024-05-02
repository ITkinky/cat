#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_READ 1024
#define SHORT_FLAGS_QUANTITY 5
#define SHORT_FLAGS "bsnetv"
#define LONG_FLAGS_QUANTITY 3

void parse_flags(int argc, char *argv[], char *result, int *index_of_last_flag);
void print_file_content(FILE **filepointer, char *possible_flags);
void parse_flags(int argc, char *argv[], char *result, int *index_of_last_flag);
