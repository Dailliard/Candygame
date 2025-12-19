#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "const.h"
#include "visual.h"
#include "forme.h"

void add(int tab[Y][X]){
    for(int y = 0; y < Y; y++){
        for(int x = 0; x < X; x++){
            if(tab[y][x] == 0){
                tab[y][x] = rand() % 5 + 1;
            }
        }
    }
}

void descendre(int tab[Y][X]){
    for(int y = Y-1; y > 0; y--){
        for(int x = X-1; x >= 0; x--){
            if(tab[y][x] == 0){
                if(tab[y-1][x]==0){
                    for(int i=y;i>=0;i--){
                        if(tab[i][x]!=0){
                           int temp = tab[y][x];
                            tab[y][x] = tab[i][x];
                            tab[i][x] = temp;
                            break;
                        }
                    }
                }else{
                    int temp = tab[y][x];
                    tab[y][x] = tab[y-1][x];
                    tab[y-1][x] = temp;
                }
            }
        }
    }
}

void replace(int tab[Y][X]){
    descendre(tab);
    add(tab);
}

int malus(int tab[Y][X], Donnees *data){
    for(int i = 1; i < Y; i++){
        for(int j = 1; j < X; j++){
            if(tab[i][j] != 0 &&
               tab[i][j] == tab[i][j-1] &&
               tab[i][j] == tab[i-1][j] &&
               tab[i][j] == tab[i-1][j-1]){

                data->Contrat[tab[i][j]][0] -= 8;

                tab[i][j] = 0;
                tab[i][j-1] = 0;
                tab[i-1][j] = 0;
                tab[i-1][j-1] = 0;

                replace(tab);
                return 1;
            }
        }
    }
    return 0;
}


int bonuslife(int tab[Y][X], Donnees *data){
    for(int i = 2; i < Y; i++){
        for(int j = 2; j < X; j++){
            if(tab[i][j]==4 && tab[i-1][j-1]==6){
                if(tab[i][j]==tab[i][j-1] &&
                    tab[i][j]==tab[i][j-2]){

                    if(tab[i][j]==tab[i-1][j] &&
                        tab[i][j]==tab[i-2][j]){

                        if(tab[i][j]==tab[i-2][j-1] &&
                            tab[i][j]==tab[i-2][j-2]){

                            if(tab[i][j]==tab[i-1][j-2] &&
                                tab[i][j]==tab[i-2][j-2]){
                                
                                int temp = tab[i][j];
                                for(int z = i-2; z <= i; z++){
                                    for(int a = j-2; a <= j; a++){
                                            tab[z][a] = 0;
                                    }
                                }
                                replace(tab);
                                if(data->vies<3)data->vies++;
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int carre(int tab[Y][X], Donnees *data){
    for(int i = 3; i < Y; i++){
        for(int j = 3; j < X; j++){
            if(tab[i][j]==tab[i][j-1] &&
                 tab[i][j]==tab[i][j-2] &&
                  tab[i][j]==tab[i][j-3]){

                if(tab[i][j]==tab[i-1][j] &&
                     tab[i][j]==tab[i-2][j] &&
                      tab[i][j]==tab[i-3][j]){

                    if(tab[i][j]==tab[i-3][j-1] &&
                         tab[i][j]==tab[i-3][j-2] &&
                          tab[i][j]==tab[i-3][j-3]){

                        if(tab[i][j]==tab[i-1][j-3] &&
                             tab[i][j]==tab[i-2][j-3] &&
                              tab[i][j]==tab[i-3][j-3]){
                            
                            int temp = tab[i][j];
                            for(int z = i-3; z <= i; z++){
                                for(int a = j-3; a <= j; a++){
                                    if(tab[z][a] == temp){
                                        data->Contrat[temp][0]++;
                                        tab[z][a] = 0;
                                    }
                                    
                                }
                            }
                            replace(tab);
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int croix(int tab[Y][X], Donnees *data){
    for(int i = 2; i < Y-2; i++){
        for(int j = 2; j < X-2; j++){
            if(tab[i][j]==tab[i][j-1] &&
                 tab[i][j]==tab[i][j-2] &&
                  tab[i][j]==tab[i][j+1] &&
                   tab[i][j]==tab[i][j+2]){

                if(tab[i][j]==tab[i-1][j] &&
                     tab[i][j]==tab[i-2][j] &&
                      tab[i][j]==tab[i+1][j] &&
                       tab[i][j]==tab[i+2][j]){

                    int temp = tab[i][j];
                    for(int z = 0; z < X; z++){
                        if(tab[i][z] == temp){
                            tab[i][z] = 0;
                            data->Contrat[temp][0]++;
                        }
                        
                    }
                    for(int z = 0; z < Y; z++){
                        if(tab[z][j] == temp){
                            tab[z][j] = 0;
                            data->Contrat[temp][0]++;
                        }
                        
                    }
                    replace(tab);
                    return 1;
                }
            } 
        }
    }
    return 0;
}

int horizontal8(int tab[Y][X], Donnees *data){
    for(int i = 0; i < Y; i++){
        for(int j = 7; j < X; j++){
            if(tab[i][j]==tab[i][j-1] &&
                 tab[i][j]==tab[i][j-2] &&
                  tab[i][j]==tab[i][j-3] &&
                   tab[i][j]==tab[i][j-4] &&
                    tab[i][j]==tab[i][j-5] &&
                     tab[i][j]==tab[i][j-6] &&
                      tab[i][j]==tab[i][j-7]){

                int temp = tab[i][j];
                for(int a = 0; a < X; a++){
                    if(tab[i][a] == temp){
                         data->Contrat[temp][0]++;
                         tab[i][a] = 0; 
                    }
                }
                tab[i][j]=6;
                replace(tab);
                return 1;
            }
        }
    }
    return 0;
}

int vertical8(int tab[Y][X], Donnees *data){
    for(int i = 7; i < Y; i++){
        for(int j = 0; j < X; j++){
            if(tab[i][j]==tab[i-1][j] &&
                 tab[i][j]==tab[i-2][j] &&
                  tab[i][j]==tab[i-3][j] &&
                   tab[i][j]==tab[i-4][j] &&
                    tab[i][j]==tab[i-5][j] &&
                     tab[i][j]==tab[i-6][j] &&
                      tab[i][j]==tab[i-7][j]){

                int temp = tab[i][j];
                for(int z = 0; z < Y; z++){
                    if(tab[z][j] == temp){
                        tab[z][j] = 0;
                        data->Contrat[temp][0]++;
                    }
                }
                tab[i][j]=6;
                replace(tab);
                return 1;
            }
        }
    }
    return 0;
}

int horizontal6(int tab[Y][X], Donnees *data){
    for(int i = 0; i < Y; i++){
        for(int j = 5; j < X; j++){
            if(tab[i][j]==tab[i][j-1] &&
                 tab[i][j]==tab[i][j-2] &&
                  tab[i][j]==tab[i][j-3] &&
                   tab[i][j]==tab[i][j-4] &&
                    tab[i][j]==tab[i][j-5]){

                int temp = tab[i][j];
                for(int a = 0; a < X; a++){
                    if(tab[i][a] == temp){
                         data->Contrat[temp][0]++;
                         tab[i][a] = 0; 
                    }
                }
                replace(tab);
                return 1;
            }
        }
    }
    return 0;
}

int vertical6(int tab[Y][X], Donnees *data){
    for(int i = 5; i < Y; i++){
        for(int j = 0; j < X; j++){
            if(tab[i][j]==tab[i-1][j] &&
                 tab[i][j]==tab[i-2][j] &&
                  tab[i][j]==tab[i-3][j] &&
                   tab[i][j]==tab[i-4][j] &&
                    tab[i][j]==tab[i-5][j]){

                int temp = tab[i][j];
                for(int z = 0; z < Y; z++){
                    if(tab[z][j] == temp){
                        tab[z][j] = 0;
                        data->Contrat[temp][0]++;
                    }
                }
                replace(tab);
                return 1;
            }
        }
    }
    return 0;
}

int horizontal4(int tab[Y][X], Donnees *data){
    for(int i = Y-1; i >=0; i--){
        for(int j = 3; j < X; j++){
            if(tab[i][j]==tab[i][j-1] && tab[i][j]==tab[i][j-2] && tab[i][j]==tab[i][j-3]){
                data->Contrat[tab[i][j]][0]+=4;
                tab[i][j] = 0;
                tab[i][j-1] = 0;
                tab[i][j-2] = 0;
                tab[i][j-3] = 0;
                replace(tab);
                return 1;
            }
        }
    }
    return 0;
}

int vertical4(int tab[Y][X], Donnees *data){
    for(int i = 3; i < Y; i++){
        for(int j = 0; j < X; j++){
            if(tab[i][j]==tab[i-1][j] && tab[i][j]==tab[i-2][j] && tab[i][j]==tab[i-3][j]){
                data->Contrat[tab[i][j]][0]+=4;
                tab[i][j] = 0;
                tab[i-1][j] = 0;
                tab[i-2][j] = 0;
                tab[i-3][j] = 0;
                replace(tab);
                return 1;
            }
        }
    }
    return 0;
}

int recherche_formes(int tab[Y][X], Donnees *data){
    srand(time(NULL));
    int count;
    do{
        count = 0;
        if(data->level>1){
            if(data->level>2){
                count+=malus(tab, data);
            }
            count += bonuslife(tab, data);
            count += horizontal8(tab, data);
            count += vertical8(tab, data);
        }
        count += carre(tab, data);
        count += croix(tab, data);
        count += horizontal6(tab, data);
        count += vertical6(tab, data);
        count += horizontal4(tab, data);
        count += vertical4(tab, data);
    }while(count > 0);
    return 0;
}
