#include <stdio.h>
#include <windows.h>

#include "const.h"
#include "visual.h"
#include "create.h"

int takecoo(int *y, int *x){
    //system("cls");
    printf("Entrez les coordonnées y et x de l'objet à sélectionner :\n");
    scanf("%d",&*y);
    scanf("%d",&*x);
    int direction;
    printf("Entrez la direction \n1.haut\n2.bas\n3.gauche\n4.droite\n");
    scanf("%d",&direction);
    return direction;
}

void change(int tab[Y][X], int y, int x, int direction){
    int temp;
    switch(direction){
        case 1:
            temp = tab[y][x];
            tab[y][x]=tab[y-1][x];
            tab[y-1][x] = temp;
            break;
        case 2:
            temp = tab[y][x];
            tab[y][x]=tab[y+1][x];
            tab[y+1][x] = temp;
            break;
        case 3:
            temp = tab[y][x];
            tab[y][x]=tab[y][x-1];
            tab[y][x-1] = temp;
            break;
        case 4:
            temp = tab[y][x];
            tab[y][x]=tab[y][x+1];
            tab[y][x+1] = temp;
            break;
    }
}

void level1(){
    int tab[Y][X];
    createtab(tab);
    viewmap(tab);
    int coups = 10;
    int x,y,direction;
    do{
        direction = takecoo(&y,&x);
        change(tab,y,x,direction);
        viewmap(tab);
        coups--;
    }while(coups!=0);
}

void new_game(){
    //niveau unique pour le moment
    level1();
}