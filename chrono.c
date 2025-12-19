#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "chrono.h"
#include "const.h"

void start_timer(Donnees *data) {
    data->tempsM += time(NULL);
}

void show_time(int temps) {
    int seconds = temps;
    int mins = seconds / 60;
    int secs_r = seconds % 60;
    printf("%02d:%02d", mins, secs_r);
}