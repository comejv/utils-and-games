#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/statfs.h>
#include <stdio.h>
#include <stdarg.h>

// Set global VERBOSE value
// 0 means nothing is printed to stderr
// anything else means verbose output to stderr
void set_VERBOSE(int value);

// Get global VERBOSE state
int get_VERBOSE();

// Print to stderr if VERBOSE
void verbose(char *fmt, ...);

// Free an array of strings
void freeStringArray(char **array);

// Count number of lines in a file
size_t count_lines(FILE *fp);

#endif // UTIL_H
