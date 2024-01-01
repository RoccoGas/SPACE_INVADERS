#ifndef __DRAWING__
#define __DRAWING__

#include "allegro.h"
#include "header.h"

void draw_all_enemies(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS]);
void draw_laser(laser_t laser);
void draw_enemy_laser(enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT]);
void draw_shields(shield_t shields[MAX_SHIELD_AMOUNT][MAX_SHIELD_HEIGHT][MAX_SHIELD_LENGTH]);
void draw_HUD(playerStatus* player, ALLEGRO_FONT* font);
void draw_lose_screen(void);
void draw_mothership(mothership_t* mothership);



#endif // !__DRAWING__
