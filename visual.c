#include "visual.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

void rules(void){
    char action;
    do{
        if(action == ' '){
            break;
        }
        system("cls");
        printf("Règles du jeu:\n");
    }while(action = getch());
}

void menu(void) {
    char action;
    do{
        if(action == '4'){
            break;
        }else if(action == '3'){
            rules();
        }else if(action == '2'){
            //load_game();
        }else if(action == '1'){
            //new_game();
        }
        system("cls");
        int choice;
        printf("ECE HEROES\n");
        printf("1. 🎮 Nouvelle Partie\n");
        printf("2. ⏯️  Reprendre une partie\n");  
        printf("3. 📖 Lire les règles du jeu\n");
        printf("4. 🔚 Quitter\n");
    }while(action = getch());
}

