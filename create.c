#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "create.h"
#include "const.h"
#include "visual.h"
#include "utile.h"
#include "forme.h"

void createtab(int tab[Y][X]){
    srand(time(NULL));
    for(int y = 0; y < Y; y++){
        for(int x =  0; x < X; x++){
            tab[y][x] = rand()%5 +1;
        }
    }
    recherche_formes(tab);
}
