#ifndef USER_INTERFACE
#define USER_INTERFACE

#include <ncurses.h>
#include <string.h>

#define MIN_WIDTH 100
#define MIN_HEIGHT 40

#define ENTER 10

void check_screen_size();
void print_menu(WINDOW *menu_win, int highlight, char *choices[], int n_choices);
int menu_input(WINDOW *menu_win, int highlight, char *choices[], int n_choices);
int main_screen();
int language_screen();
int instructor_screen();
int info_screen();
int settings_screen();

#endif // USER_INTERFACE