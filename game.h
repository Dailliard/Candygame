#ifndef GAME_H
#define GAME_H

#include "const.h"

//Charge le niveau correspondant au pseudo
void chargelevel(char pseudo[21]);

//Sauvegarde des données du jeu
void sauvegarder(Donnees *data);
void supprimer(Donnees *data);

//Démarrer une nouvelle partie/charger une partie sauvegardée
void new_game(void);
void charge_game(void);

#endif
