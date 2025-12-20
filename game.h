#ifndef GAME_H
#define GAME_H
//Structure des données du jeu
void chargelevel(char pseudo[21]);
//Sauvegarde des données du jeu
void sauvegarder(Donnees *data);
void supprimer(Donnees *data);
//Démarrer une nouvelle partie
void new_game(void);
void charge_game(void);

#endif
