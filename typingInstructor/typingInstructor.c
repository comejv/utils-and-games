#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include "interface/userInterface.h"
#include "codeFiles/download.h"
#include "codeFiles/fileSys.h"
#include "common/util.h"

int main(int argc, char *argv[])
{
    // Parse arguments
    char c;
    while ((c = getopt(argc, argv, "hv")) != -1)
    {
        switch (c)
        {
        case 'v':
            set_VERBOSE(1);
            break;
        case 'h':
            printf("Usage: %s [-vh]\n", argv[0]);
            printf("\t-v\tVerbose output to stderr\n");
            printf("\t-h\tPrint this message\n");
            return 0;
        default:
            break;
        }
    }

    // Read code urls from conf file
    int num_urls = 0;
    verbose("[INFO]: Reading urls from conf file...\n");
    char **urls = readUrlsFromFile("data/code_sources.conf", &num_urls);
    if (!num_urls)
    {
        verbose("[WARNING]: No url read from conf file\n");
    }

    // Check that folder exists
    struct stat sb;
    char folder[] = "data/code_examples";
    if (stat(folder, &sb) == -1)
    {
        mkdir("data/code_examples", 0777);
        verbose("[INFO]: Created data/code_examples\n");
    }

    // Download urls
    for (int i = 0; i < num_urls; ++i)
    {
        download_raw_file(urls[i], folder);
        verbose("[INFO]: Downloaded %s\n", urls[i]);
    }

    // Update file sys
    verbose("[INFO]: Updating file system with %s...\n", folder);
    readDir(folder);

    // Clean up
    freeStringArray(urls);
    system("clear");

    // Initialize curses
    initscr();
    clear();
    noecho();
    cbreak();
    start_color();
    curs_set(0);

    // Check screen size and colour support
    check_screen_size(0, 0);
    if (has_colors() == TRUE)
    {
        // Set colors
        init_pair(0, COLOR_BLACK, COLOR_WHITE);
        init_pair(1, COLOR_WHITE, COLOR_CYAN);
        init_pair(2, COLOR_BLACK, COLOR_RED);
    }
    else
    {
        verbose("[WARNING]: Colours are not supported by your terminal\n");
    }

    int menu = 0;
    while ((menu = main_screen()) != 4)
    {
        switch (menu)
        {
        case 1:
            instructor_screen();
            break;
        case 2:
            info_screen();
            break;
        case 3:
            settings_screen();
            break;
        default:
            break;
        }
    }
    endwin();

    freeFiles(getFiles(ALL_LANG));

    return 0;
}