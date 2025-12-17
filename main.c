#include <stdio.h>
#include <windows.h>

#include "visual.h"


void test(){
    printf("Test function executed.\n");
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    menu();
    return 0;
}