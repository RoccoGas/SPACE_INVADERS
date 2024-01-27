// main.c : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>

#include "allegro.h"
#include "menu.h"
#include "header.h"
#include "initialize.h"


int main(){


    srand(time(NULL));
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

    player_t player;
    if (!init_player(&player)) {
        printf("Failed to initialize player\n");
    }

    bool mainLoop = true;
    enum LEVEL_OPTIONS_E mainOptions;
    int difficulty = 1;
    bool menuFlag = false;
    while (mainLoop) {
        if (menuFlag == false) {
            mainOptions = start_menu(display);
            menuFlag = true;
        }
        switch (mainOptions) {
        case NO_ERROR_CONTINUE_TO_LEVEL_ONE:
             mainOptions = play_level(display, &player, difficulty, 1);
             printf("saliendo de level one main options es: %d\n", mainOptions);
            break;
        case NO_ERROR_CONTINUE_TO_LEVEL_TWO:
            mainOptions = play_level(display, &player, difficulty, 2);
            break;
        case NO_ERROR_CONTINUE_TO_LEVEL_THREE:
            mainOptions = play_level(display, &player, difficulty, 3);
            break;
        case FINISHED_GAME:
            draw_win_screen();
            printf("GANSTEEEE!!!!!!!!");
            menuFlag = false;
            break;
        case BAD_ASSET:
            printf("Error en la carga de assets!");
            mainLoop = false;
            break;
        case QUIT_TO_MENU:
            menuFlag = false;
            break;
        case QUIT_GAME:
            mainLoop = false;
            break;
        case DIFFICULTY:
            difficulty_menu(display, &difficulty);
            menuFlag = false;
            break;
        }


    }

    al_destroy_display(display);
    destroy_allegro();

    printf("HOLA!");
    return 0;
}


