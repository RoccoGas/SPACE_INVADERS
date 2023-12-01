// main.c : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>

#include "allegro.h"
#include "menu.h"
#include "header.h"

playerStatus* player;

int main(){

    if (!initialize_allegro()) {
        printf("Unable to start because allegro was not properly initialized...");
        return -1;
    }

    ALLEGRO_DISPLAY* display;
    display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);

    start_menu(display);
    level_one(display, player);


    destroy_allegro();
    return 0;
}


