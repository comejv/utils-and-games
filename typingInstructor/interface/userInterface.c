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

    // Set colors
    init_pair(1, COLOR_WHITE, COLOR_CYAN);
    init_pair(2, COLOR_BLACK, COLOR_RED);
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

    char *choices[] = {
        "PYTHON",
        "C",
    };
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
    return menu_input(menu_win, highlight, choices, n_choices);
}

int instructor_screen()
{
    clear();
    int language = language_screen();

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
