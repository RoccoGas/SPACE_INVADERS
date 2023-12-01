
#include "menu.h"
#include "allegro.h"
#include "header.h"

#include <stdio.h>

enum ERROR_OPTIONS_E start_menu(ALLEGRO_DISPLAY* display) {
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

    display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    if (display == NULL) {
        fprintf(stdout, "Failed to create menu display of width %u and height %u\n ", DISPLAY_WIDTH, DISPLAY_HEIGHT);
        return BAD_DISPLAY;
    }

    queue = al_create_event_queue();
    if (queue == NULL) {
        fprintf(stdout, "Failed to create menu event queue\n");
        return BAD_QUEUE;
    }

    timer = al_create_timer(TIMER_FPS(MENU_FPS));
    if (timer == NULL) {
        fprintf(stdout, "Failed to create menu timer of %u FPS\n", MENU_FPS);
        return BAD_TIMER;
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
    enum ERROR_OPTIONS_E menuOption = NO_ERROR_START_GAME;
    while (menuLoop) {

        al_get_next_event(queue, &event);
        al_get_keyboard_state(&keyboardState);
        al_get_mouse_state(&mouseState);

        switch (event.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            menuLoop = false;
            menuOption = QUIT_GAME;
            break;
        case ALLEGRO_EVENT_TIMER:
            al_draw_bitmap(bitmapSpace, -500, 0, NO_FLAGS);
            al_draw_bitmap(bitmapBackround,
                (DISPLAY_WIDTH / 2) - (al_get_bitmap_width(bitmapBackround) / 2),
                20,
                NO_FLAGS);
            /*al_draw_text(font,  
                GREY,
                DISPLAY_WIDTH / 2,
                DISPLAY_HEIGHT / 3,
                ALLEGRO_ALIGN_CENTER,
                "SPACE INVADERS!");*/
            if ((mouseState.x > 0.37f * DISPLAY_WIDTH) && (mouseState.x < (0.62f * DISPLAY_WIDTH)) &&
                (mouseState.y > 0.5f * DISPLAY_HEIGHT) && (mouseState.y < (0.6f * DISPLAY_HEIGHT))) {
                al_draw_text(font,
                    GREEN,
                    DISPLAY_WIDTH / 2,
                    DISPLAY_HEIGHT / 2,
                    ALLEGRO_ALIGN_CENTER,
                    "Start");
            }
            else {

                al_draw_text(font,
                    WHITE,
                    DISPLAY_WIDTH / 2,
                    DISPLAY_HEIGHT / 2,
                    ALLEGRO_ALIGN_CENTER,
                    "Start");
            }
            if ((mouseState.x > 0.40f * DISPLAY_WIDTH) && (mouseState.x < (0.59f * DISPLAY_WIDTH)) &&
                (mouseState.y > 0.75f * DISPLAY_HEIGHT) && (mouseState.y < (0.85f * DISPLAY_HEIGHT))) {
                al_draw_text(font,
                    RED,
                    DISPLAY_WIDTH / 2,
                    0.75f * DISPLAY_HEIGHT,
                    ALLEGRO_ALIGN_CENTER,
                    "Quit");
            }
            else {
                al_draw_text(font,
                    WHITE,
                    0.5 * DISPLAY_WIDTH,
                    0.75 * DISPLAY_HEIGHT,
                    ALLEGRO_ALIGN_CENTER,
                    "Quit");
            }
            al_flip_display();
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            if ((mouseState.x > 0.37f * DISPLAY_WIDTH) && (mouseState.x < (0.62f * DISPLAY_WIDTH)) &&
                (mouseState.y > 0.5f * DISPLAY_HEIGHT) && (mouseState.y < (0.6f * DISPLAY_HEIGHT))) {
                menuOption = NO_ERROR_START_GAME;
                menuLoop = false;
            }
            else if ((mouseState.x > 0.40f * DISPLAY_WIDTH) && (mouseState.x < (0.59f * DISPLAY_WIDTH)) &&
                (mouseState.y > 0.75f * DISPLAY_HEIGHT) && (mouseState.y < (0.85f * DISPLAY_HEIGHT))) {
                menuOption = QUIT_GAME;
                menuLoop = false;
            }
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_Q:
            case ALLEGRO_KEY_ESCAPE:
                menuOption = QUIT_GAME;
                menuLoop = false;
                break;
            case ALLEGRO_KEY_S:
                menuOption = NO_ERROR_START_GAME;
                menuLoop = false;
                break;
            }
        default:
            break;
        }

    }

    al_stop_sample_instance(menuMusic);

    al_destroy_bitmap(bitmapBackround);
    al_destroy_bitmap(bitmapSpace);
    al_destroy_display(display);
    al_destroy_font(font);
    al_destroy_sample(menuMusicSample);
    al_destroy_sample_instance(menuMusic);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);

    printf("Exiting [START MENU]\n");
    return menuOption;
}

//----------------------------------------------------------------------------------------------------------

enum ERROR_OPTIONS_E pause_menu(ALLEGRO_DISPLAY* display) { //igual q menu de comienzo solo, que no genera un nuevo display, usa el viejo
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
    const char* bitmapSpaceFilepath = "assets/menu/8bit_ocean.jfif";
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

    //display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT); no lo uso xq utilizo el q ya esta
    if (display == NULL) {
        fprintf(stdout, "Failed to recive menu display \n ");
        return BAD_DISPLAY;
    }

    queue = al_create_event_queue();
    if (queue == NULL) {
        fprintf(stdout, "Failed to create menu event queue\n");
        return BAD_QUEUE;
    }

    timer = al_create_timer(TIMER_FPS(MENU_FPS));
    if (timer == NULL) {
        fprintf(stdout, "Failed to create menu timer of %u FPS\n", MENU_FPS);
        return BAD_TIMER;
    }

    //---------------------- Registro eventos, comienzo el timer, nombro ventanan, empiezo musica ------------------------//

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_start_timer(timer);

    al_set_window_title(display, "Rocco's Mario =)");

    al_attach_sample_instance_to_mixer(menuMusic, al_get_default_mixer());
    al_set_sample_instance_playmode(menuMusic, ALLEGRO_PLAYMODE_LOOP);
    al_play_sample_instance(menuMusic);

    //-------------------------- Game loop del menu ---------------------------//

    bool menuLoop = true; // Este es el "game loop" solo del menu
    enum ERROR_OPTIONS_E menuOption = NO_ERROR_START_GAME; // Esta variable se devuelve para informar q opcion sucedio
    while (menuLoop) {

        al_get_next_event(queue, &event);
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
                menuLoop = false;
                menuOption = RESUME_GAME;
                break;
            }
            break;
        case ALLEGRO_EVENT_TIMER:
            //al_clear_to_color(BLUE);
            //al_draw_bitmap(bitmapSpace, 0, 0, NO_FLAGS); 
            al_draw_bitmap(bitmapBackround,
                (DISPLAY_WIDTH / 2) - (al_get_bitmap_width(bitmapBackround) / 2),
                0.2 * DISPLAY_HEIGHT,
                NO_FLAGS);
            al_draw_text(font,
                YELLOW,
                0.5 * DISPLAY_WIDTH,
                0.1 * DISPLAY_HEIGHT,
                ALLEGRO_ALIGN_CENTER,
                "PAUSE MENU");
            //// al_draw_text(font,
            //     GREY,
            //     DISPLAY_WIDTH / 2,
            //     DISPLAY_HEIGHT / 3,
            //     ALLEGRO_ALIGN_CENTER,
            //     "Mario for Proga 1!");
            al_draw_text(font,
                WHITE,
                DISPLAY_WIDTH / 2,
                DISPLAY_HEIGHT / 2,
                ALLEGRO_ALIGN_CENTER,
                "Resume");
            if ((mouseState.x > 0.37f * DISPLAY_WIDTH) && (mouseState.x < (0.62f * DISPLAY_WIDTH)) &&
                (mouseState.y > 0.5f * DISPLAY_HEIGHT) && (mouseState.y < (0.6f * DISPLAY_HEIGHT))) {
                al_draw_text(font,
                    GREEN,
                    DISPLAY_WIDTH / 2,
                    DISPLAY_HEIGHT / 2,
                    ALLEGRO_ALIGN_CENTER,
                    "Resume");
            }
            al_draw_text(font,
                WHITE,
                0.5 * DISPLAY_WIDTH,
                0.75 * DISPLAY_HEIGHT,
                ALLEGRO_ALIGN_CENTER,
                "Quit to main menu");
            if ((mouseState.x > 0.40f * DISPLAY_WIDTH) && (mouseState.x < (0.59f * DISPLAY_WIDTH)) &&
                (mouseState.y > 0.75f * DISPLAY_HEIGHT) && (mouseState.y < (0.85f * DISPLAY_HEIGHT))) {
                al_draw_text(font,
                    RED,
                    DISPLAY_WIDTH / 2,
                    0.75f * DISPLAY_HEIGHT,
                    ALLEGRO_ALIGN_CENTER,
                    "Quit to main menu");
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
    //al_destroy_display(display); noo lo destruyo xq no es mio
    al_destroy_font(font);
    al_destroy_sample(menuMusicSample);
    al_destroy_sample_instance(menuMusic);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);

    printf("Exiting [PAUSE MENU]\n");
    return menuOption;
}