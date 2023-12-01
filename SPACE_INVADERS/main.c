// main.c : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>

#include "allegro.h"
#include "menu.h"
#include "header.h"

ALLEGRO_DISPLAY* display;
playerStatus* player;

int main(){


    if (!initialize_allegro()) {
        printf("Unable to start because allegro was not properly initialized...");
        return -1;
    }
    start_menu(display);


    destroy_allegro();
    return 0;
}


