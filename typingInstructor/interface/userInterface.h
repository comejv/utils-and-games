#ifndef USER_INTERFACE
#define USER_INTERFACE

#include <ncurses.h>
#include <string.h>

#define ENTER 10

int main_screen();
int language_screen();
int instructor_screen();
int info_screen();
int settings_screen();
void print_menu(WINDOW *menu_win, int highlight, char *choices[], int n_choices);

#endif // USER_INTERFACE