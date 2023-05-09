#include "userInterface.h"

void check_screen_size()
{
    int max_x = getmaxx(stdscr);
    int max_y = getmaxy(stdscr);

    while (max_x < MIN_WIDTH || max_y < MIN_HEIGHT)
    {
        clear();
        mvprintw(max_y / 2 - 1, (max_x - 28) / 2,
                 "Current terminal size: %dx%d", max_x, max_y);
        mvprintw(max_y / 2, (max_x - 45) / 2,
                 "Please resize your terminal to at least %dx%d", MIN_WIDTH, MIN_HEIGHT);
        mvprintw(max_y / 2 + 1, (max_x - 25) / 2,
                 "Press any key to update...");
        max_x = getmaxx(stdscr);
        max_y = getmaxy(stdscr);
        getch();
    }
}

void print_menu(WINDOW *menu_win, int highlight, char *choices[], int n_choices)
{
    int x, y, i;

    y = 2;

    // Use wborder with explicit border characters
    wborder(menu_win, '|', '|', '-', '-', '+', '+',
            '+', '+');

    for (i = 0; i < n_choices; ++i)
    {
        // Center the text
        x = (getmaxx(menu_win) - strlen(choices[i])) / 2;

        // Highlight the current choice
        if (highlight == i + 1)
        {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        }
        else
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        ++y;
    }
    wrefresh(menu_win);
}

int menu_input(WINDOW *menu_win, int highlight, char *choices[], int n_choices)
{
    int c;
    while (1)
    {
        c = wgetch(menu_win);
        switch (c)
        {
        case KEY_UP:
            if (highlight == 1)
                highlight = n_choices;
            else
                --highlight;
            break;
        case KEY_DOWN:
            if (highlight == n_choices)
                highlight = 1;
            else
                ++highlight;
            break;
        case ENTER:
            return highlight;
        default:
            break;
        }
        print_menu(menu_win, highlight, choices, n_choices);
    }
}

int main_screen()
{
    clear();
    WINDOW *menu_win;
    int highlight = 1;

    char *choices[] = {
        "INSTRUCTOR",
        "INFORMATIONS",
        "SETTINGS",
        "EXIT",
    };
    int n_choices = sizeof(choices) / sizeof(char *);

    int screen_width = getmaxx(stdscr);
    int screen_height = getmaxy(stdscr);

    wbkgd(stdscr, COLOR_PAIR(1));
    mvprintw(screen_height / 5, (screen_width - 35) / 2, "Welcome to the Typing Instructor!");
    mvprintw(screen_height - 1, 0, "Use arrow keys to go up and down, press enter to select a choice");
    mvprintw(screen_height - 1, screen_width - 22, "(c) Côme VINCENT 2023");

    // Initialize menu window
    int box_width = 16;
    int box_height = n_choices + 4;

    int startx = (screen_width - box_width) / 2;
    int starty = (screen_height - box_height) / 2;

    menu_win = newwin(box_height, box_width, starty, startx - 1);
    keypad(menu_win, TRUE);
    wbkgd(menu_win, COLOR_PAIR(2));
    refresh();
    print_menu(menu_win, highlight, choices, n_choices);
    return menu_input(menu_win, highlight, choices, n_choices);
}

int language_screen()
{
    check_screen_size();

    clear();

    WINDOW *menu_win;
    int highlight = 1;

    char **choices = availableLanguages();

    int n_choices = sizeof(choices) / sizeof(char *);

    int screen_width = getmaxx(stdscr);
    int screen_height = getmaxy(stdscr);

    mvprintw(screen_height / 5, (screen_width - 25) / 2, "Please choose a language:");
    mvprintw(screen_height - 1, 0, "Use arrow keys to go up and down, press enter to select a choice");

    // Initialize menu window
    int box_width = 16;
    int box_height = n_choices + 4;

    int startx = (screen_width - box_width) / 2;
    int starty = (screen_height - box_height) / 2;

    menu_win = newwin(box_height, box_width, starty, startx - 1);
    keypad(menu_win, TRUE);
    wbkgd(menu_win, COLOR_PAIR(2));

    refresh();
    print_menu(menu_win, highlight, choices, n_choices);
    int ret = menu_input(menu_win, highlight, choices, n_choices);
    freeStringArray(choices);
    return ret;
}

void wprintFileContent(const char *filename, WINDOW *win)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        verbose("[ERROR]: Failed to open file %s\n", filename);
        return;
    }

    int lines = 0;
    int max_line_length = 0;
    char line[1024];

    // Get the number of lines
    while (fgets(line, sizeof(line), file))
    {
        lines++;
        int line_length = strlen(line);
        if (line_length > max_line_length)
        {
            max_line_length = line_length;
        }
    }

    // Print the file content
    win = newwin(lines, max_line_length, 0, 0);
    int current_line = 0;
    while (fgets(line, sizeof(line), file))
    {
        mvwprintw(win, current_line, 0, "%s", line);
        current_line++;
    }
    fclose(file);

    wrefresh(win);
}

int instructor_screen()
{
    int language = language_screen();

    clear();

    check_screen_size();

    WINDOW *file_win;
    WINDOW *text_win;
    WINDOW *scroller_win;
    WINDOW *stats_win;

    int screen_width = getmaxx(stdscr);
    int screen_height = getmaxy(stdscr);

    int file_choice = 0;

    char *stats_message = "WPM: 0 --- Accuracy: 0%";

    CodeFiles *files = getFiles(language);
    CodeFile file;
    file.language = files->files[file_choice].language;
    file.name = strdup(files->files[file_choice].name);
    file.path = strdup(files->files[file_choice].path);
    free(files->files);
    free(files);

    // Get file content
    wprintFileContent(file.path, text_win);

    file_win = newwin(screen_height - 1, 30, 0, 0);
    scroller_win = subwin(file_win, screen_height - 1, screen_width - 30, 0, 0);
    scrollok(scroller_win, TRUE);
    stats_win = newwin(1, screen_width, screen_height - 1, 0);

    wbkgd(file_win, COLOR_PAIR(1));
    wbkgd(scroller_win, COLOR_PAIR(0));
    wbkgd(stats_win, COLOR_PAIR(2));

    refresh();
    wrefresh(file_win);
    wrefresh(scroller_win);
    wrefresh(stats_win);

    // Initialise window contents
    mvwprintw(stats_win, 0, (screen_width - 23) / 2, stats_message);

    getch();

    return 0;
}

int info_screen()
{
    return 0;
}

int settings_screen()
{
    return 0;
}
