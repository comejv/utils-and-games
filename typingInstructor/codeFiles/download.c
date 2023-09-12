#include "download.h"

static size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int download_raw_file(const char *url, const char *output_dir)
{
    CURL *curl;
    FILE *fp;
    CURLcode res;

    curl = curl_easy_init();
    if (!curl)
    {
        verbose("[ERROR]: Failed to initialize libcurl\n");
        return 1;
    }

    // Create shortened file name from url
    char *output_file_name;
    char *last_slash = strrchr(url, '/');
    if (last_slash)
    {
        int file_len = strlen(url) - (last_slash - url);
        output_file_name = malloc(sizeof(char) * (file_len + 1));
        strncpy(output_file_name, last_slash + 1, file_len);
    }
    else
    {
        output_file_name = malloc(sizeof(char) * strlen(url));
        strcpy(output_file_name, url);
    }
    char *output_path = malloc(sizeof(char) * (strlen(output_dir) + strlen(output_file_name) + 1));
    sprintf(output_path, "%s/%s", output_dir, output_file_name);

    if (access(output_path, F_OK) == 0)
    {
        verbose("[INFO]: File already exists, not downloaded: %s\n", output_path);
        return 2;
    }

    fp = fopen(output_path, "wb");
    if (!fp)
    {
        verbose("[ERROR]: Failed to open output file: %s\n", output_path);
        return 1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
        verbose("[ERROR]: curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }

    fclose(fp);
    curl_easy_cleanup(curl);

    return res == CURLE_OK ? 0 : 1;
}
