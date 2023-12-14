#ifndef __MOVEMENT__
#define __MOVEMENT__ 

#include "allegro.h"
#include "header.h"

typedef struct {
	float x;
	float y;
	bool moving;
}	laser_t;

typedef struct {
	float x;
	float y;
	bool moving;
}	enemyLaser_t;

void draw_all_enemies(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS]);
void update_enemy_y(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS]);
void update_enemy_x(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS], unsigned int enemyDirection);
void enemy_movement_1(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS], unsigned int* enemyDirection, unsigned int* downFlag, enemyStatus* mostLeftEnemy, enemyStatus* mostRightEnemy);
void shoot_laser(playerStatus* player, laser_t* laser);
void update_laser(laser_t* laser, enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS], enemyStatus* mostRight, enemyStatus* mostLeft);
void draw_laser(laser_t laser);
void update_most_left(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS], enemyStatus* mostLeft);
void update_most_right(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS], enemyStatus* mostRight);
int count_alive_enemies(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS]);





#endif //__MOVEMENT__