#include "affichage_console.h"

static int __BACKGROUND = BLACK;
static int __FOREGROUND = WHITE;

void clrscr() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD written;
    COORD home = {0, 0};

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;

    DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hConsole, ' ', cellCount, home, &written);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, home, &written);

    SetConsoleCursorPosition(hConsole, home);
}

void gotoxy(int x, int y){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(h, c);
}

void delete_line(){
    COORD coord;
    DWORD written;
    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    coord.X = info.dwCursorPosition.X;
    coord.Y = info.dwCursorPosition.Y;

    FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE),
        ' ', info.dwSize.X * info.dwCursorPosition.Y, coord, &written);
    gotoxy(info.dwCursorPosition.X + 1, info.dwCursorPosition.Y + 1);
}

int wherex(){
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    return info.dwCursorPosition.X;
}

int wherey(){
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    return info.dwCursorPosition.Y;
}

void text_color(int color){
    __FOREGROUND = color;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, __FOREGROUND + (__BACKGROUND << 4));
}

void bg_color(int color){
    __BACKGROUND = color;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, __FOREGROUND + (__BACKGROUND << 4));
}

void set_color(int colorT, int colorBg){
    __FOREGROUND = colorT;
    __BACKGROUND = colorBg;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, __FOREGROUND + (__BACKGROUND << 4));
}

void hide_cursor(){
    HANDLE cH = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO inf;
    inf.dwSize = 100;
    inf.bVisible = 0;
    SetConsoleCursorInfo(cH, &inf);
}

void show_cursor(){
    HANDLE cH = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO inf;
    inf.dwSize = 100;
    inf.bVisible = 1;
    SetConsoleCursorInfo(cH, &inf);
}
