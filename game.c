#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

#include "const.h"
#include "visual.h"
#include "create.h"
#include "forme.h"
#include "chrono.h"
#include "affichage_console.h"
#include "music.h"
//Gestion des issues de la partie (victoire/défaite)
void issues(Donnees *data){
    if(data->etat==5){                                      // Victoire
        if(data->level==3){
            wingame(data);
        }else{                                              // Victoire de niveau
            winlevel(data);
        }
    }else{                                                  // Défaite
        if(data->vies==1){                                  // Perte finale
            loosegame(data);
        }else{                                              // Perte d'une vie et relance du niveau
            data->vies--;
            looselevel(data);                               // Relancer le niveau
        }
    }
}
//Fonction pour échanger deux éléments dans la grille
void change(int tab[Y][X], int y, int x, int direction){
    int temp; 
    switch(direction){ 
        case 1:                                             // Haut
            temp = tab[y][x];
            tab[y][x] = tab[y-1][x];
            tab[y-1][x] = temp;
            break;
        case 2:                                             // Bas
            temp = tab[y][x];
            tab[y][x] = tab[y+1][x];
            tab[y+1][x] = temp;
            break;
        case 3:                                             // Gauche
            temp = tab[y][x];
            tab[y][x] = tab[y][x-1];
            tab[y][x-1] = temp;
            break;
        case 4:                                             // Droite
            temp = tab[y][x];
            tab[y][x] = tab[y][x+1];
            tab[y][x+1] = temp;
            break;
    }
}
//Fonction principale de la partie
void partie(Donnees *data){
    int tab[Y][X];
    int sel=0;
    data->view=0;
    createtab(tab, data);
    data->view=1;
    for(int i=1;i<6;i++){                                   // Initialiser les contrats
        data->Contrat[i][0]=0;
    }
    int x=0, y=0;
    char action = 0;
    int lastTemps = -1;
    data->tempsR = data->tempsM - time(NULL);
    affichage_partie(tab, data, y, x, sel);
    lastTemps = data->tempsR;
    while(1){                                                // Boucle principale de la partie
        data->tempsR = data->tempsM - time(NULL);
        if(kbhit()){                                         // Vérifier si une touche a été pressée
            action = getch();
            if (action == '6')demarrer_musique();
            if(action =='7')arreter_musique();
            int moved = 0;
            if(sel==0){                                      // Déplacement du curseur
                if (action == 'z' && y!=0) { y--; moved = 1; }
                if (action == 's' && y!=Y-1) { y++; moved = 1; }
                if (action == 'q' && x!=0) { x--; moved = 1; }
                if (action == 'd' && x!=X-1) { x++; moved = 1; }
            }else{                                          // Échange des éléments
                if (action == 'z' && y!=0){change(tab,y,x,1);sel=0;y--;data->coups--;moved=1;}
                if (action == 's' && y!=Y-1){change(tab,y,x,2);sel=0;y++;data->coups--;moved=1;}
                if (action == 'q' && x!=0){change(tab,y,x,3);sel=0;x--;data->coups--;moved=1;}
                if (action == 'd' && x!=X-1){change(tab,y,x,4);sel=0;x++;data->coups--;moved=1;}
            }
            if (action == ' '){                             // Sélectionner/Désélectionner un élément
                if(sel == 0)sel=1;                          // Sélectionner l'élément
                else sel=0;                                 // Désélectionner l'élément
                moved = 1;
            }
            if(moved){                                      // Si un mouvement a été effectué
                recherche_formes(tab, data);
                affichage_partie(tab, data, y, x, sel);
                affichagetemps(data);
                lastTemps = data->tempsR;                   // Mettre à jour le temps affiché
            }
        } else {                                            // Mise à jour du temps restant
            if(data->tempsR != lastTemps){                  // Si le temps a changé
                affichagetemps(data);
                lastTemps = data->tempsR;                   // Mettre à jour le temps affiché
            }
        }
        data->etat=0;
        for(int i=0;i<5;i++){                               // Vérifier les contrats
            if(data->Contrat[i+1][0]>=data->Contrat[i+1][1])data->etat++;
        }
        if (data->coups==0 || action == 'p' || data->etat == 5 || data->tempsR <= 0){ // Vérifier les conditions de fin de partie
            issues(data);
            break;
        }
        Sleep(50); // Petite pause pour éviter une utilisation excessive du CPU
    }
}
//Fonctions pour charger et sauvegarder les niveaux
void level1(char pseudo[21],int vie){
    Donnees data;                                            // Initialiser les données de la partie
    data.level = 1;                                          // Niveau 1
    data.coups = 35;                                         // Nombre de coups
    data.vies = vie;                                         // Nombre de vies
    data.tempsM = 300;                                       // Temps maximum pour le niveau 1
    strcpy(data.pseudo,pseudo);
    start_timer(&data);                                      // Démarrer le chronomètre
    data.Contrat[1][1]=10;                                   // Objectifs des contrats
    data.Contrat[2][1]=20;
    data.Contrat[3][1]=10;
    data.Contrat[4][1]=15;
    data.Contrat[5][1]=20;
    partie(&data);                                           // Lancer la partie
}

void level2(char pseudo[21],int vie){
    Donnees data;                                            // Initialiser les données de la partie
    data.level = 2;                                          // Niveau 2
    data.coups = 50;                                         // Nombre de coups
    data.vies = vie;                                         // Nombre de vies
    data.tempsM = 360;                                       // Temps maximum pour le niveau 2
    strcpy(data.pseudo,pseudo);
    start_timer(&data);                                      // Démarrer le chronomètre
    data.Contrat[1][1]=35;                                   // Objectifs des contrats
    data.Contrat[2][1]=20;
    data.Contrat[3][1]=20;
    data.Contrat[4][1]=35;
    data.Contrat[5][1]=20;
    partie(&data);                                           // Lancer la partie
}
//  Fonction pour charger le niveau 3
void level3(char pseudo[21],int vie){
    Donnees data;                                            // Initialiser les données de la partie
    data.level = 3;                                          // Niveau 3
    data.coups = 65;                                         // Nombre de coups
    data.vies = vie;                                         // Nombre de vies
    data.tempsM = 330;                                       // Temps maximum pour le niveau 3
    strcpy(data.pseudo,pseudo);                              // Copier le pseudo
    start_timer(&data);
    data.Contrat[1][1]=115;                                  // Objectifs des contrats
    data.Contrat[2][1]=85;
    data.Contrat[3][1]=115;
    data.Contrat[4][1]=85;
    data.Contrat[5][1]=115;
    partie(&data);                                            // Lancer la partie
}
// Fonction pour charger le niveau en fonction du pseudo
void chargelevel(char pseudo[21]){
    FILE *f = fopen(ENREGISTREMENT, "r");                       // Ouvrir le fichier de sauvegarde
    char temps[21]; 
    int temp1,temp2;
    char ligne[256]; 
    while(fgets(ligne,sizeof(ligne), f)!=NULL){                  // Lire chaque ligne du fichier
        if(sscanf(ligne, "%[^;];%d;%d",temps,&temp1,&temp2)==3){ // Extraire les données
            if(strcmp(temps,pseudo) == 0){                       // Trouver le pseudo correspondant
                switch(temp2){
                    case 1:                                      // Charger le niveau 1
                        fclose(f);                               // Fermer le fichier
                        level1(pseudo,temp1);
                        break;
                    case 2:                                      // Charger le niveau 2
                        fclose(f);
                        level2(pseudo,temp1);
                        break;
                    case 3:                                      //  Charger le niveau 3
                        fclose(f);
                        level3(pseudo,temp1);
                        break;
                }
                break;
            }
        }
    }
}
// Fonction pour sauvegarder la partie
void sauvegarder(Donnees *data){
    FILE *f = fopen(ENREGISTREMENT, "r");                       // Ouvrir le fichier de sauvegarde
    FILE *temp = fopen("temp.txt", "w");                        // Fichier temporaire pour la mise à jour
    
    char ligne[256];
    
    while (fgets(ligne, sizeof(ligne), f) != NULL) {            // Lire chaque ligne du fichier
        char pseudo_lu[21];
        int vie, level;
        
        if (sscanf(ligne, "%[^;];%d;%d", pseudo_lu, &vie, &level) == 3) { // Extraire les données
            if (strcmp(pseudo_lu, data->pseudo) == 0) {         // Trouver le pseudo correspondant
                fprintf(temp, "%s;%d;%d\n", data->pseudo,data->vies, data->level);
            } else {                                            // Copier les autres lignes inchangées
                fprintf(temp, "%s", ligne);
            }
        }
    }
    fclose(f);
    fclose(temp);
    CopyFile("temp.txt", ENREGISTREMENT, FALSE);
}
// Fonction pour supprimer une sauvegarde
void supprimer(Donnees *data){
    FILE *f = fopen(ENREGISTREMENT, "r");                       // Ouvrir le fichier de sauvegarde
    FILE *temp = fopen("temp.txt", "w");                        // Fichier temporaire pour la mise à jour
    
    char ligne[256];
    
    while (fgets(ligne, sizeof(ligne), f) != NULL) {            // Lire chaque ligne du fichier
        char pseudo_lu[21];
        int vie, level;
        
        if (sscanf(ligne, "%[^;];%d;%d", pseudo_lu, &vie, &level) == 3) {// Extraire les données
            if (strcmp(pseudo_lu, data->pseudo) == 0);          // Trouver le pseudo correspondant
            else {                                              // Copier les autres lignes inchangées
                fprintf(temp, "%s", ligne);
            }
        }
    }
    fclose(f);                                                  // Fermer les fichiers
    fclose(temp);                                               // Supprimer l'ancien fichier et renommer le fichier temporaire
    remove(ENREGISTREMENT);
    rename("temp.txt", ENREGISTREMENT);
}
// Fonction pour démarrer une nouvelle partie
void new_game(){
    char pseudo[21];
    int verif=0;
    system("cls");                                              // Effacer l'écran
    printf("Entrez votre pseudo : ");
    do{ // Boucle jusqu'à un pseudo valide
        FILE *f = fopen(ENREGISTREMENT, "r");                   // Ouvrir le fichier de sauvegarde
        fgets(pseudo,21,stdin);
        pseudo[strlen(pseudo)-1]='\0';
        if(f==NULL)verif=0;                                     // Si le fichier n'existe pas, le pseudo est valide
        else{                                                   // Vérifier si le pseudo existe déjà
            char temps[21];
            int temp1,temp2;
            char ligne[256];
            verif=0;
            while(fgets(ligne,sizeof(ligne), f)!=NULL){         // Lire chaque ligne du fichier
                if(sscanf(ligne, "%[^;];%d;%d",temps,&temp1,&temp2)==3){ // Extraire les données
                    if(strcmp(temps,pseudo) == 0){              // Vérifier si le pseudo existe déjà
                        verif=1;
                        system("cls");                          // Effacer l'écran
                        printf("Pseudo déjà pris choisissez-en un autre !\n");
                        f=0;
                        break;
                    }
                }
            }
        }
    fclose(f);
    }while(verif==1);
    FILE *d = fopen(ENREGISTREMENT, "a"); 
    fprintf(d, "%s;%d;%d\n", pseudo, 3, 1);                     // Ajouter la nouvelle sauvegarde
    fclose(d);
    level1(pseudo,3);                                           // Démarrer le niveau 1 avec 3 vies
}
// Fonction pour charger une partie sauvegardée
void charge_game(){
    system("cls");
    char pseudo[21];
    FILE *f = fopen(ENREGISTREMENT, "r");                       // Ouvrir le fichier de sauvegarde
    if(f==NULL){
        do{                                                     // Si le fichier n'existe pas, afficher un message d'erreur
            printf("Attention aucune sauvegarde !\n");
            printf("Cliquer sur une touche");                   // Instructions pour l'utilisateur
        }while(!getch());
        return;
    }
    int verif=0;
    do{                                                         // Boucle jusqu'à un pseudo valide
        system("cls");                                          // Effacer l'écran
        printf("Entrez votre pseudo : ");
        fgets(pseudo,21,stdin);
        pseudo[strlen(pseudo)-1]='\0';
        char temps[21];
        int temp1,temp2;
        char ligne[256];

        rewind(f);                                              // Revenir au début du fichier

        while(fgets(ligne,sizeof(ligne), f)!=NULL){             // Lire chaque ligne du fichier
            if(sscanf(ligne, "%[^;];%d;%d",temps,&temp1,&temp2)==3){ // Extraire les données
                if(strcmp(temps,pseudo) == 0){                  // Trouver le pseudo correspondant
                    verif=1;
                    chargelevel(pseudo);
                    return;
                }
            }
        }
        if(verif==0){                                           // Si le pseudo n'existe pas, afficher un message d'erreur
            char action='0';
            do{                                                 // Boucle jusqu'à une action valide
                if(action=='1'){                                // Réessayer avec un autre pseudo
                    verif=0;
                    break;
                }
                if(action=='2'){                                // Jouer une nouvelle partie
                    new_game();
                    verif=1;
                    break;
                }
                system("cls");                                  // Effacer l'écran
                printf("Pseudo Inexistant !\n");
                printf("1. Essayer un autre pseudo\n");
                printf("2. Jouer une nouvelle partie\n");
            }while(action = getch());
        }
    }while(verif==0);
}
