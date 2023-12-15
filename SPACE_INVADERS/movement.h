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
void update_laser(laser_t* laser, enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS], enemyStatus** mostRight, enemyStatus** mostLeft);
void draw_laser(laser_t laser);
enemyStatus* update_most_left(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS]);
enemyStatus* update_most_right(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS]);

int count_alive_enemies(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS]);
int count_alive_lasers(enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT]);


void decide_enemy_shot(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS], enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT]);
void start_enemy_shot(enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT], float x, float y);
void update_enemy_shot(enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT], playerStatus* player);
void draw_enemy_laser(enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT]);





#endif //__MOVEMENT__