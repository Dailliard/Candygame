#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "chrono.h"
#include "const.h"

void start_timer(int duration) {
    end_time = time(NULL) + duration;
}

int remaining_time() {
    int time_r = (int)((end_time - time(NULL)));// Temps restant 
    if (time_r < 0){
        time_r = 0;
    }
    return time_r;
}

void show_time() {
    int seconds = remaining_time();
    int mins = seconds / 60;
    int secs_r = seconds % 60;

    if(seconds>0){
        printf("Temps restant: %02d:%02d\n", mins, secs_r);
        fflush(stdout);
    }
    if(remaining_time() == 0) {
        printf("\nTemps écoulé!\n");
    }
}