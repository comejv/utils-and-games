#ifndef FILESYS_H
#define FILESYS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>


#include "../common/util.h"

#define ALL_LANG -1
#define UNKOWN_LANG 0
#define C_LANG 1
#define PY_LANG 2
#define RS_LANG 3

#define NUM_LANG 3

typedef struct
{
    char *path;
    int language;
    char *name;
} CodeFile;

typedef struct
{
    CodeFile *files;
    int num_files;
} CodeFiles;

char **readUrlsFromFile(const char *file_path, int *num_urls);
void readDir(char *dirPath);
CodeFiles *getFiles(int language);
char **availableLanguages();
void freeFiles(CodeFiles *files);

#endif // FILESYS_H
