#ifndef VISUAL_H
#define VISUAL_H

#include "const.h"
//Gestion des issues de la partie
void winlevel(Donnees *data);                                               // Victoire de niveau
void wingame(Donnees *data);                                                // Victoire finale
void looselevel(Donnees *data);                                             // Défaite de niveau
void loosegame(Donnees *data);                                              // Défaite finale
void affichagetemps(Donnees *data);                                         // Affichage du temps restant
void affichage_partie(int tab[Y][X], Donnees *data,int y, int x,int sel);
void viewmap(int tab[Y][X], int a, int b,int sel);

void menu(void);

#endif
