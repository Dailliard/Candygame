#include <stdlib.h>
#include <time.h>

#include "create.h"
#include "const.h"
#include "visual.h"
#include "utile.h"
#include "forme.h"
//Fonction pour créer et initialiser la grille de jeu
void createtab(int tab[Y][X], Donnees *data){
    srand(time(NULL)); // Initialiser le générateur de nombres aléatoires
    for(int y = 0; y < Y; y++){ // Parcourir les lignes
        for(int x = 0; x < X; x++){ // Parcourir les colonnes
            tab[y][x] = rand() % 5 + 1; 
        }
    }
    recherche_formes(tab, data); // Vérifier et remplacer les formes initiales
}
