#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>

#include "music.h"
#include "affichage_console.h"

#pragma comment(lib, "winmm.lib")

static int musique_en_cours = 0;
//Fonction pour démarrer la musique de fond
void demarrer_musique(void) {

    if (musique_en_cours) { // La musique est déjà en cours
        return;
    }

    MCIERROR erreur; 
    erreur = mciSendString("open \"musique_jeu.mp3\" type mpegvideo alias bgmusic", NULL, 0, NULL); // Ouvrir le fichier musique
    if (erreur) {                                                           // Vérifier les erreurs lors de l'ouverture du fichier
        gotoxy(0, 19);                                                      // Déplacer le curseur pour afficher le message
        printf("Erreur ouverture musique: %d\n", erreur);
        return;
    }
    // Lire le fichier musique en boucle
    erreur = mciSendString("play bgmusic repeat", NULL, 0, NULL);
    if (erreur) {                                                           // Vérifier les erreurs lors de la lecture du fichier
        printf("Erreur lecture musique: %d\n", erreur);
    } else {                                                                // Musique démarrée avec succès
        gotoxy(0, 19);                                                      // Déplacer le curseur pour afficher le message
        printf("Musique démarrée !\n");
        musique_en_cours = 1;
    }
}
//Fonction pour arrêter la musique de fond
void arreter_musique(void) {
    if (musique_en_cours) {                                                 // La musique est en cours
        mciSendString("stop bgmusic", NULL, 0, NULL);                       // Arrêter la musique
        mciSendString("close bgmusic", NULL, 0, NULL);                      // Fermer le fichier musique
        musique_en_cours = 0;                                               // Mettre à jour l'état de la musique
        gotoxy(0, 19);                                                      // Déplacer le curseur pour afficher le message
        printf("Musique arrêtée.\n");
    }
}
