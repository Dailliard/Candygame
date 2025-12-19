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
#include "affichage_console.h"
#include "music.h"

void issues(Donnees *data){
    if(data->etat==5){
        if(data->level==3){
            wingame(data);
        }else{
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
    data->view=0;
    createtab(tab, data);
    data->view=1;
    for(int i=1;i<6;i++){
        data->Contrat[i][0]=0;
    }
    int x=0, y=0;
    char action = 0;
    int lastTemps = -1;
    data->tempsR = data->tempsM - time(NULL);
    affichage_partie(tab, data, y, x, sel);
    lastTemps = data->tempsR;
    while(1){
        data->tempsR = data->tempsM - time(NULL);
        if(kbhit()){
            action = getch();
            if (action == '6')demarrer_musique();
            if(action =='7')arreter_musique();
            int moved = 0;
            if(sel==0){
                if (action == 'z' && y!=0) { y--; moved = 1; }
                if (action == 's' && y!=Y-1) { y++; moved = 1; }
                if (action == 'q' && x!=0) { x--; moved = 1; }
                if (action == 'd' && x!=X-1) { x++; moved = 1; }
            }else{
                if (action == 'z' && y!=0){change(tab,y,x,1);sel=0;y--;data->coups--;moved=1;}
                if (action == 's' && y!=Y-1){change(tab,y,x,2);sel=0;y++;data->coups--;moved=1;}
                if (action == 'q' && x!=0){change(tab,y,x,3);sel=0;x--;data->coups--;moved=1;}
                if (action == 'd' && x!=X-1){change(tab,y,x,4);sel=0;x++;data->coups--;moved=1;}
            }
            if (action == ' '){
                if(sel == 0)sel=1;
                else sel=0;
                moved = 1;
            }
            if(moved){
                recherche_formes(tab, data);
                affichage_partie(tab, data, y, x, sel);
                affichagetemps(data);
                lastTemps = data->tempsR;
            }
        } else {
            if(data->tempsR != lastTemps){
                affichagetemps(data);
                lastTemps = data->tempsR;
            }
        }
        data->etat=0;
        for(int i=0;i<5;i++){
            if(data->Contrat[i+1][0]>=data->Contrat[i+1][1])data->etat++;
        }
        if (data->coups==0 || action == 'p' || data->etat == 5 || data->tempsR <= 0){
            issues(data);
            break;
        }
        Sleep(50);
    }
}

void level1(char pseudo[21],int vie){
    Donnees data;
    data.level = 1;
    data.coups = 35;
    data.vies = vie;
    data.tempsM = 300;
    strcpy(data.pseudo,pseudo);
    start_timer(&data);
    data.Contrat[1][1]=10;
    data.Contrat[2][1]=20;
    data.Contrat[3][1]=10;
    data.Contrat[4][1]=15;
    data.Contrat[5][1]=20;
    partie(&data);
}

void level2(char pseudo[21],int vie){
    Donnees data;
    data.level = 2;
    data.coups = 45;
    data.vies = vie;
    data.tempsM = 120;
    strcpy(data.pseudo,pseudo);
    start_timer(&data);
    data.Contrat[1][1]=50;
    data.Contrat[2][1]=30;
    data.Contrat[3][1]=25;
    data.Contrat[4][1]=60;
    data.Contrat[5][1]=20;
    partie(&data);
}

void level3(char pseudo[21],int vie){
    Donnees data;
    data.level = 3;
    data.coups = 75;
    data.vies = vie;
    data.tempsM = 120;
    strcpy(data.pseudo,pseudo);
    start_timer(&data);
    data.Contrat[1][1]=100;
    data.Contrat[2][1]=50;
    data.Contrat[3][1]=100;
    data.Contrat[4][1]=50;
    data.Contrat[5][1]=100;
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
                switch(temp2){
                    case 1:
                        fclose(f);
                        level1(pseudo,temp1);
                        break;
                    case 2:
                        fclose(f);
                        level2(pseudo,temp1);
                        break;
                    case 3:
                        fclose(f);
                        level3(pseudo,temp1);
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
    CopyFile("temp.txt", ENREGISTREMENT, FALSE);
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
    int verif=0;
    system("cls");
    printf("Entrez votre pseudo : ");
    do{
        FILE *f = fopen(ENREGISTREMENT, "r");
        fgets(pseudo,21,stdin);
        pseudo[strlen(pseudo)-1]='\0';
        if(f==NULL)verif=0;
        else{
            char temps[21];
            int temp1,temp2;
            char ligne[256];
            verif=0;
            while(fgets(ligne,sizeof(ligne), f)!=NULL){
                if(sscanf(ligne, "%[^;];%d;%d",temps,&temp1,&temp2)==3){
                    if(strcmp(temps,pseudo) == 0){
                        verif=1;
                        system("cls");
                        printf("Pseudo déjà pris choisissez-en un autre !\n");
                        f=0;
                        break;
                    }
                }
            }
        }
    fclose(f);
    }while(verif==1);
    FILE *d = fopen(ENREGISTREMENT, "a");
    fprintf(d, "%s;%d;%d\n", pseudo, 3, 1);
    fclose(d);
    level1(pseudo,3);
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
            char action='0';
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
