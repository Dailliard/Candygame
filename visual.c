#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#include "visual.h"
#include "game.h"
#include "const.h"
#include "affichage_console.h"
#include "chrono.h"

#define CONSOLE_WIDTH 80

void affichage_partie(int tab[Y][X], Donnees *data, int sec_r){
    do{
	system("cls");
    gotoxy(0, 0);
	printf("Niveau %d \n", data->level);

    data->vies=3;
    int vies_pos = (CONSOLE_WIDTH / 2) - 6;
    gotoxy(vies_pos, 0);
    printf("Vies: ");
    for(int i = 0; i < 3; i++){
        if(i < data->vies){
            printf("❤️  ");
        }else{
            printf("🖤 ");
        }
    }

    int time_pos = CONSOLE_WIDTH - 14;
    gotoxy(time_pos, 0);
    printf("Temps: %d", sec_r);

    gotoxy(0, 2);
    printf("Coups restants: %d\n", data->coups);

    gotoxy(0, 8);
    printf("Contrats:\n");
    const char* emoji_contrat[] = {"🐶", "😺", "🐮", "🐴", "🐔"};
    for(int i = 0; i < 5; i++){
        printf("- %s : %d/%d\n", emoji_contrat[i], data->Contrat[i][0], data->Contrat[i][1]);
    }

    gotoxy(25, 5);
    viewmap(tab, -1, -1, 0);

    }while(getch()!='p');
}

void viewmap(int tab[Y][X], int a, int b, int sel){
    const char* emoji[] = {" ", "🐶", "😺", "🐮", "🐴", "🐔"};
    system("cls");
    text_color(0);
    for(int y = 0; y < Y; y++){
        for(int x =  0; x < X; x++){
            if(a==y && b==x){
                if(sel==0)text_color(4);
                else text_color(3);
                printf("|%s|", emoji[tab[y][x]]);
            }
            else {
                text_color(0);
                printf("|%s|", emoji[tab[y][x]]);
            }
        }
        printf("\n");
    }
    text_color(15);
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
        printf("     - Alignement : 4 items identiques horizontalement ou verticalement\n");
        printf("     Figures spéciales :\n");
        printf("         - Alignement de 4 : élimine toute la ligne\n");
        printf("         - Alignement de 6 : élimine tous les items de la même famille\n");
        printf("         - Croix de 9 : élimine ligne x colone\n");
        printf("\nAppuyez sur ESPACE pour revenir au menu principal\n");
    }while(action = getch());
}

void menu() {
    char action;
    do{
        if(action == '4')break;
        else if(action == '3') rules();
        else if(action == '2'){ break;}
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