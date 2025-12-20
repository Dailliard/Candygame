#include <windows.h>

#include "visual.h"
//Point d'entrée principal du programme
int main() {
    SetConsoleOutputCP(CP_UTF8);        // Activer le support UTF-8 pour les emojis
    menu();                             // Afficher le menu principal
    return 0;
}
