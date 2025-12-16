#include "create.h"
#include "const.h"

#include <stdlib.h>
#include <time.h>

void createtab(int tab[Y][X]){
    srand(time(NULL));
    for(int y = 0; y < Y; y++){
        for(int x =  0; x < X; y++){
            tab[y][x] = rand()%10;
        }
    }
}