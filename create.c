#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "create.h"
#include "const.h"
#include "visual.h"
#include "utile.h"
#include "forme.h"



int horizontal4(int tab[Y][X]){
    int z=10;
    for(int i=Y-1; i>=0;i--){
        for(int j=X-1; i>=0;j--){
            if(tab[i][j]==tab[i][j-1] && tab[i][j]==tab[i][j-2] && tab[i][j]==tab[i][j-3]){
                z=i;
                for(int a=0;a<X;a++){
                    tab[z][a]=0;
                }
                return 1;
            }
        }
    }
    return 0;
}

int vertical4(int tab[Y][X]){
    for(int i=Y-1; i>=0;i--){
        for(int j=X-1; i>=0;j--){
            if(tab[i][j]==tab[i-1][j] && tab[i][j]==tab[i-2][j] && tab[i][j]==tab[i-3][j]){
                tab[i][j]=0;
                tab[i-1][j]=0;
                tab[i-2][j]=0;
                tab[i-3][j]=0;
                break;
            }
        }
    }
    return 0;
}

void createtab(int tab[Y][X]){
    srand(time(NULL));
    for(int y = 0; y < Y; y++){
        for(int x =  0; x < X; x++){
            tab[y][x] = rand()%5 +1;
        }
    }
    recherche_formes(tab);
}
