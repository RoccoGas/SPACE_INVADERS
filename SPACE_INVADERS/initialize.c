
#include <stdio.h>

#include "allegro.h"
#include "menu.h"
#include "header.h"
#include "movement.h"

bool init_player(playerStatus* player) {
    player->x = 20;
    player->lives = 3;
    player->score = 0;
    player->state = NOT_MOVING;
    player->bitmap = al_load_bitmap("sprites/Spaceshipf.png");
    if (player->bitmap == NULL) {
        fprintf(stdout, "Failed to load player bitmap\n");
        return false;
    }
    return true;

}

bool init_enemy_lasers(enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT]) {
    unsigned int i;
    for (i = 0; i < MAX_ENEMY_LASER_AMOUNT; i++) {
        enemyLasers[i].moving = false;
        enemyLasers[i].x = 0;
        enemyLasers[i].y = 0;
    }
    return true;

}



bool init_enemy(enemyStatus* enemy, const char* enemyTypeFile){
    enemy->x = 0;
    enemy->y = 0;
    enemy->alive = 1;
    enemy->bitmap = al_load_bitmap(enemyTypeFile);
    if (enemy->bitmap == NULL){
        fprintf(stdout, "Failed to load enemy bitmap\n");
        return false;
    }
    return true;
}

bool init_all_enemies1(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS], const char* enemyTypeFile) {
    int i, j;
    for (i = 0; i < LEVEL1_ROWS; i++) {
        for (j = 0; j < LEVEL1_COLS; j++) {
            if (!init_enemy(&enemy[i][j], enemyTypeFile)) {
                printf("Failed to initialize enemy %d\n", i);
                return false;
            }

            enemy[i][j].x += INITIAL_X_OFFSET * j;
            enemy[i][j].y += INITIAL_Y_OFFSET * i;
        }
    }
    return true;
}

bool init_all_shields(shield_t shields[MAX_SHIELD_AMOUNT][MAX_SHIELD_HEIGHT][MAX_SHIELD_LENGTH]) { // hay tres escudos de 4 cada uno por eso MAX_SHIELD_AMOUNT es 12
    int i, k, j;
    for (k = 0; k < MAX_SHIELD_AMOUNT; k++) {
        for (i = 0; i < MAX_SHIELD_HEIGHT; i++) {
            for (j = 0; j <= MAX_SHIELD_LENGTH; j++) { //Cada for genera un escudo "grande"
                shields[k][i][j].x = (((k + 1) *SHIELD_OFFSET) +( k * MAX_SHIELD_ALLEGRO_LENGTH)) + j * INDIVIDUAL_SHIELD_THICKNESS;
                shields[k][i][j].y = (SHIELD_Y + (i *INDIVIDUAL_SHIELD_THICKNESS));
                shields[k][i][j].health = INITIAL_SHIELD_HEALTH_PART;
            }
        }
    }
}