
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