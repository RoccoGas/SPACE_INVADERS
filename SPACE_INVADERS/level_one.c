
//ESTARIA BUENO PONER EL PLAYER MOVEMENT EN UNA FUNCION EN UNA LIBRERIA DE MOVEMENT
#include "menu.h"
#include "allegro.h"
#include "header.h"
#include "movement.h"
#include <stdio.h>
#include "initialize.h"
#include <Windows.h>

#define LEVEL_ONE_ENEMY_AMOUNT 30

enemyStatus enemies[LEVEL_ONE_ENEMY_AMOUNT];

void draw_heads_up_display(player);

enum ERROR_OPTIONS_E level_one(ALLEGRO_DISPLAY* display, playerStatus* player) { 

    printf("[LEVEL ONE]\n");

    al_reserve_samples(1); // Para la musica del menu

    //ALLEGRO_FONT* font;
    //ALLEGRO_SAMPLE* levelOneMusicSample;
    //ALLEGRO_SAMPLE_INSTANCE* levelOneMusic;


    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_TIMER* timer;

    ALLEGRO_EVENT event;
    ALLEGRO_KEYBOARD_STATE keyboardState;

    enemyStatus enemy; //despues va a ser un vector esto
    if (!init_enemy(&enemy, "sprites/enemy1f.png")) {
        printf("Failed to initialize enemy\n");
    }



    unsigned int x = player->x;  //si en el gameloop se entra en cada ciclo al struct player y/o enemy, y se usa la macro BLACK2 se ralentiza todo CONSIDERABLEMENTE, hace mucho de mas
    ALLEGRO_COLOR black2 = BLACK2;
    ALLEGRO_BITMAP* bitmap = player->bitmap;
    ALLEGRO_BITMAP* enemyBitmap = enemy.bitmap;
    unsigned int enemyX = enemy.x;
    unsigned int enemyY = enemy.y;

    unsigned int enemyDirection = DEFAULT_ENEMY_DIRECTION;
    unsigned int downFlag = 1; //activada en un principio para que no se vaya para abajo al comienzo del nivel
    

    //const char* levelOneMusicSampleFilenpath = "assets/menu/Cirno_Fortress_Stage_1.wav";

    //------------------ chequeo rrores de inicializacion de  Allegro ----------------------//

   

    /*
    levelOneMusicSample = al_load_sample(levelOneMusicSampleFilenpath);
    if (levelOneMusicSample == NULL) {
        fprintf(stdout, "Failed to load: %s\n", levelOneMusicSampleFilenpath);
        return BAD_ASSET;
    }

    levelOneMusic = al_create_sample_instance(levelOneMusicSample);
    */

    queue = al_create_event_queue();
    if (queue == NULL) {
        fprintf(stdout, "Failed to create event queue\n");
        return BAD_QUEUE;
    }

    timer = al_create_timer(TIMER_FPS(60));
    if (timer == NULL) {
        fprintf(stdout, "Failed to create level timer of %u FPS\n", MENU_FPS);
        return BAD_TIMER;
    }


    //---------------------- Registro eventos, comienzo el timer, nombro ventana, empiezo musica(?) ------------------------//

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_start_timer(timer);


   /* al_attach_sample_instance_to_mixer(levelOneMusic, al_get_default_mixer());
    al_set_sample_instance_playmode(levelOneMusic, ALLEGRO_PLAYMODE_LOOP);
    al_play_sample_instance(levelOneMusic);*/


    //-------------------------- Game loop del menu ---------------------------//

    bool levelOneLoop = true; // Este es el "game loop" del nivel 1

    enum ERROR_OPTIONS_E levelOneOption = NO_ERROR_START_GAME;
    while (levelOneLoop) {

        al_get_keyboard_state(&keyboardState);

        if (al_key_down(&keyboardState, ALLEGRO_KEY_RIGHT)) {
            if ((x + SPACESHIP_SIZE) < DISPLAY_WIDTH) {
                x += 5;
            }
        }
        else if (al_key_down(&keyboardState, ALLEGRO_KEY_LEFT)) {
            if (x > 0) {
                x -= 5;
            }
        }

        al_wait_for_event(queue, &event);
       

        if (event.type == ALLEGRO_EVENT_TIMER) {
            al_clear_to_color(black2);
            enemyMovement(1, enemyBitmap, &enemyX, &enemyY, &enemyDirection, &downFlag);
            al_draw_bitmap(bitmap, x, PLAYERY, 0);
            al_flip_display();
        }


        /*switch (event.type) {
            
            case ALLEGRO_EVENT_TIMER:
                al_clear_to_color(BLACK2);
                al_draw_bitmap(player->bitmap, player->x, PLAYERY, 0);                  //ESTE SWITCH HACE MIERDA TODO HAY QUE VER QUE HACER
                al_flip_display();
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                levelOneLoop = false;
                levelOneOption = QUIT_GAME;
                break;
        
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_Q:
                    case ALLEGRO_KEY_ESCAPE:
                        levelOneOption = QUIT_GAME;
                        levelOneLoop = false;
                        break;

                        default:
                            break;
            }

            default:
                break;
           
        }*/

        
    }

    
    player->x = x; //carga player pos en su status

    //al_stop_sample_instance(levelOneMusic);


    al_destroy_display(display);
    //al_destroy_sample(levelOneMusicSample);
    //al_destroy_sample_instance(levelOneMusic);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);

    printf("Exiting [LEVEL ONE]\n");
    return levelOneOption;
}

