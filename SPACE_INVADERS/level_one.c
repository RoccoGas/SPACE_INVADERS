
#include "menu.h"
#include "allegro.h"
#include "header.h"

#include <stdio.h>

#define LEVEL_ONE_ENEMY_AMOUNT 30

enemyStatus enemies[LEVEL_ONE_ENEMY_AMOUNT];

enum ERROR_OPTIONS_E level_one(ALLEGRO_DISPLAY* display, playerStatus* player) {
    printf("[LEVEL ONE]\n");

    al_reserve_samples(1); // Para la musica del menu

    ALLEGRO_BITMAP* bitmapSpace;
    ALLEGRO_FONT* font;
    ALLEGRO_SAMPLE* levelOneMusicSample;
    ALLEGRO_SAMPLE_INSTANCE* levelOneMusic;


    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_TIMER* timer;

    ALLEGRO_EVENT event;
    ALLEGRO_KEYBOARD_STATE keyboardState;
    ALLEGRO_MOUSE_STATE mouseState;

    const char* bitmapBackgroundFilepath = "assets/menu/space_invader_logo.png";
    const char* bitmapSpaceFilepath = "assets/menu/space3.jpg";
    const char* fontFilepath = "assets/menu/space_invaders_font.ttf";
    const char* levelOneMusicSampleFilenpath = "assets/menu/Cirno_Fortress_Stage_1.wav";

    //------------------ chequeo rrores de inicializacion de  Allegro ----------------------//

   

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

    levelOneMusicSample = al_load_sample(levelOneMusicSampleFilenpath);
    if (levelOneMusicSample == NULL) {
        fprintf(stdout, "Failed to load: %s\n", levelOneMusicSampleFilenpath);
        return BAD_ASSET;
    }

    levelOneMusic = al_create_sample_instance(levelOneMusicSample);

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

    al_attach_sample_instance_to_mixer(levelOneMusic, al_get_default_mixer());
    al_set_sample_instance_playmode(levelOneMusic, ALLEGRO_PLAYMODE_LOOP);
    al_play_sample_instance(levelOneMusic);


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

    al_stop_sample_instance(levelOneMusic);

    al_destroy_bitmap(bitmapBackround);
    al_destroy_bitmap(bitmapSpace);
    al_destroy_display(display);
    al_destroy_font(font);
    al_destroy_sample(levelOneMusicSample);
    al_destroy_sample_instance(levelOneMusic);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);

    printf("Exiting [LEVEL ONE]\n");
    return menuOption;
}

