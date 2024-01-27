#ifndef __DRAWING__
#define __DRAWING__

#include "allegro.h"
#include "header.h"

void draw_all_enemies(enemy_t enemy[MAX_ENEMY_ROWS][MAX_ENEMY_COLS], int rows, int cols);
void draw_laser(laser_t laser);
void draw_enemy_laser(enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT]);
void draw_shields(shield_t shields[MAX_SHIELD_AMOUNT][MAX_SHIELD_HEIGHT][MAX_SHIELD_LENGTH]);
void draw_HUD(player_t* player, ALLEGRO_FONT* font);
void draw_lose_screen(void);
void draw_win_screen(void);

void draw_mothership(mothership_t* mothership);



#endif // !__DRAWING__
