// main.c : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>

#include "allegro.h"
#include "menu.h"
#include "header.h"
#include "initialize.h"


int main(){
    if (!initialize_allegro()) {
        printf("Unable to start because allegro was not properly initialized...");
        return -1;
    }

    ALLEGRO_DISPLAY* display;
    display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    if (display == NULL) {
        fprintf(stdout, "Failed to create display\n");
        return false;
    }

    playerStatus player;
    if (!init_player(&player)) {
        printf("Failed to initialize player\n");
    }


    start_menu(display);
    level_one(display, player);


    destroy_allegro();
    return 0;
}


