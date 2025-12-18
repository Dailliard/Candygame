#include <stdio.h>
#include <conio.h>
#include <windows.h>

#include "const.h"
#include "visual.h"
#include "create.h"
#include "forme.h"
#include "chrono.h"

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

void partie(Donnees *data){
    int tab[Y][X];
    int sel=0;
    createtab(tab, data);
    viewmap(tab,0,0,sel);
    for(int i=1;i<6;i++){
        data->Contrat[i][0]=0;
    }
    int x=0, y=0;
    char action;
    do{
        if(sel==0){
            if (action == 'z' && y!=0) y--;
            if (action == 's' && y!=Y-1) y++;
            if (action == 'q' && x!=0) x--;
            if (action == 'd' && x!=X-1) x++;
        }else{
            if (action == 'z' && y!=0){change(tab,y,x,1);sel=0;y--;data->coups--;}
            if (action == 's' && y!=Y-1){change(tab,y,x,2);sel=0;y++;data->coups--;}
            if (action == 'q' && x!=0){change(tab,y,x,3);sel=0;x--;data->coups--;}
            if (action == 'd' && x!=X-1){change(tab,y,x,4);sel=0;x++;data->coups--;}
        }
        if (action == ' '){
            if(sel == 0)sel=1;
            else sel=0;
        }
        if(action == 'g')affichage_partie(tab,data,sel);
        if (data->coups==0 || action == 'p')break;
        recherche_formes(tab, data);
        viewmap(tab, y, x, sel);
        
    }while(action = getch());
}

void level1(){
    Donnees data;
    data.level = 1;
    data.coups = 10;
    start_timer(120);
    for(int i=1;i<6;i++){
        show_time();
        data.Contrat[i][1]=10;
    }
    partie(&data);
}

void new_game(){
    level1();
}
