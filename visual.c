#include "visual.h"
#include "game.h"
#include "const.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

void viewmap(int tab[Y][X]){
    for(int y = 0; y < Y; y++){
        for(int x =  0; x < X; y++){
            printf("%d",tab[y][x]);
        }
    }
}

void rules(void){
    char action;
    do{
        if(action == ' ')break;
        system("cls");
        printf("Règles du jeu:\n\n");
        printf("🎯 BUT : Remplir les contrats en remplissant les alignements d'items\n");
        printf("📃 Contrats : Eliminer X items de chaques types demandés\n");
        printf("🧩 Figures :\n");
        printf("     - Alignement : 3 items identiques horizontalement ou verticalement\n");
        printf("     Figures spéciales :\n");
        printf("         - Alignement de 4 : élimine toute la ligne\n");
        printf("         - Alignement de 6 : élimine tous les items de la même famille\n");
        printf("         - Croix de 9 : élimine ligne x colone\n");
        printf("\nAppuyez sur ESPACE pour revenir au menu principal\n");
    }while(action = getch());
}

void menu(void) {
    char action;
    do{
        if(action == '4')break;
        else if(action == '3') rules();
        else if(action == '2'){ /**load_game();**/ break;}
        else if(action == '1'){ new_game(); break;}
        system("cls");
        int choice;
        printf("ECE HEROES\n");
        printf("1. 🎮 Nouvelle Partie\n");
        printf("2. ⏯️  Reprendre une partie\n");  
        printf("3. 📖 Lire les règles du jeu\n");
        printf("4. 🔚 Quitter\n");
    }while(action = getch());
}

