#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

#include "const.h"
#include "visual.h"
#include "create.h"
#include "forme.h"
#include "chrono.h"

void issues(Donnees *data){

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

void partie(Donnees *data){
    int tab[Y][X];
    int sel=0;
    createtab(tab, data);
    affichage_partie(tab, data, 0, 0, sel, 0);
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
        
        recherche_formes(tab, data);
        affichage_partie(tab, data, y, x, sel, 0);
        data->etat=0;
        for(int i=0;i<5;i++){
            if(data->Contrat[i+1][0]>=data->Contrat[i+1][1])data->etat++;
        }
        if (data->coups==0 || action == 'p' || data->etat == 5){
            issues(data);
            break;
        }
    }while(action = getch());
}

void level1(char pseudo[21]){
    Donnees data;
    data.level = 1;
    data.coups = 50;
    strcpy(data.pseudo,pseudo);
    start_timer(120);
    for(int i=1;i<6;i++){
        show_time();
        data.Contrat[i][1]=50;
    }
    partie(&data);
}

void level2(char pseudo[21]){
    Donnees data;
    data.level = 2;
    data.coups = 75;
    strcpy(data.pseudo,pseudo);
    start_timer(120);
    for(int i=1;i<6;i++){
        show_time();
        data.Contrat[i][1]=100;
    }
    partie(&data);
}

void level3(char pseudo[21]){
    Donnees data;
    data.level = 3;
    data.coups = 100;
    strcpy(data.pseudo,pseudo);
    start_timer(120);
    for(int i=1;i<6;i++){
        show_time();
        data.Contrat[i][1]=150;
    }
    partie(&data);
}

void takepseudo(char pseudo[21]){
    FILE *f = fopen(ENREGISTREMENT, "r");
    int verif=0;
    do{
        printf("Entrez votre pseudo");
        fgets(pseudo,21,stdin);
        pseudo[strlen(pseudo)-1]='\0';
        if(f==NULL)verif=0;
        else{
            char temps[21];
            int temp1,temp2;
            char ligne[256];
            while(fgets(ligne,sizeof(ligne), f)!=NULL){
                if(sscanf(ligne, "%[^;];%d;%d",temps,&temp1,&temp2)==3){
                    if(strcmp(temps,pseudo) == 0){
                        verif=1;
                        printf("Pseudo déja pris choisissez-en un autre !\n");
                        break;
                    }
                }
            }
            verif=0;
        }
    }while(verif==1);
    fclose(f);
}

void new_game(){
    char pseudo[21];
    takepseudo(pseudo);
    level1(pseudo);
}
