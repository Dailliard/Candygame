#include "affichage_console.h"

static int __BACKGROUND = BLACK;
static int __FOREGROUND = WHITE;

//Effacer l'écran de la console
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

//Déplacer le curseur à une position spécifique
void gotoxy(int x, int y){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(h, c);
}

//Supprimer la ligne courante
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

//Obtenir la position X du curseur
int wherex(){
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    return info.dwCursorPosition.X;
}

//Obtenir la position Y du curseur
int wherey(){
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    return info.dwCursorPosition.Y;
}

//Définir la couleur du texte
void text_color(int color){
    __FOREGROUND = color;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, __FOREGROUND + (__BACKGROUND << 4));
}

//Définir la couleur de l'arrière-plan
void bg_color(int color){
    __BACKGROUND = color;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, __FOREGROUND + (__BACKGROUND << 4));
}

//Définir la couleur du texte et de l'arrière-plan
void set_color(int colorT, int colorBg){
    __FOREGROUND = colorT;
    __BACKGROUND = colorBg;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, __FOREGROUND + (__BACKGROUND << 4));
}

//Cacher le curseur
void hide_cursor(){
    HANDLE cH = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO inf;
    inf.dwSize = 100;
    inf.bVisible = 0;
    SetConsoleCursorInfo(cH, &inf);
}

//Afficher le curseur
void show_cursor(){ 
    HANDLE cH = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO inf;
    inf.dwSize = 100;
    inf.bVisible = 1;
    SetConsoleCursorInfo(cH, &inf);
}
