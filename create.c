#include <stdlib.h>
#include <time.h>

#include "create.h"
#include "const.h"
#include "visual.h"
#include "utile.h"
#include "forme.h"

//Fonction pour créer et initialiser la grille de jeu
void createtab(int tab[Y][X], Donnees *data){

    // Initialiser le générateur de nombres aléatoires pour obtenir une grille différente à chaque exécution
    srand(time(NULL));       

    // Remplit chaque case avec une valeur aléatoire entre 1 et 5
    for(int y = 0; y < Y; y++){
        for(int x = 0; x < X; x++){
            tab[y][x] = rand() % 5 + 1;
        }
    }
    recherche_formes(tab, data); // Supprime et remplace les formes trouvées
}
