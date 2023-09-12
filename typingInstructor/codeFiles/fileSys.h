#ifndef FILESYS_H
#define FILESYS_H

#include <stdlib.h>
#include <stdint.h>
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

// Parse urls from file and modify num_urls
char **readUrlsFromFile(const char *file_path, int *num_urls);

// Scan a directory and update G_Files with what's inside
void readDir(char *dirPath);

// Get list of available files in a languages
// language: 0 = all, 1 = C, 2 = Python, 3 = Rust
// See defines in fileSys.h
CodeFiles *getFiles(int language);

// Get list of all available languages
char **availableLanguages();

// Free a CodeFiles
void freeFiles(CodeFiles *files);

#endif // FILESYS_H
