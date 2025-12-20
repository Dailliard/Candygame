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
//Gestion des issues de la partie (victoire/défaite)
void winlevel(Donnees *data){
    char action;
    do{                                                         // Boucle jusqu'à une action valide
        if(action ==' '){ 
            data->level++;                                      // Passer au niveau suivant
            sauvegarder(data);                                  // Sauvegarder les données avant de charger le niveau suivant
            chargelevel(data->pseudo);                          // Charger le niveau suivant
            return;
        }
        if(action =='q'){                                       // Quitter et sauvegarder
            data->level++;
            sauvegarder(data);                                  // Sauvegarder les données
            return; 
        }
        system("cls");
        int centre_x, centre_y; 
        centre_x = CONSOLE_WIDTH / 2;
        centre_y = 6;
        gotoxy(centre_x-11, centre_y);                          // Centrer le texte
        printf("----------------------");
        gotoxy(centre_x-11, centre_y + 1);                      // Affichage de la bordure
        printf("|    Félicitation    |");
        gotoxy(centre_x-11, centre_y + 2);
        printf("|         ✅         |");
        gotoxy(centre_x-11, centre_y + 3);                      // Affichage de la bordure
        printf("----------------------");
        gotoxy(10, centre_y + 5);
        printf("Bravo %s ! Vous avez terminé le niveau %d avec %d vies restantes.\n", data->pseudo, data->level, data->vies);
        gotoxy(10, centre_y + 7);
        printf("[Vous pouvez passer au niveau suivant ou sauvegarder et quitter.]\n");
        gotoxy(10, centre_y + 8);
        printf("[Appuyez sur ESPACE pour le niveau suivant ou q pour sauvegarder et quitter.]\n");
    }while(action = getch());
}
//Gestion de la victoire finale
void wingame(Donnees *data){
    do{
        system("cls");                                          // Effacer l'écran
        int centre_x, centre_y;
        centre_x = CONSOLE_WIDTH / 2;
        centre_y = 6;

        gotoxy(0, 0);   printf("🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅🏅");
        for(int y=1; y<25; y++){                                // Bordures latérales avec des emojis
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

        text_color(GREEN);                                      // Changer la couleur du texte
        gotoxy(centre_x-11, centre_y);                          // Affichage du message de victoire
        printf("----------------------");
        gotoxy(centre_x-11, centre_y + 1);
        printf("|      VICTOIRE      |");
        gotoxy(centre_x-11, centre_y + 2);                      // Affichage de la bordure
        printf("|         🏆         |");
        gotoxy(centre_x-11, centre_y + 3);
        printf("----------------------");                       // Affichage de la bordure
        text_color(WHITE);                                      // Réinitialiser la couleur du texte
        gotoxy(10, centre_y + 5);
        printf("Bravo %s !", data->pseudo);
        gotoxy(10, centre_y + 6);
        printf("Vous avez remporté la partie avec %d vies restantes.\n", data->vies);
        gotoxy(10, centre_y + 8);
        printf("[Appuyez sur ESPACE pour retourner au menu.]\n");
    }while(getch()!=' ');
    supprimer(data);                                            // Supprimer les données de sauvegarde
}
//Gestion de la défaite de niveau
void looselevel(Donnees *data){
    char action='0';
    do{                                                         // Boucle jusqu'à une action valide
        if(action ==' '){
            sauvegarder(data);                                  // Sauvegarder les données avant de relancer le niveau
            chargelevel(data->pseudo);                          // Recharger le niveau actuel
            return;
        }
        if(action =='q'){                                       // Quitter et sauvegarder
            sauvegarder(data);                                  // Sauvegarder les données
            return; 
        }
        system("cls");                                          // Effacer l'écran
        int centre_x, centre_y;
        centre_x = CONSOLE_WIDTH / 2;                           // Calculer le centre de l'écran
        centre_y = 6;

        gotoxy(centre_x-11, centre_y);                          // Centrer le texte
        printf("---------------------");                        // Affichage du message de défaite
        gotoxy(centre_x-11, centre_y + 1);
        printf("|      Défaite      |");
        gotoxy(centre_x-11, centre_y + 2);                      // Affichage de la bordure
        printf("|        🥹          |");
        gotoxy(centre_x-11, centre_y + 3);                      // Affichage de la bordure
        printf("---------------------");
        gotoxy(10, centre_y + 5);
        printf("Dommage %s ! Vous avez échoué le niveau %d il vous reste %d vies.\n", data->pseudo, data->level, data->vies);
        gotoxy(10, centre_y + 7);
        printf("[Vous pouvez recommencer le niveau ou sauvegarder et quitter.]\n");
        gotoxy(10, centre_y + 8);
        printf("[Appuyez sur ESPACE pour recommencer le niveau ou 'q' pour sauvegarder et quitter.]\n"); // Instructions pour l'utilisateur
    }while(action = getch());

}
//Gestion de la défaite finale
void loosegame(Donnees *data){
    do{                                                         // Boucle jusqu'à une action valide
        system("cls");                                          // Effacer l'écran
        int centre_x, centre_y; 
        centre_x = CONSOLE_WIDTH / 2;                           // Calculer le centre de l'écran
        centre_y = 6;

        gotoxy(0, 0);   printf("💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀💀 Deadpool 💀 Deadpool 💀 Deadpool 💀 Deadpool 💀 Deadpool 💀 Deadpool 💀 Deadpool 💀 Deadpool 💀 Deadpool 💀 Deadpool 💀 Deadpool 💀 Deadpool 💀 Deadpool 💀 Deadpool 💀 Deadpool 💀 Deadpool 💀 Deadpool 💀");
        for(int y=1; y<25; y++){                                // Bordures latérales avec des emojis
            gotoxy(0, y);   printf("😔");
            gotoxy(CONSOLE_WIDTH-1, y); printf("😵");
        }
        for(int x = 0; x < CONSOLE_WIDTH; x++){                 // Bordures inférieures avec des emojis
            gotoxy(x, 25);
            printf("💀");
        }
        gotoxy(0, 25);   printf("🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬");
                                                                // Affichage d'emojis décoratifs
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

        text_color(RED);                                        // Changer la couleur du texte
        gotoxy(centre_x-11, centre_y);                          // Centrer le texte
        printf("---------------------");                        // Affichage du message de défaite
        gotoxy(centre_x-11, centre_y + 1);
        printf("|     GAME OVER     |");
        gotoxy(centre_x-11, centre_y + 2);
        printf("|        😭         |");
        gotoxy(centre_x-11, centre_y + 3);                      // Affichage de la bordure
        printf("---------------------");
        text_color(WHITE);
        gotoxy(10, centre_y + 5);                               // Réinitialiser la couleur du texte
        printf("Bien tenté %s ...", data->pseudo);              // Affichage du message de défaite
        gotoxy(10, centre_y + 6);
        printf("Vous avez perdu la partie, réessayez une prochaine fois.\n");
        gotoxy(10, centre_y + 8);
        printf("[Appuyez sur ESPACE pour retourner au menu.]\n");

    }while(getch()!=' ');
    supprimer(data);                                            // Supprimer les données de sauvegarde
}
//Affichage de la grille de jeu
void viewmap(int tab[Y][X], int a, int b, int sel){
    const char* emoji[] = {" ", "🐶", "😺", "🐮", "🐴", "🐔", "🦄"};
    text_color(0);
    for(int y = 0; y < Y; y++){                                 // Parcourir les lignes
        gotoxy(25, y+3);                                        // Positionner le curseur
        for(int x =  0; x < X; x++){                            // Parcourir les colonnes
            if(a==y && b==x){
                if(sel==0)text_color(4);                        // Case sélectionnée
                else text_color(2); 
                printf("|%s|", emoji[tab[y][x]]);               // Afficher l'emoji avec une bordure
            }
            else {                                              // Case non sélectionnée
                text_color(0);
                printf(" %s ", emoji[tab[y][x]]);
            }
        }
    }
    text_color(15);                                             // Réinitialiser la couleur du texte
    printf("\n");
}
//Affichage du temps restant
void affichagetemps(Donnees *data){
    gotoxy(CONSOLE_WIDTH - 20, 0);
    printf("                        ");
    gotoxy(CONSOLE_WIDTH - 14, 0);
    printf("Temps: ");
    show_time(data->tempsR);
    fflush(stdout);
}
//Affichage de la partie
void affichage_partie(int tab[Y][X], Donnees *data,int y, int x, int sel){
	system("cls");                                              // Effacer l'écran
    gotoxy(0, 0);                                               // Affichage des informations de la partie
	printf("Niveau %d \n", data->level);
    int vies_pos = (CONSOLE_WIDTH / 2) - 6;
    gotoxy(vies_pos, 0);
    printf("Vies: ");
    for(int i = 0; i < 3; i++){                                 // Affichage des vies restantes
        if(i < data->vies){
            printf("❤️  ");
        }else{
            printf("🖤 ");
        }
    }
    gotoxy(0, 2);                                               // Affichage des coups restants et des contrats
    printf("Coups restants: %d\n", data->coups);
    gotoxy(0, 5);
    printf("Contrats:\n");
    const char* emoji_contrat[] = {"🐶", "😺", "🐮", "🐴", "🐔"}; 
    for(int i = 0; i < 5; i++){                                 // Affichage des contrats avec des emojis
        if(data->Contrat[i+1][0]>=data->Contrat[i+1][1])text_color(2); // Vert si le contrat est rempli
        else text_color(15);                                    // Blanc sinon
        printf("- %s : %d/%d\n", emoji_contrat[i], data->Contrat[i+1][0], data->Contrat[i+1][1]);
        text_color(15);
    }
    viewmap(tab, y, x, sel);                                    // Affichage de la grille de jeu
}
//Affichge des règles du jeu
void rules(void){
    char action;
    do{                                                         // Boucle jusqu'à une action valide
        if(action == ' ')break;
        system("cls");                                          // Effacer l'écran
        printf("Règles du jeu:\n\n");
        printf("🎯 BUT : Remplir les contrats en remplissant les alignements d'items\n");
        printf("📃 Contrats : Eliminer X items de chaques types demandés dans le temps imparti\n");
        printf("🧩 Figures :\n");
        printf("     - Alignement de 4 : élimine les 4 items\n");
        printf("     Figures spéciales :\n");
        printf("         - Alignement de 6 : élimine tous les items de la même famille sur la ligne ou la colonne correspondante\n");
        printf("         - Croix de 9 : élimine ligne x colonne\n");
        printf("         - Carré 4x4 : élimine tous les items de la même famille dans le carré\n");
        printf("🦄 Bonus la licorn-bombe (à partir du niveau 3) :\n");
        printf("     - item spécial : formez une ligne de 7 items identiques pour créer un item spécial\n");
        printf("     - licorn-bombe : formez un carré 2x2 de 🦄 pour détruire l'entièreté de la grille\n");
        printf("⚠️  Malus (à partir du niveau 2) :\n");
        printf("     - carré 2x2 :  vous perdez 8 items du même type dans le contrat\n");
        printf("\nAppuyez sur ESPACE pour revenir au menu principal\n"); // Instructions pour l'utilisateur
    }while(action = getch());
}
//Affichage des commandes du jeu
void cmds(void){
    char action;
    do{                                                         // Boucle jusqu'à une action valide
        if(action == ' ')break;
        system("cls");                                          // Effacer l'écran
        printf("Commandes du jeu:\n\n");
        printf("     - ⌨️  ZQSD pour déplacer le curseur\n");
        printf("     - 👾 Espace pour sélectionner/déselectionner un item\n");
        printf("     - 🎶 6 et 7 pour activer/désactiver la musique\n");
        printf("     - 😔 p pour abandonner la partie\n");
        printf("\nAppuyez sur ESPACE pour revenir au menu principal\n"); // Instructions pour l'utilisateur
    }while(action = getch());
}
//Affichage du menu principal
void menu() {
    char action;
    do{                                                         // Boucle jusqu'à une action valide
        if(action =='7'){                                       // Arrêter la musique
            arreter_musique();
        }
        else if(action =='6'){                                  // Démarrer la musique
            demarrer_musique();
        }
        else if(action == '5')break;
        else if(action == '4')cmds();
        else if(action == '3')rules();
        else if(action == '2')charge_game();
        else if(action == '1')new_game();
        system("cls");                                          // Effacer l'écran
        int choice;
        printf("ECE HEROES\n");                                 // Titre du jeu
        printf("1. 🎮 Nouvelle Partie\n");
        printf("2. ⏯️  Reprendre une partie\n");  
        printf("3. 📖 Lire les règles du jeu\n");
        printf("4. 🎮 Voir les commandes du jeu\n");
        printf("5. 🔚 Quitter\n");
    }while(action = getch());
}