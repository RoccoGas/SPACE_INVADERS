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

    bool mainLoop = true;
    enum LEVEL_OPTIONS_E mainOptions;
    while (mainLoop) {
        mainOptions = start_menu(display);
        switch (mainOptions) {
        case NO_ERROR_CONTINUE_TO_LEVEL_ONE:
             mainOptions = level_one(display, player);
            break;
        case BAD_ASSET:
            printf("Error en la carga de assets!");
            mainLoop = false;
            break;
        case QUIT_GAME:
            mainLoop = false;
            break;
        case QUIT_TO_MENU:
            break;
        }


    }

    al_destroy_display(display);
    destroy_allegro();

    printf("HOLA!");
    return 0;
}


