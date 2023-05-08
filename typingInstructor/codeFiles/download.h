#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <curl/curl.h>
#include "../common/util.h"

int download_raw_file(const char *url, const char *output_path);

#endif // DOWNLOAD_H
