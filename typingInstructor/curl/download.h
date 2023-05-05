#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "../common/util.h"

char **read_urls_from_file(const char *file_path, int *num_urls);
int download_raw_file(const char *url, const char *output_path);

#endif // DOWNLOAD_H
