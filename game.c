#include "const.h"
#include "visual.h"
#include "create.h"

void level1(){
    int tab[Y][X];
    createtab(tab);
    viewmap(tab);
}

void new_game(){
    //niveau unique pour le moment
    level1();
}