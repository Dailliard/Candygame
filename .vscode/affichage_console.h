#ifndef AFFICHAGE_CONSOLE_H_INCLUDED
#define AFFICHAGE_CONSOLE_H_INCLUDED

#include <windows.h>
#include <conio.h>

// 16 couleurs utilisables en mode console de base
typedef enum{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
} COLORS;

void clrscr();
void gotoxy(int x, int y);
void delete_line();
int wherex();
int wherey();
void text_color(int color);
void bg_color(int color);
void set_color(int colorT, int colorBg);
void hide_cursor();
void show_cursor();
int kbhit();
int getch();

#endif
