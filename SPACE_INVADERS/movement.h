#ifndef __MOVEMENT__
#define __MOVEMENT__ 

#include "allegro.h"
#include "header.h"

void draw_all_enemies(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS]);
void update_enemy_y(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS]);
void update_enemy_x(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS], unsigned int enemyDirection);
void enemy_movement_1(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS], unsigned int* enemyDirection, unsigned int* downFlag, enemyStatus* mostLeftEnemy, enemyStatus* mostRightEnemy);

#endif //__MOVEMENT__