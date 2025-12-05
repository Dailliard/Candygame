#include "visual.h"

#include <stdio.h>
#include <windows.h>
void test(){
    printf("Test function executed.\n");
}
int main() {
    SetConsoleOutputCP(CP_UTF8);
    menu();
    test();
    //test 2 de test
    return 0;
}