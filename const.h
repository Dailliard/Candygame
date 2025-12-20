#ifndef CONST_H
#define CONST_H

#include <time.h>

#define Y 15                               // hauteur du plateau
#define X 15                               // largeur du plateau    
#define CONSOLE_WIDTH 100                  // largeur de la console utilisée pour l'affichage
#define ENREGISTREMENT "Sauvegarde.txt"    // nom du fichier de sauvegarde

//Structure des données du jeu
typedef struct {
    char pseudo[21];                       // Pseudo du joueur
    int level;                             // Niveau actuel
    int vies;                              // Nombre de vies restantes
    int Contrat[6][2];                     // Objectifs des contrats
    int coups;                             // Coups restants
    int etat;                              // État des contrats
    int tempsR;                            // Temps restant
    int tempsM;                            // Temps maximum pour le niveau
    int view;                              // Mode d'affichage
} Donnees;

#endif