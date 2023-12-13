
#include <stdio.h>

#include "allegro.h"
#include "menu.h"
#include "header.h"

bool init_player(playerStatus* player) {
    player->x = 20;
    player->lives = 3;
    player->score = 0;
    player->bitmap = al_load_bitmap("sprites/Spaceshipf.png");
    if (player->bitmap == NULL) {
        fprintf(stdout, "Failed to load player bitmap\n");
        return false;
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
