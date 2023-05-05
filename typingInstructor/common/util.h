#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdarg.h>

void set_VERBOSE(int value);
int get_VERBOSE();
void verbose(char *fmt, ...);

#endif // UTIL_H
