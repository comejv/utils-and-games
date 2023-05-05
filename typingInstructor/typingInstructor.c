#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include "interface/userInterface.h"
#include "curl/download.h"
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
    int num_urls;
    char **urls = read_urls_from_file("data/code_sources.conf", &num_urls);

    // Check that folder exists
    struct stat sb;
    char folder[] = "data/code_examples";
    if (stat(folder, &sb) == -1)
    {
        mkdir("data/code_examples", 0777);
        verbose("INFO: Created data/code_examples\n");
    }

    // Download urls
    int i;
    for (i = 0; i < num_urls; ++i)
    {
        download_raw_file(urls[i], "data/code_examples");
        verbose("INFO: Downloaded %s\n", urls[i]);
    }

    // Initialize curses
    initscr();
    clear();
    noecho();
    cbreak();
    start_color();
    curs_set(0);

    check_screen_size();

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
}