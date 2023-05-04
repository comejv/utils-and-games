#include "interface/userInterface.h"

int main()
{
    // Initialize curses
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);

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