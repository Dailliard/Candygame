#ifndef CONST_H
#define CONST_H

#include <time.h>

#define Y 15
#define X 15
#define CONSOLE_WIDTH 100
#define ENREGISTREMENT "Sauvegarde.txt"

typedef struct {
    char pseudo[21];
    int level;
    int vies;
    int Contrat[6][2];
    int coups;
    int etat;
    int tempsR;
    int tempsM;
    int view;
} Donnees;
#endif