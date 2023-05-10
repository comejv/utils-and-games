#include "userInterface.h"

void check_screen_size(int min_width, int min_height)
{
    int max_x = getmaxx(stdscr);
    int max_y = getmaxy(stdscr);

    min_width = min_width ? min_width : MIN_WIDTH;
    min_height = min_height ? min_height : MIN_HEIGHT;

    while (max_x < min_width || max_y < min_height)
    {
        clear();
        mvprintw(max_y / 2 - 1, (max_x - 28) / 2,
                 "Current terminal size: %dx%d", max_x, max_y);
        mvprintw(max_y / 2, (max_x - 45) / 2,
                 "Please resize your terminal to at least %dx%d", min_width, min_height);
        mvprintw(max_y / 2 + 1, (max_x - 25) / 2,
                 "Press any key to update...");
        max_x = getmaxx(stdscr);
        max_y = getmaxy(stdscr);
        wgetch(stdscr);
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

    keypad(menu_win, TRUE);

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
            refresh();
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
    wbkgd(menu_win, COLOR_PAIR(2));
    refresh();
    print_menu(menu_win, highlight, choices, n_choices);
    return menu_input(menu_win, highlight, choices, n_choices);
}

int language_screen()
{
    check_screen_size(0, 0);

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
    wbkgd(menu_win, COLOR_PAIR(2));

    refresh();
    print_menu(menu_win, highlight, choices, n_choices);
    int ret = menu_input(menu_win, highlight, choices, n_choices);
    freeStringArray(choices);
    return ret;
}

size_t wprintFileContent(const char *filepath, WINDOW **win, int pad_width)
{
    FILE *file = fopen(filepath, "r");
    if (!file)
    {
        verbose("[ERROR]: Failed to open file %s\n", filepath);
        return 0;
    }

    char *line = NULL;
    size_t len = 0;

    // Count number of lines in file
    size_t num_lines = count_lines(file);

    fseek(file, 0, SEEK_SET);

    // Initialize pad
    *win = newpad(num_lines + 7, pad_width);

    int current_line = 4;
    // Print file name
    mvwprintw(*win, current_line, (pad_width - strlen(filepath)) / 2, "%s", filepath);
    current_line += 3;
    // Print file content
    while (getline(&line, &len, file) != -1)
    {
        mvwprintw(*win, current_line++, 0, "%s", line);
    }
    fclose(file);
    free(line);

    return num_lines;
}

int instructor_screen()
{
    int language = language_screen();

    clear();

    WINDOW *file_browse_win;
    WINDOW *code_win;
    WINDOW *stats_win;

    int screen_width = getmaxx(stdscr);
    int screen_height = getmaxy(stdscr);
    int file_browse_win_width = 30;
    int code_win_width = screen_width - file_browse_win_width;

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
    int num_lines = wprintFileContent(file.path, &code_win, code_win_width);

    file_browse_win = newwin(screen_height - 1, file_browse_win_width, 0, 0);
    stats_win = newwin(1, screen_width, screen_height - 1, 0);

    wbkgd(stdscr, COLOR_PAIR(0));
    wbkgd(file_browse_win, COLOR_PAIR(1));
    wbkgd(code_win, COLOR_PAIR(0));
    wbkgd(stats_win, COLOR_PAIR(2));

    // Initialise window contents
    mvwprintw(stats_win, 0, (screen_width - 23) / 2, "%s", stats_message);

    refresh();
    prefresh(code_win, 0, 0, 0, file_browse_win_width, screen_height - 2, screen_width - 1);
    wrefresh(file_browse_win);
    wrefresh(stats_win);

    int c;

    while ((c = getch()) != KEY_BACKSPACE)
    {
        static int pad_top_line = 0;
        switch (c)
        {
        case 'a':
            if (pad_top_line > 0)
            {
                pad_top_line--;
                prefresh(code_win, pad_top_line, 0, 0, file_browse_win_width, screen_height - 2, screen_width - 1);
            }
            break;
        case 'z':
            if (pad_top_line < num_lines + 7 - screen_height - 1)
            {
                pad_top_line++;
                prefresh(code_win, pad_top_line, 0, 0, file_browse_win_width, screen_height - 2, screen_width - 1);
            }
            break;
        default:
            break;
        }
    }

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
