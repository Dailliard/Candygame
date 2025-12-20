#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

#include "const.h"
#include "visual.h"
#include "forme.h"

//Ajoute des nouveaux éléments dans les emplacements vides de la grille
void add(int tab[Y][X]){

    // Parcourir le tableau et si la case est vide, ajouter un nouvel élément aléatoire
    for(int y = 0; y < Y; y++){
        for(int x = 0; x < X; x++){
            if(tab[y][x] == 0){ 
                tab[y][x] = rand() % 5 + 1; // Nouvelle valeur aléatoire entre 1 et 5
            }
        }
    }
}

//Fonction pour faire descendre les éléments dans la grille
void descendre(int tab[Y][X]){
    for(int y = Y-1; y > 0; y--){                   // Parcourir les lignes de bas en haut
        for(int x = X-1; x >= 0; x--){              // Parcourir les colonnes de droite à gauche
            if(tab[y][x] == 0){                     // Si la case est vide
                if(tab[y-1][x]==0){                 // Si la case au-dessus est aussi vide
                    for(int i=y;i>=0;i--){          // Chercher la première case non vide au-dessus
                        if(tab[i][x]!=0){           // Si une case non vide est trouvée
                           int temp = tab[y][x];    // Échanger les valeurs
                            tab[y][x] = tab[i][x];
                            tab[i][x] = temp;
                            break;
                        }
                    }
                }else{                              // Échanger avec la case au-dessus
                    int temp = tab[y][x];
                    tab[y][x] = tab[y-1][x];
                    tab[y-1][x] = temp;
                }
            }
        }
    }
}

//Fonction pour remplacer les éléments après une suppression
void replace(int tab[Y][X], Donnees *data){
    descendre(tab);
    if(data->view==1){
        affichage_partie(tab,data,0,0,0);

                                                    // Pause pour visualiser l'animation
        Sleep(250);                                  
    }
    add(tab);
}

//Fonction pour rechercher le malus dans la grille
int malus(int tab[Y][X], Donnees *data){

    // Vérifier la présence d'un carré 2x2 dans la grille
    for(int i = 1; i < Y; i++){ 
        for(int j = 1; j < X; j++){ 
            if(tab[i][j] != 0 &&                   
                tab[i][j] == tab[i][j-1] &&
                tab[i][j] == tab[i-1][j] &&
                tab[i][j] == tab[i-1][j-1]){

                    // Si c'est des licornes (6ème élément), supprimer tous les éléments de la grille
                    if(tab[i][j]==6){                   
                        for(int y = 0; y < Y; y++){ 
                            for(int x = 0; x < X; x++){ 
                                data->Contrat[tab[y][x]][0]++;
                                tab[y][x] = 0;
                            }
                        }
                    }
                    else{
                        // Mettre à jour le contrat                       
                        if(data->Contrat[tab[i][j]][0]<=8)data->Contrat[tab[i][j]][0] = 0;
                        else data->Contrat[tab[i][j]][0] -= 8;

                        // Supprimer les éléments du carré
                        tab[i][j] = 0; 
                        tab[i][j-1] = 0;
                        tab[i-1][j] = 0;
                        tab[i-1][j-1] = 0;
                    }

                    replace(tab,data); // Remplacer les éléments
                    return 1;
                }
        }
    }
    return 0;
}

//Fonction pour rechercher un carré 4x4 dans la grille
int carre(int tab[Y][X], Donnees *data){
    for(int i = 3; i < Y; i++){ 
        for(int j = 3; j < X; j++){ 
            if(tab[i][j]==tab[i][j-1] &&                    // Vérifier les 4 éléments horizontaux bas
                 tab[i][j]==tab[i][j-2] &&
                  tab[i][j]==tab[i][j-3]){

                if(tab[i][j]==tab[i-1][j] &&                // Vérifier les 4 éléments verticaux droites
                     tab[i][j]==tab[i-2][j] &&
                      tab[i][j]==tab[i-3][j]){

                    if(tab[i][j]==tab[i-3][j-1] &&          // Vérifier les 4 éléments horizontaux supérieurs
                         tab[i][j]==tab[i-3][j-2] &&
                          tab[i][j]==tab[i-3][j-3]){

                        if(tab[i][j]==tab[i-1][j-3] &&      // Vérifier les 4 éléments verticaux gauches
                             tab[i][j]==tab[i-2][j-3] &&
                              tab[i][j]==tab[i-3][j-3]){
                            
                            int temp = tab[i][j];           // Stocker la valeur de l'élément
                            
                            for(int z = i-3; z <= i; z++){  // Suppression du carré
                                for(int a = j-3; a <= j; a++){
                                    if(tab[z][a] == temp){
                                        data->Contrat[temp][0]++;
                                        tab[z][a] = 0;
                                    }
                                    
                                }
                            }
                            replace(tab,data);              // Remplacer les éléments
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

//Fonction pour rechercher une croix dans la grille
int croix(int tab[Y][X], Donnees *data){
    for(int i = 2; i < Y-2; i++){ 
        for(int j = 2; j < X-2; j++){ 
            if(tab[i][j]==tab[i][j-1] &&            // Vérifier les 5 éléments horizontaux
                 tab[i][j]==tab[i][j-2] &&
                  tab[i][j]==tab[i][j+1] &&
                   tab[i][j]==tab[i][j+2]){

                if(tab[i][j]==tab[i-1][j] &&        // Vérifier les 5 éléments verticaux
                     tab[i][j]==tab[i-2][j] &&
                      tab[i][j]==tab[i+1][j] &&
                       tab[i][j]==tab[i+2][j]){

                    int temp = tab[i][j];

                    for(int z = 0; z < X; z++){
                        if(tab[i][z] == temp){      // Suppression de la ligne
                            tab[i][z] = 0;
                            data->Contrat[temp][0]++;
                        }
                        
                    }
                    for(int z = 0; z < Y; z++){
                        if(tab[z][j] == temp){      // Suppression de la colonne
                            tab[z][j] = 0;
                            data->Contrat[temp][0]++;
                        }
                        
                    }
                    replace(tab,data);             // Remplacer les éléments
                    return 1;
                }
            } 
        }
    }
    return 0;
}

//Fonction pour rechercher les lignes de 7 éléments dans la grille
int horizontal7(int tab[Y][X], Donnees *data){
    for(int i = 0; i < Y; i++){ 
        for(int j = 6; j < X; j++){ 
            if(tab[i][j]==tab[i][j-1] &&                    // Vérifier les 7 éléments
                 tab[i][j]==tab[i][j-2] &&
                  tab[i][j]==tab[i][j-3] &&
                   tab[i][j]==tab[i][j-4] &&
                    tab[i][j]==tab[i][j-5] &&
                     tab[i][j]==tab[i][j-6]){

                int temp = tab[i][j];
                for(int a = 0; a < X; a++){ 
                    if(tab[i][a] == temp){                  // Supprimer les éléments correspondants
                         data->Contrat[temp][0]++;          // Mettre à jour le contrat
                         tab[i][a] = 0; 
                    }
                }
                tab[i][j]=6;
                replace(tab,data);                          // Remplacer les éléments
                return 1;
            }
        }
    }
    return 0;
}

//Fonction pour rechercher les formes dans la grille
int vertical7(int tab[Y][X], Donnees *data){
    for(int i = 6; i < Y; i++){                             // Commencer à la ligne 6
        for(int j = 0; j < X; j++){                         // Parcourir les colonnes
            if(tab[i][j]==tab[i-1][j] &&                    // Vérifier les 7 éléments
                 tab[i][j]==tab[i-2][j] &&
                  tab[i][j]==tab[i-3][j] &&
                   tab[i][j]==tab[i-4][j] &&
                    tab[i][j]==tab[i-5][j] &&
                     tab[i][j]==tab[i-6][j]){

                int temp = tab[i][j]; 
                for(int z = 0; z < Y; z++){                 // Parcourir les lignes
                    if(tab[z][j] == temp){                  // Supprimer les éléments correspondants
                        tab[z][j] = 0;                      // Supprimer les éléments correspondants
                        data->Contrat[temp][0]++;           // Mettre à jour le contrat
                    }
                }
                tab[i][j]=6; 
                replace(tab,data);                          // Remplacer les éléments
                return 1;
            }
        }
    }
    return 0;
}

//Fonction pour rechercher les formes dans la grille
int horizontal6(int tab[Y][X], Donnees *data){
    for(int i = 0; i < Y; i++){                             // Lire la grille de bas en haut
        for(int j = 5; j < X; j++){                         
            if(tab[i][j]==tab[i][j-1] &&                    // Vérifier les 6 éléments
                 tab[i][j]==tab[i][j-2] &&
                  tab[i][j]==tab[i][j-3] &&
                   tab[i][j]==tab[i][j-4] &&
                    tab[i][j]==tab[i][j-5]){

                int temp = tab[i][j];
                for(int a = 0; a < X; a++){                 // Parcourir les colonnes
                    if(tab[i][a] == temp){                  // Supprimer les éléments correspondants
                         data->Contrat[temp][0]++;
                         tab[i][a] = 0; 
                    }
                }
                replace(tab,data);                          // Remplacer les éléments
                return 1;
            }
        }
    }
    return 0;
}

//Fonction pour rechercher les formes dans la grille
int vertical6(int tab[Y][X], Donnees *data){
    for(int i = 5; i < Y; i++){                             // Commencer à la ligne 5
        for(int j = 0; j < X; j++){                         // Parcourir les colonnes
            if(tab[i][j]==tab[i-1][j] &&                    // Vérifier les 6 éléments
                 tab[i][j]==tab[i-2][j] &&
                  tab[i][j]==tab[i-3][j] &&
                   tab[i][j]==tab[i-4][j] &&
                    tab[i][j]==tab[i-5][j]){

                int temp = tab[i][j];
                for(int z = 0; z < Y; z++){                 // Parcourir les lignes
                    if(tab[z][j] == temp){                  // Supprimer les éléments correspondants
                        tab[z][j] = 0;
                        data->Contrat[temp][0]++;
                    }
                }
                replace(tab,data);                           // Remplacer les éléments
                return 1;
            }
        }
    }
    return 0;
}

//Fonction pour rechercher les formes dans la grille
int horizontal4(int tab[Y][X], Donnees *data){
    for(int i = Y-1; i >=0; i--){                           // Lire la grille de bas en haut
        for(int j = 3; j < X; j++){                         
            if(tab[i][j]==tab[i][j-1] &&                    // Horizontale de 4
                 tab[i][j]==tab[i][j-2] &&                  // Vérifier les 4 éléments
                  tab[i][j]==tab[i][j-3]){                  // Si une horizontale de 4 est trouvée
                    
                data->Contrat[tab[i][j]][0]+=4;             // Mettre à jour le contrat
                tab[i][j] = 0;                              // Supprimer les éléments
                tab[i][j-1] = 0;
                tab[i][j-2] = 0;
                tab[i][j-3] = 0;
                replace(tab,data);                          // Remplacer les éléments
                return 1;
            }
        }
    }
    return 0;
}

//Fonction pour rechercher les formes dans la grille
int vertical4(int tab[Y][X], Donnees *data){
    for(int i = 3; i < Y; i++){                                                             // Commencer à la ligne 3
        for(int j = 0; j < X; j++){                                                         // Parcourir les colonnes
            if(tab[i][j]==tab[i-1][j] && tab[i][j]==tab[i-2][j] && tab[i][j]==tab[i-3][j]){ // Verticale de 4
                data->Contrat[tab[i][j]][0]+=4;                                             // Mettre à jour le contrat
                tab[i][j] = 0;                                                              // Supprimer les éléments
                tab[i-1][j] = 0; 
                tab[i-2][j] = 0;
                tab[i-3][j] = 0;
                replace(tab,data);                                                          // Remplacer les éléments
                return 1;
            }
        }
    }
    return 0;
}

//Fonction pour rechercher les formes dans la grille
int recherche_formes(int tab[Y][X], Donnees *data){
    srand(time(NULL));
    int count;
    do{                                                                                    // Répéter jusqu'à ce qu'aucune forme ne soit trouvée
        count = 0;
        if(data->level>1){                                                                 // Niveaux 2 et 3
            if(data->level>2){                                                             // Niveau 3
                count += horizontal7(tab, data);
                count += vertical7(tab, data); 
            }
            count+=malus(tab, data);                                                       // Niveaux 2 et 3
        }
        count += carre(tab, data);                                                         // Tous les niveaux
        count += croix(tab, data); 
        count += horizontal6(tab, data); 
        count += vertical6(tab, data); 
        count += horizontal4(tab, data); 
        count += vertical4(tab, data);  
    }while(count > 0);
    return 0;
}
