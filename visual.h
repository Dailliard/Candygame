#ifndef VISUAL_H
#define VISUAL_H

#include "const.h"

void winlevel(Donnees *data);
void wingame(Donnees *data);
void looselevel(Donnees *data);
void loosegame(Donnees *data);


void affichage_partie(int tab[Y][X], Donnees *data,int y, int x,int sel, int sec_r);
void viewmap(int tab[Y][X], int a, int b,int sel);

void menu(void);

#endif
