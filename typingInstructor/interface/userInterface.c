#include "userInterface.h"

int main_screen()
{
    clear();
    WINDOW *menu_win;
    int highlight = 1;
    int c;

    char *choices[] = {
        "INSTRUCTOR",
        "INFORMATION",
        "SETTINGS",
        "EXIT",
    };
    int n_choices = sizeof(choices) / sizeof(char *);

    int screen_width = getmaxx(stdscr);
    int screen_height = getmaxy(stdscr);

    mvprintw(screen_height / 5, (screen_width - 35) / 2, "Welcome to the Typing Instructor!");
    mvprintw(screen_height - 1, 0, "Use arrow keys to go up and down, press enter to select a choice");

    // Initialize menu window
    int box_width = 15;
    int box_height = n_choices + 4;

    int startx = (screen_width - box_width) / 2;
    int starty = (screen_height - box_height) / 2;

    menu_win = newwin(box_height, box_width, starty, startx - 1);
    keypad(menu_win, TRUE);
    refresh();
    print_menu(menu_win, highlight, choices, n_choices);
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

int language_screen()
{
    clear();

    WINDOW *menu_win;
    int highlight = 1;
    int c;

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
    int box_width = 10;
    int box_height = n_choices + 4;

    int startx = (screen_width - box_width) / 2;
    int starty = (screen_height - box_height) / 2;

    menu_win = newwin(box_height, box_width, starty, startx - 1);
    keypad(menu_win, TRUE);
    refresh();
    print_menu(menu_win, highlight, choices, n_choices);
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

    return 0;
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

void print_menu(WINDOW *menu_win, int highlight, char *choices[], int n_choices)
{
    int x, y, i;

    int win_width = getmaxx(menu_win);

    y = 2;

    // Use wborder with explicit border characters
    wborder(menu_win, '|', '|', '-', '-', '+', '+',
            '+', '+');

    for (i = 0; i < n_choices; ++i)
    {
        x = (win_width - strlen(choices[i])) / 2;
        if (highlight == i + 1) /* High light the present choice */
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
