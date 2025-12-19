#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>

#include "music.h"
#include "affichage_console.h"

#pragma comment(lib, "winmm.lib")

static int musique_en_cours = 0;

void demarrer_musique(void) {

    if (musique_en_cours) {
        return;
    }
    
    MCIERROR erreur;
    erreur = mciSendString("open \"musique_jeu.mp3\" type mpegvideo alias bgmusic", NULL, 0, NULL);
    if (erreur) {
        gotoxy(0, 19);
        printf("Erreur ouverture musique: %d\n", erreur);
        return;
    }
    
    erreur = mciSendString("play bgmusic repeat", NULL, 0, NULL);
    if (erreur) {
        printf("Erreur lecture musique: %d\n", erreur);
    } else {
        gotoxy(0, 19);
        printf("Musique démarrée !\n");
        musique_en_cours = 1;
    }
}

void arreter_musique(void) {
    if (musique_en_cours) {
        mciSendString("stop bgmusic", NULL, 0, NULL);
        mciSendString("close bgmusic", NULL, 0, NULL);
        musique_en_cours = 0;
        gotoxy(0, 19);
        printf("Musique arrêtée.\n");
    }
}
