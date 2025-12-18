#include <time.h>

#include "utile.h"

void attendre(int x){
    int ms;
    int tempsp = time(NULL);
    do{
        ms = time(NULL) - tempsp;
    }while(ms < x);
}
