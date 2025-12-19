#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#include "visual.h"
#include "game.h"
#include "const.h"
#include "affichage_console.h"
#include "chrono.h"
#include "music.h"

void winlevel(Donnees *data){
    char action;
    do{
        if(action ==' '){
            sauvegarder(data);
            chargelevel(data->pseudo);
            return;
        }
        if(action =='q'){
            sauvegarder(data);
            return; 
        }
        system("cls");
        int centre_x, centre_y;
        centre_x = CONSOLE_WIDTH / 2;
        centre_y = 6;
        gotoxy(centre_x-11, centre_y);
        printf("----------------------");
        gotoxy(centre_x-11, centre_y + 1);
        printf("|    Félicitation    |");
        gotoxy(centre_x-11, centre_y + 2);
        printf("|         ✅         |");
        gotoxy(centre_x-11, centre_y + 3);
        printf("----------------------");
        gotoxy(10, centre_y + 5);
        printf("Bravo %s ! Vous avez terminé le niveau %d avec %d vies restantes.\n", data->pseudo, data->level, data->vies);
        gotoxy(10, centre_y + 7);
        printf("[Vous pouvez passer au niveau suivant ou sauvegarder et quitter.]\n");
        gotoxy(10, centre_y + 8);
        printf("[Appuyez sur ESPACE pour le niveau suivant ou q pour sauvegarder et quitter.]\n");
    }while(action = getch());
}

void wingame(Donnees *data){
    do{
        system("cls");
        int centre_x, centre_y;
        centre_x = CONSOLE_WIDTH / 2;
        centre_y = 6;

        gotoxy(0, 0);   printf("🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅");
        for(int y=1; y<25; y++){
            gotoxy(0, y);   printf("🎉");
            gotoxy(CONSOLE_WIDTH-1, y); printf("✨");
        }
        gotoxy(0, 25);   printf("🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺🕺");

        gotoxy(10, 2);  printf("🎈");
        gotoxy(5, 3);   printf("🎊");
        gotoxy(10, 8);  printf("🏆");
        gotoxy(70, 6);  printf("🎉");
        gotoxy(90, 12); printf("✨");
        gotoxy(15, 20); printf("🥇");
        gotoxy(60, 22); printf("🏅");
        gotoxy(30, 16); printf("🎆");
        gotoxy(80, 18); printf("🎇");

        gotoxy(centre_x-11, centre_y);
        printf("----------------------");
        gotoxy(centre_x-11, centre_y + 1);
        printf("|      VICTOIRE      |");
        gotoxy(centre_x-11, centre_y + 2);
        printf("|         🏆         |");
        gotoxy(centre_x-11, centre_y + 3);
        printf("----------------------");
        gotoxy(10, centre_y + 5);
        printf("Bravo %s ! Vous avez remporté la partie avec %d vies restantes.\n", data->pseudo, data->vies);
        gotoxy(10, centre_y + 7);
        printf("[Appuyez sur ESPACE pour retourner au menu.]\n");
    }while(getch()!=' ');
    supprimer(data);
}

void looselevel(Donnees *data){
    char action='0';
    do{
        if(action ==' '){
            sauvegarder(data);
            chargelevel(data->pseudo);
            return;
        }
        if(action =='q'){
            sauvegarder(data);
            return; 
        }
        system("cls");
        int centre_x, centre_y;
        centre_x = CONSOLE_WIDTH / 2;
        centre_y = 6;

        gotoxy(centre_x-11, centre_y);
        printf("---------------------");
        gotoxy(centre_x-11, centre_y + 1);
        printf("|      Défaite      |");
        gotoxy(centre_x-11, centre_y + 2);
        printf("|        🥹          |");
        gotoxy(centre_x-11, centre_y + 3);
        printf("---------------------");
        gotoxy(10, centre_y + 5);
        printf("Dommage %s ! Vous avez échoué le niveau %d il vous reste %d vies.\n", data->pseudo, data->level, data->vies);
        gotoxy(10, centre_y + 7);
        printf("[Vous pouvez recommencer le niveau ou sauvegarder et quitter.]\n");
        gotoxy(10, centre_y + 8);
        printf("[Appuyez sur ESPACE pour recommencer le niveau ou 'q' pour sauvegarder et quitter.]\n");
    }while(action = getch());

}

void loosegame(Donnees *data){
    do{
        system("cls");
        int centre_x, centre_y;
        centre_x = CONSOLE_WIDTH / 2;
        centre_y = 6;

        gotoxy(0, 0);   printf("💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀");
        for(int y=1; y<25; y++){
            gotoxy(0, y);   printf("😔");
            gotoxy(CONSOLE_WIDTH-1, y); printf("😵");
        }
        for(int x = 0; x < CONSOLE_WIDTH; x++){
            gotoxy(x, 25);
            printf("💀");
        }
        gotoxy(0, 25);   printf("🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬");

        gotoxy(8, 3);   printf("💔");
        gotoxy(15, 10); printf("😫");
        gotoxy(70, 5);  printf("😤");
        gotoxy(90, 12); printf("🥀");
        gotoxy(20, 18); printf("🩸");
        gotoxy(60, 21); printf("🐀");
        gotoxy(30, 15); printf("🤢");
        gotoxy(80, 22); printf("👻");
        gotoxy(10, 24); printf("   🤣");
        gotoxy(9, 24);  printf("🫵");

        gotoxy(centre_x-11, centre_y);
        printf("---------------------");
        gotoxy(centre_x-11, centre_y + 1);
        printf("|     GAME OVER     |");
        gotoxy(centre_x-11, centre_y + 2);
        printf("|        😭         |");
        gotoxy(centre_x-11, centre_y + 3);
        printf("---------------------");
        gotoxy(10, centre_y + 5);
        printf("GAME OVER %s ... Vous avez perdu la partie, réessayez une prochaine fois.\n", data->pseudo);
        gotoxy(10, centre_y + 7);
        printf("[Appuyez sur ESPACE pour retourner au menu.]\n");
    }while(getch()!=' ');
    supprimer(data);
}

void viewmap(int tab[Y][X], int a, int b, int sel){
    const char* emoji[] = {" ", "🐶", "😺", "🐮", "🐴", "🐔", "🦄"};
    text_color(0);
    for(int y = 0; y < Y; y++){
        gotoxy(25, y+3);
        for(int x =  0; x < X; x++){
            if(a==y && b==x){
                if(sel==0)text_color(4);
                else text_color(2);
                printf("|%s|", emoji[tab[y][x]]);
            }
            else {
                text_color(0);
                printf(" %s ", emoji[tab[y][x]]);
            }
        }
    }
    text_color(15);
    printf("\n");
}

void affichage_partie(int tab[Y][X], Donnees *data,int y, int x, int sel){
	system("cls");
    gotoxy(0, 0);
	printf("Niveau %d \n", data->level);
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
    printf("Temps: ");
    show_time(data->tempsR);

    gotoxy(0, 2);
    printf("Coups restants: %d\n", data->coups);
    gotoxy(0, 5);
    printf("Contrats:\n");
    const char* emoji_contrat[] = {"🐶", "😺", "🐮", "🐴", "🐔"};
    for(int i = 0; i < 5; i++){
        if(data->Contrat[i+1][0]>=data->Contrat[i+1][1])text_color(2);
        printf("- %s : %d/%d\n", emoji_contrat[i], data->Contrat[i+1][0], data->Contrat[i+1][1]);
        text_color(15);
    }
    viewmap(tab, y, x, sel);
}

void rules(void){
    char action;
    do{
        if(action == ' ')break;
        system("cls");
        printf("Règles du jeu:\n\n");
        printf("🎯 BUT : Remplir les contrats en remplissant les alignements d'items\n");
        printf("📃 Contrats : Eliminer X items de chaques types demandés dans le temps imparti\n");
        printf("🧩 Figures :\n");
        printf("     - Alignement de 4 : élimine les 4 items\n");
        printf("     Figures spéciales :\n");
        printf("         - Alignement de 6 : élimine tous les items de la même famille sur la ligne ou la colonne correspondante\n");
        printf("         - Croix de 9 : élimine ligne x colonne\n");
        printf("         - Carré 4x4 : élimine tous les items de la même famille dans le carré\n");
        printf("🦄 Bonus (à partir du niveau 2) :\n");
        printf("     - item spécial : formez une ligne de 8 items identiques pour créer un item spécial\n");
        printf("     - Vie : formez un carré 3x3 de 🐴 avec une 🦄 au centre pour gagner une vie (max 3 vies)\n");
        printf("⚠️ Malus (à partir du niveau 3) :\n");
        printf("     - carré 2x2 :  vous perdez 8 items du même type dans le contrat\n");
        printf("\nAppuyez sur ESPACE pour revenir au menu principal\n");
    }while(action = getch());
}

void cmds(void){
    char action;
    do{
        if(action == ' ')break;
        system("cls");
        printf("Commandes du jeu:\n\n");
        printf("     - ⌨️  ZQSD pour déplacer le curseur\n");
        printf("     - 👾 Espace pour sélectionner/déselectionner un item\n");
        printf("     - 🎶 6 et 7 pour activer/désactiver la musique\n");
        printf("     - 😔 p pour abandonner la partie\n");
        printf("\nAppuyez sur ESPACE pour revenir au menu principal\n");
    }while(action = getch());
}

void menu() {
    char action;
    do{
        
        if(action =='7'){
            arreter_musique();
        }
        else if(action =='6'){
            demarrer_musique();
        }
        else if(action == '5')break;
        else if(action == '4')cmds();
        else if(action == '3')rules();
        else if(action == '2')charge_game();
        else if(action == '1')new_game();
        system("cls");
        int choice;
        printf("ECE HEROES\n");
        printf("1. 🎮 Nouvelle Partie\n");
        printf("2. ⏯️  Reprendre une partie\n");  
        printf("3. 📖 Lire les règles du jeu\n");
        printf("4. 🎮 Voir les commandes du jeu\n");
        printf("5. 🔚 Quitter\n");
    }while(action = getch());
}