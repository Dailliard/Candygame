#ifndef CONST_H
#define CONST_H

#include <time.h>

#define Y 15
#define X 15
#define CONSOLE_WIDTH 100

typedef struct {
    int level;
    int vies;
    int Contrat[6][2];
    int coups;
    int etat;
} Donnees;

static time_t end_time;

#endif

