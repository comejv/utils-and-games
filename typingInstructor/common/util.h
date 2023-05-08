#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

void set_VERBOSE(int value);
int get_VERBOSE();
void verbose(char *fmt, ...);
void freeStringArray(char **array);

#endif // UTIL_H
