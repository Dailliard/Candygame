#include <time.h>

#include "utile.h"
//Fonction d'attente en millisecondes
void attendre(int x){ // x en secondes
    int ms;
    int tempsp = time(NULL);
    do{ // Boucle jusqu'à ce que le temps écoulé soit supérieur à x
        ms = time(NULL) - tempsp;
    }while(ms < x);
}
