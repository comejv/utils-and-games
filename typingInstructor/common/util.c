#include "util.h"

static int VERBOSE = 0;

void set_VERBOSE(int value)
{
    VERBOSE = value;
}

int get_VERBOSE()
{
    return VERBOSE;
}

void verbose(char *fmt, ...)
{
    if (get_VERBOSE())
    {
        va_list ap;
        va_start(ap, fmt);
        vfprintf(stderr, fmt, ap);
        va_end(ap);
    }
}

void freeStringArray(char **array)
{
    for (int i = 0; array[i]; ++i)
    {
        free(array[i]);
    }
    free(array);
}
