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
    if(data->etat==5){
        if(data->level==3){
            wingame(data);
        }else{
            data->level++;
            winlevel(data);
        }
    }else{
        if(data->vies==1){
            loosegame(data);
        }else{
            data->vies--;
            looselevel(data);
        }
    }
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
        data.Contrat[i][1]=4;
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

void chargelevel(char pseudo[21]){
    FILE *f = fopen(ENREGISTREMENT, "r");
    char temps[21];
    int temp1,temp2;
    char ligne[256];
    while(fgets(ligne,sizeof(ligne), f)!=NULL){
        if(sscanf(ligne, "%[^;];%d;%d",temps,&temp1,&temp2)==3){
            if(strcmp(temps,pseudo) == 0){
                switch(temp1){
                    case 1:
                        level1(pseudo);
                        break;
                    case 2:
                        level2(pseudo);
                        break;
                    case 3:
                        level3(pseudo);
                        break;
                }
                break;
            }
        }
    }
}

void sauvegarder(Donnees *data){
    FILE *f = fopen(ENREGISTREMENT, "r");
    FILE *temp = fopen("temp.txt", "w");
    
    char ligne[256];
    
    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        char pseudo_lu[21];
        int vie, level;
        
        if (sscanf(ligne, "%[^;];%d;%d", pseudo_lu, &vie, &level) == 3) {
            if (strcmp(pseudo_lu, data->pseudo) == 0) {
                fprintf(temp, "%s;%d;%d\n", data->pseudo,data->vies, data->level);
            } else {
                fprintf(temp, "%s", ligne);
            }
        }
    }
    fclose(f);
    fclose(temp);
    remove(ENREGISTREMENT);
    rename("temp.txt", ENREGISTREMENT);
}

void supprimer(Donnees *data){
    FILE *f = fopen(ENREGISTREMENT, "r");
    FILE *temp = fopen("temp.txt", "w");
    
    char ligne[256];
    
    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        char pseudo_lu[21];
        int vie, level;
        
        if (sscanf(ligne, "%[^;];%d;%d", pseudo_lu, &vie, &level) == 3) {
            if (strcmp(pseudo_lu, data->pseudo) == 0);
            else {
                fprintf(temp, "%s", ligne);
            }
        }
    }
    fclose(f);
    fclose(temp);
    remove(ENREGISTREMENT);
    rename("temp.txt", ENREGISTREMENT);
}

void new_game(){
    char pseudo[21];
    FILE *f = fopen(ENREGISTREMENT, "r");
    int verif=0;
    system("cls");
    printf("Entrez votre pseudo : ");
    do{
        
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
                        system("cls");
                        printf("Pseudo déja pris choisissez-en un autre !\n");
                        break;
                    }
                }
            }
            verif=0;
        }
    }while(verif==1);
    fclose(f);
    FILE *d = fopen(ENREGISTREMENT, "a");
    fprintf(d, "%s;%d;%d\n", pseudo, 3, 1);
    fclose(d);
    level1(pseudo);
}

void charge_game(){
    system("cls");
    char pseudo[21];
    FILE *f = fopen(ENREGISTREMENT, "r");
    if(f==NULL){
        do{
            printf("Attention aucune sauvegarde !\n");
            printf("Cliquer sur une touche");
        }while(!getch());
        return;
    }
    int verif=0;
    
    do{
        system("cls");
        printf("Entrez votre pseudo : ");
        fgets(pseudo,21,stdin);
        pseudo[strlen(pseudo)-1]='\0';
        char temps[21];
        int temp1,temp2;
        char ligne[256];
        while(fgets(ligne,sizeof(ligne), f)!=NULL){
            if(sscanf(ligne, "%[^;];%d;%d",temps,&temp1,&temp2)==3){
                if(strcmp(temps,pseudo) == 0){
                    verif=1;
                    chargelevel(pseudo);
                    return;
                }
            }
        }
        if(verif==0){
            char action;
            do{
                if(action=='1'){
                    verif=0;
                    break;
                }
                if(action=='2'){
                    new_game();
                    verif=1;
                    break;
                }
                system("cls");
                printf("Pseudo Inexistant !\n");
                printf("1. Essayer un autre pseudo\n");
                printf("2. Jouer une nouvelle partie\n");
            }while(action = getch());
        }
    }while(verif==0);
}
