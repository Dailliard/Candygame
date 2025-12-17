#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "const.h"
#include "visual.h"
#include "forme.h"

void add(int tab[Y][X]){
    for(int y=0;y<Y;y++){
        for(int x=0;x<X;x++){
            if(tab[y][x]==0){
                tab[y][x] = rand()%5 +1;
            }
        }
    }
}

void descendre(int tab[Y][X]){
    for(int y=Y-1;y>0;y--){
        for(int x=X-1;x>=0;x--){
            if(tab[y][x]==0){
                int temp = tab[y][x];
                tab[y][x]=tab[y-1][x];
                tab[y-1][x]=temp;
            }
        }
    }
}

void replace(int tab[Y][X]){
    descendre(tab);
    add(tab);
}

int horizontal4(int tab[Y][X]){
    for(int i=Y-1; i>=0;i--){
        for(int j=X-1; j>=0;j--){
            if(tab[i][j]==tab[i][j-1] && tab[i][j]==tab[i][j-2] && tab[i][j]==tab[i][j-3]){
                for(int z=0;z<X;z++){
                    tab[i][z]=0;
                }
                replace(tab);
                return 1;
            }
        }
    }
    return 0;
}

int vertical4(int tab[Y][X]){
    for(int i=Y-1; i>=0;i--){
        for(int j=X-1; j>=0;j--){
            if(tab[i][j]==tab[i-1][j] && tab[i][j]==tab[i-2][j]){
                tab[i][j]=0;
                tab[i-1][j]=0;
                tab[i-2][j]=0;
                replace(tab);
                return 1;
            }
        }
    }
    return 0;
}

int horizontal3(int tab[Y][X]){
    for(int i=Y-1; i>=0;i--){
        for(int j=X-1; j>=0;j--){
            if(tab[i][j]==tab[i][j-1] && tab[i][j]==tab[i][j-2]){
                tab[i][j]=0;
                tab[i][j-1]=0;
                tab[i][j-2]=0;
                replace(tab);
                return 1;
            }
        }
    }
    return 0;
}

int vertical3(int tab[Y][X]){
    for(int i=Y-1; i>=0;i--){
        for(int j=X-1; j>=0;j--){
            if(tab[i][j]==tab[i-1][j] && tab[i][j]==tab[i-2][j]){
                tab[i][j]=0;
                tab[i-1][j]=0;
                tab[i-2][j]=0;
                replace(tab);
                return 1;
            }
        }
    }
    return 0;
}

int recherche_formes(int tab[Y][X]){
    srand(time(NULL));
    int count;
    do{
        count = 0;
        count += horizontal4(tab);
        count += vertical4(tab);
        count += horizontal3(tab);
        count += vertical3(tab);
    }while(count >0);
    return 0;
}