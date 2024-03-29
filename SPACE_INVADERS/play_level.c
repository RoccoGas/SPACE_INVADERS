
//ESTARIA BUENO PONER EL PLAYER MOVEMENT EN UNA FUNCION EN UNA LIBRERIA DE MOVEMENT
#include "menu.h"
#include "allegro.h"
#include "header.h"
#include "movement.h"
#include <stdio.h>
#include "initialize.h"
#include "drawing.h"

enum LEVEL_OPTIONS_E  play_level(ALLEGRO_DISPLAY* display, player_t* player, int difficulty, int level) {
    printf("[LEVEL %d]\n", level);


    int enemy_rows, enemy_cols;

    enemy_t enemy[MAX_ENEMY_ROWS][MAX_ENEMY_COLS]; //despues va a ser un vector esto
    enemy_t* mostRightEnemy;


    switch (level) {
    case 1:
        enemy_rows = LEVEL1_ROWS;
        enemy_cols = LEVEL1_COLS;
        mostRightEnemy = &enemy[0][LEVEL1_COLS - 1];
        break;
    case 2:
        enemy_rows = LEVEL2_ROWS;
        enemy_cols = LEVEL2_COLS;
        mostRightEnemy = &enemy[0][LEVEL2_COLS - 1];

        break;
    case 3:
        enemy_rows = LEVEL3_ROWS;
        enemy_cols = LEVEL3_COLS;
        mostRightEnemy = &enemy[0][LEVEL3_COLS - 1];
        break;
    default:
        printf("FUERA DEL RANGO DE NIVELES");
        return PARAMETER_ERROR;

    }

    al_reserve_samples(1); // Para la musica del menu

    ALLEGRO_FONT* font;
    ALLEGRO_SAMPLE* levelOneMusicSample;
    ALLEGRO_SAMPLE_INSTANCE* levelOneMusic;


    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_TIMER* timer;
    ALLEGRO_FONT* HUDfont;

    ALLEGRO_EVENT event;
    ALLEGRO_KEYBOARD_STATE keyboardState;

    //enemy_t enemy[MAX_ENEMY_ROWS][MAX_ENEMY_COLS]; //despues va a ser un vector esto
    laser_t laser;
    enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT];
    shield_t shields[MAX_SHIELD_AMOUNT][MAX_SHIELD_HEIGHT][MAX_SHIELD_LENGTH];
    mothership_t mothership;


    laser.moving = false;
    init_all_enemies1(enemy, enemy_rows, enemy_cols, ENEMY1_FILE_PATH, ENEMY2_FILE_PATH);
    init_enemy_lasers(enemyLasers);
    init_all_shields(shields);
    init_mothership(&mothership);
    unsigned int enemyDirection = DEFAULT_ENEMY_DIRECTION;
    unsigned int downFlag = 1; //para que no se vaya para abajo al principio
    enemy_t* mostLeftEnemy = &enemy[0][0];
    //enemy_t* mostRightEnemy = &enemy[0][LEVEL1_COLS - 1];


    const char* levelOneMusicSampleFilenpath = "assets/menu/Cirno_Fortress_Stage_1.wav";
    


    //------------------ chequeo rrores de inicializacion de  Allegro ----------------------//




    levelOneMusicSample = al_load_sample(levelOneMusicSampleFilenpath);
    if (levelOneMusicSample == NULL) {
        fprintf(stdout, "Failed to load: %s\n", levelOneMusicSampleFilenpath);
        return BAD_ASSET;
    }

    levelOneMusic = al_create_sample_instance(levelOneMusicSample);

    HUDfont = al_load_font(FONT_FILE_PATH, HUD_FONT_SIZE, NO_FLAGS);
    if (HUDfont == NULL) {
        fprintf(stdout, "Failed to load: %s\n", FONT_FILE_PATH);
        return BAD_ASSET;
    }

    queue = al_create_event_queue();
    if (queue == NULL) {
        fprintf(stdout, "Failed to create event queue\n");
        return BAD_ASSET;
    }

    timer = al_create_timer(TIMER_FPS(60));
    if (timer == NULL) {
        fprintf(stdout, "Failed to create level timer of %u FPS\n", MENU_FPS);
        return BAD_ASSET;
    }


    //---------------------- Registro eventos, comienzo el timer, nombro ventana, empiezo musica(?) ------------------------//

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());

    al_start_timer(timer);


     //al_attach_sample_instance_to_mixer(levelOneMusic, al_get_default_mixer());
     //al_set_sample_instance_playmode(levelOneMusic, ALLEGRO_PLAYMODE_LOOP);
     //al_play_sample_instance(levelOneMusic);


     //-------------------------- Game loop del nivel 1 ---------------------------//

    bool levelOneLoop = true; // Este es el "game loop" del nivel 1

    enum LEVEL_OPTIONS_E levelOneOption = NO_ERROR_CONTINUE_TO_LEVEL_ONE;
    int shooting = 0; //solucion momentanea al doble disparo
    unsigned int time = 0;

    al_stop_timer(timer);
    al_clear_to_color(BLACK2);
    al_draw_textf(HUDfont, WHITE, DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "LEVEL %d!", level);
    al_flip_display();
    al_rest(2.0);
    al_start_timer(timer);

    int levelDifficulty = 0;

    while (levelOneLoop) {

        al_get_keyboard_state(&keyboardState);
        al_wait_for_event(queue, &event);


        switch (event.type) {

        case ALLEGRO_EVENT_TIMER:
            if (count_alive_enemies(enemy) == 0) { // pasaste de nivel
                printf("TERMINO EL NIVEL UNO!!!\n");
                switch (level) {
                case 1:
                    levelOneOption = NO_ERROR_CONTINUE_TO_LEVEL_TWO;
                    break;
                case 2:
                    levelOneOption = NO_ERROR_CONTINUE_TO_LEVEL_THREE;
                    break;
                case 3:
                    levelOneOption = FINISHED_GAME;

                    break;
                default:
                    printf("FUERA DEL RANGO DE NIVELES");
                    return PARAMETER_ERROR;

                }
                levelOneLoop = false;
                break;
            }
            //UPDATE SPRITES 
            update_player(player, keyboardState, &laser);
            enemy_movement_1(enemy, &enemyDirection, &downFlag, mostLeftEnemy, mostRightEnemy, difficulty + levelDifficulty);
            update_laser(player, &laser, enemy, &mostRightEnemy, &mostLeftEnemy, enemyLasers, shields, &mothership);
            update_mothership(&mothership);
            time++; // cada cuanto diapara
            if ((time % (480 - 60* difficulty)) == 0) { // cada 6 segundos aumenta la dificultad "en easy" sube la dificultad cambia cada cuantos segundos aumenta
                if (levelDifficulty < MAX_DIFFICULTY) {
                    printf("AMENTO LA DIFICULTAD!\n");
                    levelDifficulty++;
                }
            }
            if (time % (50 - (10 * difficulty) - levelDifficulty) == 0) {
                start_enemy_shot(enemyLasers, decide_enemy_shot(enemy,enemy_rows, enemy_cols));
            }
            update_enemy_shot(enemyLasers, player, shields);
            if (player->lives == 0) {
                al_stop_timer(timer);
                draw_lose_screen();
                al_start_timer(timer);

                player->lives--;
                levelOneLoop = false; //GIT!!!
                return QUIT_TO_MENU;
            }
            mothership.timer++;
            if ((mothership.timer == MOTHERSHIP_FREQUENCY_TIMER) && (mothership.health == 0)) {
                reset_mothership(&mothership);
            }

            //DRAWING

            al_clear_to_color(BLACK);
            al_draw_bitmap(player->bitmap, player->x, PLAYERY, 0);
            draw_all_enemies(enemy, enemy_rows , enemy_cols);
            draw_laser(laser);
            draw_enemy_laser(enemyLasers);
            draw_shields(shields);
            draw_mothership(&mothership);
            draw_HUD(player, HUDfont);

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

            case ALLEGRO_KEY_RIGHT:
            case ALLEGRO_KEY_D:
                player->state = MOVING_RIGHT;
                break;

            case ALLEGRO_KEY_LEFT:
            case ALLEGRO_KEY_A:
                player->state = MOVING_LEFT;
                break;

            case ALLEGRO_KEY_SPACE:
                shoot_laser(player, &laser);
                break;
            case ALLEGRO_KEY_P:
                al_stop_sample_instance(levelOneMusic);
                al_stop_timer(timer);
                if(pause_menu(display) == QUIT_TO_MENU) {
                    levelOneOption = QUIT_TO_MENU;
                    levelOneLoop = false;
                    break;
                }
                al_flush_event_queue(queue);
                al_start_timer(timer);
                break;
            }
            break;



        case ALLEGRO_EVENT_KEY_UP: // SOLTO LA TECLA DE MOVERSE
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_RIGHT:
            case ALLEGRO_KEY_D: // LOGICA PARA QUE NO PARE CUANDO SOLTAS CUALQUIER TECLA
                if (player->state == MOVING_LEFT) {
                    break;
                }
                else if (player->state == MOVING_RIGHT) {
                    player->state = NOT_MOVING;
                }
                
            case ALLEGRO_KEY_LEFT:
            case ALLEGRO_KEY_A:
                if (player->state == MOVING_RIGHT) {
                    break;
                }
                else if (player->state == MOVING_LEFT) {
                    player->state = NOT_MOVING;
                }
            }
            break;

            
        }
    }
 
    

    //carga player pos en su status

    /*al_stop_sample_instance(levelOneMusic);


    al_destroy_display(display);
    al_destroy_sample(levelOneMusicSample);
    al_destroy_sample_instance(levelOneMusic);*/
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);

    printf("Exiting [LEVEL ONE]\n");
    return levelOneOption;
}

