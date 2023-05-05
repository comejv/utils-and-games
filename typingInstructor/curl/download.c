#include "download.h"

char **read_urls_from_file(const char *file_path, int *num_urls)
{
    FILE *fp;
    char **urls = NULL;
    char line[512];
    int count = 0;

    fp = fopen(file_path, "r");
    if (!fp)
    {
        verbose("Failed to open input file: %s\n", file_path);
        return NULL;
    }

    while (fgets(line, sizeof(line), fp))
    {
        ++count;
        urls = realloc(urls, count * sizeof(char *));
        urls[count - 1] = strdup(line);
        // Remove newline
        urls[count - 1][strlen(line) - 1] = '\0';
    }

    fclose(fp);
    *num_urls = count;
    return urls;
}

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
        verbose("Failed to initialize libcurl\n");
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

    fp = fopen(output_path, "wb");
    if (!fp)
    {
        verbose("Failed to open output file: %s\n", output_path);
        return 1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
        verbose("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }

    fclose(fp);
    curl_easy_cleanup(curl);

    return res == CURLE_OK ? 0 : 1;
}
