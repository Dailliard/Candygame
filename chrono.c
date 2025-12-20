#include <stdio.h>
#include <time.h>

#include "chrono.h"
#include "const.h"

// Démarrer le chronomètre
void start_timer(Donnees *data) {
    data->tempsM += time(NULL); 
}

// Afficher le temps au format minutes:secondes
void show_time(int temps) {
    int seconds = temps;
    int mins = seconds / 60;             // Calculer les minutes
    int secs_r = seconds % 60;           // Calculer les secondes restantes
    printf("%02d:%02d", mins, secs_r); 
}