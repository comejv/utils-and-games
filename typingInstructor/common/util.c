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

size_t count_lines(FILE *fp)
{
    struct statfs fsInfo = {0};
    int fd = fileno(fp);
    long optimalSize;
    size_t line_count = 0;

    if (fstatfs(fd, &fsInfo) == -1)
    {
        optimalSize = 4 * 1024 * 1024;
    }
    else
    {
        optimalSize = fsInfo.f_bsize;
    }

    char *buffer = malloc(optimalSize);
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, optimalSize, fp)) > 0)
    {
        for (size_t i = 0; i < bytesRead; i++)
        {
            if (buffer[i] == '\n')
            {
                line_count++;
            }
        }
    }

    free(buffer);
    return line_count;
}
