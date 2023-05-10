#ifndef USER_INTERFACE
#define USER_INTERFACE

#include <ncurses.h>
#include <string.h>
#include <stdio.h>
#include "../common/util.h"
#include "../codeFiles/fileSys.h"

#define MIN_WIDTH 100
#define MIN_HEIGHT 40

#define ENTER 10

// Check screen size
// If either arg is 0, use MIN_WIDTH and MIN_HEIGHT
void check_screen_size(int min_width, int min_height);

// Print menu with choices in a box in the middle
void print_menu(WINDOW *menu_win, int highlight, char *choices[], int n_choices);

// Get input and change highlighted text
int menu_input(WINDOW *menu_win, int highlight, char *choices[], int n_choices);

// Show welcome screen
int main_screen();

// Show language choice screen (choices depend on available files)
int language_screen();

// Print content of filename in WINDOW
// Put file name at the top
size_t wprintFileContent(const char *filename, WINDOW **win, int pad_width);

// Unimplemented
int instructor_screen();
int info_screen();
int settings_screen();

#endif // USER_INTERFACE