#include <stdio.h>
#include <windows.h>

#include "const.h"
#include "visual.h"
#include "create.h"
#include "forme.h"

int takecoo(int *y, int *x, Donnees *data){
    for(int i=1;i<6;i++){
        printf("|%d : %d / %d |",i,data->Contrat[i][0],data->Contrat[i][1]);
    }
    printf("\nEntrez les coordonnees y et x de l'objet a selectionner :\n");
    scanf("%d", y);
    scanf("%d", x);
    int direction;
    printf("Entrez la direction \n1.haut\n2.bas\n3.gauche\n4.droite\n");
    scanf("%d", &direction);
    return direction;
}

void change(int tab[Y][X], int y, int x, int direction){
    int temp;
    switch(direction){
        case 1:
            temp = tab[y][x];
            tab[y][x] = tab[y-1][x];
            tab[y-1][x] = temp;
            break;
        case 2:
            temp = tab[y][x];
            tab[y][x] = tab[y+1][x];
            tab[y+1][x] = temp;
            break;
        case 3:
            temp = tab[y][x];
            tab[y][x] = tab[y][x-1];
            tab[y][x-1] = temp;
            break;
        case 4:
            temp = tab[y][x];
            tab[y][x] = tab[y][x+1];
            tab[y][x+1] = temp;
            break;
    }
}

void level1(){
    Donnees data;
    data.level = 1;
    data.score = 0;
    for(int i=1;i<6;i++){
        data.Contrat[i][0]=0;
        data.Contrat[i][1]=10;
    }
    
    int tab[Y][X];
    createtab(tab, &data);
    viewmap(tab);
    
    int coups = 10;
    int x, y, direction;
    
    do{
        direction = takecoo(&y, &x, &data);
        change(tab, y, x, direction);
        recherche_formes(tab, &data);
        viewmap(tab);
        coups--;
    }while(coups != 0);
}

void new_game(){
    level1();
}
