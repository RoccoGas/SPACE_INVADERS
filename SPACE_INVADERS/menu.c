
#include "menu.h"
#include "allegro.h"
#include "header.h"

#include <stdio.h>

enum LEVEL_OPTIONS_E start_menu(ALLEGRO_DISPLAY* display) {
    printf("[START MENU]\n");

    al_reserve_samples(1); // Para la musica del menu

    ALLEGRO_BITMAP* bitmapBackround;
    ALLEGRO_BITMAP* bitmapSpace;
    ALLEGRO_FONT* font;
    ALLEGRO_SAMPLE* menuMusicSample;
    ALLEGRO_SAMPLE_INSTANCE* menuMusic;


    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_TIMER* timer;

    ALLEGRO_EVENT event;
    ALLEGRO_KEYBOARD_STATE keyboardState;
    ALLEGRO_MOUSE_STATE mouseState;

    const char* bitmapBackgroundFilepath = "assets/menu/space_invaders_logo.png";
    const char* bitmapSpaceFilepath = "assets/menu/space3.jpg";
    const char* fontFilepath = "assets/menu/space_invaders_font.ttf";
    const char* menuMusicSampleFilenpath = "assets/menu/Cirno_Fortress_Stage_1.wav";

    enum DIFFICULTY_OPTIONS_E difficulty = EASY;


    //------------------ chequeo rrores de inicializacion de  Allegro ----------------------//

    bitmapBackround = al_load_bitmap(bitmapBackgroundFilepath);
    if (bitmapBackround == NULL) {
        fprintf(stdout, "Failed to load: %s\n", bitmapBackgroundFilepath);
        return BAD_ASSET;
    }

    bitmapSpace = al_load_bitmap(bitmapSpaceFilepath);
    if (bitmapSpace == NULL) {
        fprintf(stdout, "Failed to load: %s\n", bitmapSpaceFilepath);
        return BAD_ASSET;
    }

    font = al_load_font(fontFilepath, MENU_FONT_SIZE, NO_FLAGS);
    if (font == NULL) {
        fprintf(stdout, "Failed to load: %s\n", fontFilepath);
        return BAD_ASSET;
    }

    menuMusicSample = al_load_sample(menuMusicSampleFilenpath);
    if (menuMusicSample == NULL) {
        fprintf(stdout, "Failed to load: %s\n", menuMusicSampleFilenpath);
        return BAD_ASSET;
    }

    menuMusic = al_create_sample_instance(menuMusicSample);


    if (display == NULL) {
        fprintf(stdout, "Failed to create menu display of width %u and height %u\n ", DISPLAY_WIDTH, DISPLAY_HEIGHT);
        return BAD_DISPLAY;
    }

    queue = al_create_event_queue();
    if (queue == NULL) {
        fprintf(stdout, "Failed to create menu event queue\n");
        return BAD_ASSET;
    }

    timer = al_create_timer(TIMER_FPS(MENU_FPS));
    if (timer == NULL) {
        fprintf(stdout, "Failed to create menu timer of %u FPS\n", MENU_FPS);
        return BAD_ASSET;
    }

    //---------------------- Registro eventos, comienzo el timer, nombro ventana, empiezo musica ------------------------//

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_start_timer(timer);

    al_set_window_title(display, "SPACE INVADERS!");

    al_attach_sample_instance_to_mixer(menuMusic, al_get_default_mixer());
    al_set_sample_instance_playmode(menuMusic, ALLEGRO_PLAYMODE_LOOP);
    al_play_sample_instance(menuMusic);


    //-------------------------- Game loop del menu ---------------------------//

    bool menuLoop = true; // Este es el "game loop" solo del menu
    enum LEVEL_OPTIONS_E menuOption = NO_ERROR_CONTINUE_TO_LEVEL_ONE;
    char menuOptionCycle = 0;
    while (menuLoop) {

        al_wait_for_event(queue, &event);
        al_get_keyboard_state(&keyboardState);
        al_get_mouse_state(&mouseState);

        switch (event.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            menuLoop = false;
            menuOption =  QUIT_GAME;
            break;
        case ALLEGRO_EVENT_TIMER:
            al_draw_bitmap(bitmapSpace, -500, 0, NO_FLAGS);
            al_draw_bitmap(bitmapBackround,
                (DISPLAY_WIDTH / 2) - (al_get_bitmap_width(bitmapBackround) / 2),
                20,
                NO_FLAGS);
            if ((mouseState.x > 0.37f * DISPLAY_WIDTH) && (mouseState.x < (0.62f * DISPLAY_WIDTH)) && // cambia de color si el mouse esta sobre la opcion 
                (mouseState.y > 0.5f * DISPLAY_HEIGHT) && (mouseState.y < (0.6f * DISPLAY_HEIGHT))) {

                al_draw_text(font, GREEN, DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "Start");
            }
            else { // Blanco si no esta el mouse sobre el texto 

                al_draw_text(font, WHITE, DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "Start");
            }
            /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// 
            if ((mouseState.x > 0.37f * DISPLAY_WIDTH) && (mouseState.x < (0.62f * DISPLAY_WIDTH)) && // cambia de color si el mouse esta sobre la opcion 
                (mouseState.y > 0.6f * DISPLAY_HEIGHT) && (mouseState.y < (0.7f * DISPLAY_HEIGHT))) {

                al_draw_text(font, GREEN, DISPLAY_WIDTH / 2, 0.6 * DISPLAY_HEIGHT , ALLEGRO_ALIGN_CENTER, "Dificulty");
            }
            else { // Blanco si no esta el mouse sobre el texto 

                al_draw_text(font, WHITE, DISPLAY_WIDTH / 2, 0.6 * DISPLAY_HEIGHT, ALLEGRO_ALIGN_CENTER, "Dificulty");
            }
            /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// 
            if ((mouseState.x > 0.40f * DISPLAY_WIDTH) && (mouseState.x < (0.59f * DISPLAY_WIDTH)) &&
                (mouseState.y > 0.7f * DISPLAY_HEIGHT) && (mouseState.y < (0.8f * DISPLAY_HEIGHT))) {
                al_draw_text(font, GREEN, DISPLAY_WIDTH / 2, 0.7 * DISPLAY_HEIGHT, ALLEGRO_ALIGN_CENTER, "Scoreboard");

            }
            else {
                al_draw_text(font, WHITE, DISPLAY_WIDTH / 2, 0.7 * DISPLAY_HEIGHT, ALLEGRO_ALIGN_CENTER, "Scoreboard");

            }
            /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// 
            if ((mouseState.x > 0.40f * DISPLAY_WIDTH) && (mouseState.x < (0.59f * DISPLAY_WIDTH)) &&
                (mouseState.y > 0.8f * DISPLAY_HEIGHT) && (mouseState.y < (0.9f * DISPLAY_HEIGHT))) {

                    al_draw_text(font, RED, DISPLAY_WIDTH / 2, 0.8 * DISPLAY_HEIGHT, ALLEGRO_ALIGN_CENTER, "QUIT");

            }
            else {
                al_draw_text(font, WHITE, DISPLAY_WIDTH / 2, 0.8 * DISPLAY_HEIGHT, ALLEGRO_ALIGN_CENTER, "QUIT");

            }
            /// /// /// /// /// /// /// /// /// /// /// /// 
            /// /// /// /// /// /// /// /// /// /// /// /// 
            /// /// /// /// /// /// /// /// /// /// /// /// 
            switch (menuOptionCycle) {
            case 0: // caso "Start"
                al_draw_text(font, GREEN, DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "Start");
                break;
            case 1:
                al_draw_text(font, GREEN, DISPLAY_WIDTH / 2, 0.6 * DISPLAY_HEIGHT, ALLEGRO_ALIGN_CENTER, "Dificulty");
                break;
            case 2:
                al_draw_text(font, GREEN, DISPLAY_WIDTH / 2, 0.7 * DISPLAY_HEIGHT, ALLEGRO_ALIGN_CENTER, "Scoreboard");

                break;
            case 3:
                al_draw_text(font, RED, DISPLAY_WIDTH / 2, 0.8 * DISPLAY_HEIGHT, ALLEGRO_ALIGN_CENTER, "Quit");
                break;
            }

            al_flip_display();
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: // clickea una opcion del menu
            if ((mouseState.x > 0.37f * DISPLAY_WIDTH) && (mouseState.x < (0.62f * DISPLAY_WIDTH)) &&
                (mouseState.y > 0.5f * DISPLAY_HEIGHT) && (mouseState.y < (0.6f * DISPLAY_HEIGHT))) {
                menuOption = NO_ERROR_CONTINUE_TO_LEVEL_ONE;
                menuLoop = false;
            }
            else if ((mouseState.x > 0.40f * DISPLAY_WIDTH) && (mouseState.x < (0.59f * DISPLAY_WIDTH)) &&
                (mouseState.y > 0.6f * DISPLAY_HEIGHT) && (mouseState.y < (0.7f * DISPLAY_HEIGHT))) {
                menuOption = DIFFICULTY;
                menuLoop = false;
            }
            else if ((mouseState.x > 0.40f * DISPLAY_WIDTH) && (mouseState.x < (0.59f * DISPLAY_WIDTH)) &&
                (mouseState.y > 0.7f * DISPLAY_HEIGHT) && (mouseState.y < (0.8f * DISPLAY_HEIGHT))) {
                menuOption = SCOREBOARD;
                menuLoop = false;
            }
            else if ((mouseState.x > 0.40f * DISPLAY_WIDTH) && (mouseState.x < (0.59f * DISPLAY_WIDTH)) &&
                (mouseState.y > 0.8f * DISPLAY_HEIGHT) && (mouseState.y < (0.9f * DISPLAY_HEIGHT))) {
                menuOption = QUIT_GAME;
                menuLoop = false;
            }
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_Q:
            case ALLEGRO_KEY_ESCAPE: // sale del juego
                menuOption = QUIT_GAME;
                menuLoop = false;
                break;
            case ALLEGRO_KEY_DOWN:
            case ALLEGRO_KEY_S:
                menuOptionCycle++; // cambia que opcion esta "activa para seleccionar"
                if (menuOptionCycle > 3) {
                    menuOptionCycle = 0;
                }
                break;
            case ALLEGRO_KEY_UP:
            case ALLEGRO_KEY_W:
                menuOptionCycle--; // cambia que opcion esta "activa para seleccionar"
                if (menuOptionCycle < 0) {
                    menuOptionCycle = 3;
                }
                break;
            case ALLEGRO_KEY_ENTER: 
                switch (menuOptionCycle){
                case 0:
                    al_stop_sample_instance(menuMusic);
                    return NO_ERROR_CONTINUE_TO_LEVEL_ONE;
                    break;
                case 1:
                    menuLoop = false;
                    menuOption =  DIFFICULTY;
                    break;
                case 2:
                    return SCOREBOARD;
                    break;
                case 3:
                    al_stop_sample_instance(menuMusic);
                    return QUIT_GAME;
                    break;
                }
            }


        }

    }

    al_stop_sample_instance(menuMusic);

    al_destroy_bitmap(bitmapBackround);
    al_destroy_bitmap(bitmapSpace);
    al_destroy_font(font);
    al_destroy_sample(menuMusicSample);
    al_destroy_sample_instance(menuMusic);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);

    printf("Exiting [START MENU]\n");
    return menuOption;
}

//----------------------------------------------------------------------------------------------------------

enum LEVEL_OPTIONS_E pause_menu(ALLEGRO_DISPLAY* display) { //igual q menu de comienzo solo, que no genera un nuevo display, usa el viejo
    printf("Entering [PAUSE MENU]\n");

    al_set_target_backbuffer(display);

    al_reserve_samples(1); // Para la musica del menu

    ALLEGRO_BITMAP* bitmapBackround;
    ALLEGRO_BITMAP* bitmapSpace;
    ALLEGRO_FONT* font;

    ALLEGRO_SAMPLE* menuMusicSample;
    ALLEGRO_SAMPLE_INSTANCE* menuMusic;

    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_TIMER* timer;

    ALLEGRO_EVENT event;
    ALLEGRO_KEYBOARD_STATE keyboardState;
    ALLEGRO_MOUSE_STATE mouseState;

    const char* bitmapBackgroundFilepath = "assets/menu/space_invaders_logo.png";
    const char* bitmapSpaceFilepath = "assets/menu/space3.jpg";
    const char* fontFilepath = "assets/menu/space_invaders_font.ttf";
    const char* menuMusicSampleFilenpath = "assets/menu/sweet_mystery_galaxy.wav";

    //------------------ chequeo rrores de inicializacion de  Allegro ----------------------//

    bitmapBackround = al_load_bitmap(bitmapBackgroundFilepath);
    if (bitmapBackround == NULL) {
        fprintf(stdout, "Failed to load: %s\n", bitmapBackgroundFilepath);
        return BAD_ASSET;
    }

    bitmapSpace = al_load_bitmap(bitmapSpaceFilepath);
    if (bitmapSpace == NULL) {
        fprintf(stdout, "Failed to load: %s\n", bitmapSpaceFilepath);
        return BAD_ASSET;
    }

    font = al_load_font(fontFilepath, MENU_FONT_SIZE, NO_FLAGS);
    if (font == NULL) {
        fprintf(stdout, "Failed to load: %s\n", fontFilepath);
        return BAD_ASSET;
    }

    menuMusicSample = al_load_sample(menuMusicSampleFilenpath);
    if (menuMusicSample == NULL) {
        fprintf(stdout, "Failed to load: %s\n", menuMusicSampleFilenpath);
        return BAD_ASSET;
    }

    menuMusic = al_create_sample_instance(menuMusicSample);

    if (display == NULL) {
        fprintf(stdout, "Failed to recive menu display \n ");
        return BAD_DISPLAY;
    }

    queue = al_create_event_queue();
    if (queue == NULL) {
        fprintf(stdout, "Failed to create menu event queue\n");
        return BAD_ASSET;
    }

    timer = al_create_timer(TIMER_FPS(MENU_FPS));
    if (timer == NULL) {
        fprintf(stdout, "Failed to create menu timer of %u FPS\n", MENU_FPS);
        return BAD_ASSET;
    }

    //---------------------- Registro eventos, comienzo el timer, nombro ventanan, empiezo musica ------------------------//

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_start_timer(timer);

    al_set_window_title(display, "Pause menu");

    al_attach_sample_instance_to_mixer(menuMusic, al_get_default_mixer());
    al_set_sample_instance_playmode(menuMusic, ALLEGRO_PLAYMODE_LOOP);
    al_play_sample_instance(menuMusic);

    //-------------------------- Game loop del menu ---------------------------//

    bool menuLoop = true; // Este es el "game loop" solo del menu
    enum LEVEL_OPTIONS_E menuOption = NO_ERROR_CONTINUE_TO_LEVEL_ONE; // Esta variable se devuelve para informar q opcion sucedio
    char pauseMenuOptionCycle = 0;
    while (menuLoop) {

        al_wait_for_event(queue, &event);
        al_get_keyboard_state(&keyboardState);
        al_get_mouse_state(&mouseState);

        switch (event.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            menuLoop = false;
            menuOption = QUIT_GAME;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_P:
                menuOption = RESUME_GAME;
                menuLoop = false;
                break;
            case ALLEGRO_KEY_DOWN:
            case ALLEGRO_KEY_S:
                pauseMenuOptionCycle++; // cambia que opcion esta "activa para seleccionar"
                if (pauseMenuOptionCycle > 1) {
                    pauseMenuOptionCycle = 0;
                }
                break;
            case ALLEGRO_KEY_UP:
            case ALLEGRO_KEY_W:
                pauseMenuOptionCycle--; // cambia que opcion esta "activa para seleccionar"
                if (pauseMenuOptionCycle < 0) {
                    pauseMenuOptionCycle = 1;
                }
                break;
            case ALLEGRO_KEY_ENTER:
                switch (pauseMenuOptionCycle) {
                case 0:
                    menuOption = RESUME_GAME;
                    menuLoop = false;
                    break;
                case 1:
                    menuOption = QUIT_TO_MENU;
                    menuLoop = false;
                }
                
            }
            break;

        case ALLEGRO_EVENT_TIMER:
            al_clear_to_color(BLACK);
            al_draw_text(font, YELLOW, 0.5 * DISPLAY_WIDTH, 0.1 * DISPLAY_HEIGHT, ALLEGRO_ALIGN_CENTER, "PAUSE MENU");

            if ((mouseState.x > 0.37f * DISPLAY_WIDTH) && (mouseState.x < (0.62f * DISPLAY_WIDTH)) &&
                (mouseState.y > 0.5f * DISPLAY_HEIGHT) && (mouseState.y < (0.6f * DISPLAY_HEIGHT))) {
                al_draw_text(font, GREEN, DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "Resume");
            }
            else {
                al_draw_text(font, WHITE, DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "Resume");
            }
            if ((mouseState.x > 0.40f * DISPLAY_WIDTH) && (mouseState.x < (0.59f * DISPLAY_WIDTH)) &&
                (mouseState.y > 0.75f * DISPLAY_HEIGHT) && (mouseState.y < (0.85f * DISPLAY_HEIGHT))) {
                al_draw_text(font, RED, DISPLAY_WIDTH / 2, 0.75f * DISPLAY_HEIGHT, ALLEGRO_ALIGN_CENTER, "Quit to main menu");
            }
            else {
                al_draw_text(font, WHITE, 0.5 * DISPLAY_WIDTH, 0.75 * DISPLAY_HEIGHT, ALLEGRO_ALIGN_CENTER, "Quit to main menu");
            }

            switch (pauseMenuOptionCycle) {
            case 0:
                al_draw_text(font, GREEN, DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "Resume");
                break;
            case 1:
                al_draw_text(font, RED, DISPLAY_WIDTH / 2, 0.75f * DISPLAY_HEIGHT, ALLEGRO_ALIGN_CENTER, "Quit to main menu");
            }

            al_flip_display();
            break;


        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            if ((mouseState.x > 0.37f * DISPLAY_WIDTH) && (mouseState.x < (0.62f * DISPLAY_WIDTH)) &&
                (mouseState.y > 0.5f * DISPLAY_HEIGHT) && (mouseState.y < (0.6f * DISPLAY_HEIGHT))) {
                menuOption = RESUME_GAME;
                menuLoop = false;
            }
            else if ((mouseState.x > 0.40f * DISPLAY_WIDTH) && (mouseState.x < (0.59f * DISPLAY_WIDTH)) &&
                (mouseState.y > 0.75f * DISPLAY_HEIGHT) && (mouseState.y < (0.85f * DISPLAY_HEIGHT))) {
                menuOption = QUIT_TO_MENU;
                menuLoop = false;
            }
            break;
        default:
            break;
        }

    }

    al_stop_sample_instance(menuMusic);

    al_destroy_bitmap(bitmapBackround);
    al_destroy_bitmap(bitmapSpace);
    al_destroy_font(font);
    al_destroy_sample(menuMusicSample);
    al_destroy_sample_instance(menuMusic);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);

    printf("Exiting [PAUSE MENU]\n");
    return menuOption;
}

enum LEVEL_OPTIONS_E difficulty_menu(ALLEGRO_DISPLAY* display, int* difficulty) {
    printf("Entering [PAUSE MENU]\n");

    al_set_target_backbuffer(display);

    al_reserve_samples(1); // Para la musica del menu

    ALLEGRO_FONT* font;

    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_TIMER* timer;

    ALLEGRO_EVENT event;
    ALLEGRO_KEYBOARD_STATE keyboardState;
    ALLEGRO_MOUSE_STATE mouseState;

    const char* fontFilepath = "assets/menu/space_invaders_font.ttf";
    const char* menuMusicSampleFilenpath = "assets/menu/sweet_mystery_galaxy.wav";

    //------------------ chequeo rrores de inicializacion de  Allegro ----------------------//



    font = al_load_font(fontFilepath, MENU_FONT_SIZE, NO_FLAGS);
    if (font == NULL) {
        fprintf(stdout, "Failed to load: %s\n", fontFilepath);
        return BAD_ASSET;
    }


    if (display == NULL) {
        fprintf(stdout, "Failed to recive menu display \n ");
        return BAD_DISPLAY;
    }

    queue = al_create_event_queue();
    if (queue == NULL) {
        fprintf(stdout, "Failed to create menu event queue\n");
        return BAD_ASSET;
    }

    timer = al_create_timer(TIMER_FPS(MENU_FPS));
    if (timer == NULL) {
        fprintf(stdout, "Failed to create menu timer of %u FPS\n", MENU_FPS);
        return BAD_ASSET;
    }

    //---------------------- Registro eventos, comienzo el timer, nombro ventanan, empiezo musica ------------------------//

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_start_timer(timer);

    al_set_window_title(display, "Difficulty menu");


    //-------------------------- Game loop del menu ---------------------------//

    bool menuLoop = true; // Este es el "game loop" solo del menu
    enum LEVEL_OPTIONS_E menuOption = NO_ERROR_CONTINUE_TO_LEVEL_ONE; // Esta variable se devuelve para informar q opcion sucedio
    char difficultyMenuOptionCycle = 0;
    while (menuLoop) {

        al_wait_for_event(queue, &event);
        al_get_keyboard_state(&keyboardState);
        al_get_mouse_state(&mouseState);

        switch (event.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            menuLoop = false;
            menuOption = QUIT_GAME;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_P:
                menuOption = RESUME_GAME;
                menuLoop = false;
                break;
            case ALLEGRO_KEY_DOWN:
            case ALLEGRO_KEY_S:
                difficultyMenuOptionCycle++; // cambia que opcion esta "activa para seleccionar"
                if (difficultyMenuOptionCycle > 3) {
                    difficultyMenuOptionCycle = 0;
                }
                break;
            case ALLEGRO_KEY_UP:
            case ALLEGRO_KEY_W:
                difficultyMenuOptionCycle--; // cambia que opcion esta "activa para seleccionar"
                if (difficultyMenuOptionCycle < 0) {
                    difficultyMenuOptionCycle = 3;
                }
                break;
            case ALLEGRO_KEY_ENTER:
                switch (difficultyMenuOptionCycle) {
                case 0:
                    *difficulty = EASY;
                    menuLoop = false;
                    break;
                case 1:
                    *difficulty = MEDIUM;
                    menuLoop = false;
                    break;
                case 2:
                    *difficulty = HARD;
                    menuLoop = false;
                    break;
                case 3:
                    *difficulty = HELL;
                    menuLoop = false;
                    break;
                }

            }
            break;

        case ALLEGRO_EVENT_TIMER:
            al_clear_to_color(BLACK);
            al_draw_text(font, YELLOW, 0.5 * DISPLAY_WIDTH, 0.1 * DISPLAY_HEIGHT, ALLEGRO_ALIGN_CENTER, "Difficulty MENU");

            if ((mouseState.x > 0.37f * DISPLAY_WIDTH) && (mouseState.x < (0.62f * DISPLAY_WIDTH)) && // cambia de color si el mouse esta sobre la opcion 
                (mouseState.y > 0.5f * DISPLAY_HEIGHT) && (mouseState.y < (0.6f * DISPLAY_HEIGHT))) {

                al_draw_text(font, GREEN, DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "EASY");
            }
            else { // Blanco si no esta el mouse sobre el texto 

                al_draw_text(font, WHITE, DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "EASY");
            }
            /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// 
            if ((mouseState.x > 0.37f * DISPLAY_WIDTH) && (mouseState.x < (0.62f * DISPLAY_WIDTH)) && // cambia de color si el mouse esta sobre la opcion 
                (mouseState.y > 0.6f * DISPLAY_HEIGHT) && (mouseState.y < (0.7f * DISPLAY_HEIGHT))) {

                al_draw_text(font, GREEN, DISPLAY_WIDTH / 2, 0.6 * DISPLAY_HEIGHT, ALLEGRO_ALIGN_CENTER, "MEDIUM");
            }
            else { // Blanco si no esta el mouse sobre el texto 

                al_draw_text(font, WHITE, DISPLAY_WIDTH / 2, 0.6 * DISPLAY_HEIGHT, ALLEGRO_ALIGN_CENTER, "MEDIUM");
            }
            /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// 
            if ((mouseState.x > 0.40f * DISPLAY_WIDTH) && (mouseState.x < (0.59f * DISPLAY_WIDTH)) &&
                (mouseState.y > 0.7f * DISPLAY_HEIGHT) && (mouseState.y < (0.8f * DISPLAY_HEIGHT))) {
                al_draw_text(font, GREEN, DISPLAY_WIDTH / 2, 0.7 * DISPLAY_HEIGHT, ALLEGRO_ALIGN_CENTER, "HARD");

            }
            else {
                al_draw_text(font, WHITE, DISPLAY_WIDTH / 2, 0.7 * DISPLAY_HEIGHT, ALLEGRO_ALIGN_CENTER, "HARD");

            }
            /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// 
            if ((mouseState.x > 0.40f * DISPLAY_WIDTH) && (mouseState.x < (0.59f * DISPLAY_WIDTH)) &&
                (mouseState.y > 0.8f * DISPLAY_HEIGHT) && (mouseState.y < (0.9f * DISPLAY_HEIGHT))) {

                al_draw_text(font, RED, DISPLAY_WIDTH / 2, 0.8 * DISPLAY_HEIGHT, ALLEGRO_ALIGN_CENTER, "HELL");

            }
            else {
                al_draw_text(font, WHITE, DISPLAY_WIDTH / 2, 0.8 * DISPLAY_HEIGHT, ALLEGRO_ALIGN_CENTER, "HELL");

            }
            /// /// /// /// /// /// /// /// /// /// /// /// 
            /// /// /// /// /// /// /// /// /// /// /// /// 
            /// /// /// /// /// /// /// /// /// /// /// /// 
            switch (difficultyMenuOptionCycle) {
            case 0: // caso "Start"
                al_draw_text(font, GREEN, DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "EASY");
                break;
            case 1:
                al_draw_text(font, GREEN, DISPLAY_WIDTH / 2, 0.6 * DISPLAY_HEIGHT, ALLEGRO_ALIGN_CENTER, "MEDIUM");
                break;
            case 2:
                al_draw_text(font, GREEN, DISPLAY_WIDTH / 2, 0.7 * DISPLAY_HEIGHT, ALLEGRO_ALIGN_CENTER, "HARD");

                break;
            case 3:
                al_draw_text(font, RED, DISPLAY_WIDTH / 2, 0.8 * DISPLAY_HEIGHT, ALLEGRO_ALIGN_CENTER, "HELL");
                break;
            }

            al_flip_display();
            break;


        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            if ((mouseState.x > 0.37f * DISPLAY_WIDTH) && (mouseState.x < (0.62f * DISPLAY_WIDTH)) &&
                (mouseState.y > 0.5f * DISPLAY_HEIGHT) && (mouseState.y < (0.6f * DISPLAY_HEIGHT))) {
                menuOption = RESUME_GAME;
                menuLoop = false;
            }
            else if ((mouseState.x > 0.40f * DISPLAY_WIDTH) && (mouseState.x < (0.59f * DISPLAY_WIDTH)) &&
                (mouseState.y > 0.75f * DISPLAY_HEIGHT) && (mouseState.y < (0.85f * DISPLAY_HEIGHT))) {
                menuOption = QUIT_TO_MENU;
                menuLoop = false;
            }
            break;
        default:
            break;
        }

    }


    al_destroy_font(font);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);

    printf("Exiting [PAUSE MENU]\n");
    return menuOption;
}