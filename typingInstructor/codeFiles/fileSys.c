#include "fileSys.h"

static CodeFiles *G_files = NULL;
static char langExt[NUM_LANG][4] = {"c", "py", "rs"};

char **readUrlsFromFile(const char *file_path, int *num_urls)
{
    FILE *fp;
    char **urls = NULL;
    char line[512];
    int count = 0;

    fp = fopen(file_path, "r");
    if (!fp)
    {
        verbose("[WARNING]: Failed to open input file: %s\n", file_path);
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

void readDir(char *dirPath)
{
    DIR *d;
    struct dirent *file;
    d = opendir(dirPath);
    if (!d)
    {
        verbose("[ERROR]: Failed to open data directory\n");
        return;
    }

    if (!G_files)
    {
        G_files = (CodeFiles *)malloc(sizeof(CodeFiles));
        G_files->num_files = 0;
        G_files->files = NULL;
    }

    verbose("[INFO]: Reading files...\n");
    while ((file = readdir(d)) != NULL)
    {
        if (file->d_type != DT_REG)
            continue;

        verbose("[INFO]: Found file: %s\n", file->d_name);

        // Create file object
        CodeFile *cf = (CodeFile *)malloc(sizeof(CodeFile));

        // Allocate and fill in path
        cf->path = malloc(sizeof(char) * (21 + strlen(file->d_name) + 1));
        sprintf(cf->path, "./data/code_examples/%s", file->d_name);

        // Find file extension and use as language
        cf->language = UNKOWN_LANG;
        char *ext = strrchr(cf->path, '.');
        if (ext)
        {
            for (int i = 0; i < NUM_LANG; ++i)
            {
                if (strcmp(ext + 1, langExt[i]) == 0)
                {
                    cf->language = i + 1;
                    break;
                }
            }
            if (!cf->language)
            {
                verbose("[WARNING]: Unknown language: %s\n", cf->path);
            }
        }
        else
        {
            verbose("[WARNING]: No extension: %s\n", cf->path);
        }

        // Allocate and fill in name
        cf->name = malloc(sizeof(char) * (strlen(file->d_name) + 1));
        strcpy(cf->name, file->d_name);

        // Add to files
        G_files->files = realloc(G_files->files, (G_files->num_files + 1) * sizeof(CodeFile));
        G_files->files[G_files->num_files++] = *cf;
    }
}

CodeFiles *getFiles(int language)
{
    if (!G_files)
    {
        verbose("[ERROR]: No files found\n");
        return NULL;
    }
    if (language == ALL_LANG)
        return G_files;

    CodeFiles *cf = (CodeFiles *)malloc(sizeof(CodeFiles));
    cf->num_files = 0;
    cf->files = NULL;

    for (int i = 0; i < G_files->num_files; ++i)
    {
        if (G_files->files[i].language == language)
        {
            cf->files = realloc(cf->files, (cf->num_files + 1) * sizeof(CodeFile));
            cf->files[cf->num_files++] = G_files->files[i];
        }
    }
    return cf;
}

char **availableLanguages()
{
    u_int32_t l = 0;

    // Find languages without keeping duplicates
    // By ORing the bit with position = language num
    for (int i = 0; i < G_files->num_files; ++i)
    {
        l |= 1 << G_files->files[i].language;
    }

    // Allocate and fill in languages
    unsigned int count = 0, i = 0;
    char **languages = NULL;

    while (l)
    {
        if (l & 1)
        {
            languages = realloc(languages, (++count) * sizeof(char *));
            languages[count - 1] = strdup(langExt[i - 1]);
        }
        l >>= 1;
        i++;
    }
    return languages;
}

void freeFiles(CodeFiles *files)
{
    if (files)
    {
        for (int i = 0; i < files->num_files; ++i)
        {
            free(files->files[i].path);
            free(files->files[i].name);
        }
        free(files->files);
        free(files);
    }
}
