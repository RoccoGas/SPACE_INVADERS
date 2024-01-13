#ifndef __MOVEMENT__
#define __MOVEMENT__ 

#include "allegro.h"
#include "header.h"


void update_player(playerStatus* player, ALLEGRO_KEYBOARD_STATE keyboardState, laser_t* laser);
void update_enemy_y(enemyStatus enemy[MAX_ENEMY_ROWS][MAX_ENEMY_COLS]);
void update_enemy_x(enemyStatus enemy[MAX_ENEMY_ROWS][MAX_ENEMY_COLS], unsigned int enemyDirection);
void enemy_movement_1(enemyStatus enemy[MAX_ENEMY_ROWS][MAX_ENEMY_COLS], unsigned int* enemyDirection, unsigned int* downFlag, enemyStatus* mostLeftEnemy, enemyStatus* mostRightEnemy);
void shoot_laser(playerStatus* player, laser_t* laser);

void update_laser(playerStatus* player, laser_t* laser, 
					enemyStatus enemy[MAX_ENEMY_ROWS][MAX_ENEMY_COLS], enemyStatus** mostRight, enemyStatus** mostLeft, 
					enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT], shield_t shields[MAX_SHIELD_AMOUNT][MAX_SHIELD_HEIGHT][MAX_SHIELD_LENGTH],
					mothership_t* mothership);

void update_mothership(mothership_t* mothership);
enemyStatus* update_most_left(enemyStatus enemy[MAX_ENEMY_ROWS][MAX_ENEMY_COLS]);
enemyStatus* update_most_right(enemyStatus enemy[MAX_ENEMY_ROWS][MAX_ENEMY_COLS]);

int count_alive_enemies(enemyStatus enemy[MAX_ENEMY_ROWS][MAX_ENEMY_COLS]);
int count_alive_lasers(enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT]);


enemyStatus* decide_enemy_shot(enemyStatus enemy[MAX_ENEMY_ROWS][MAX_ENEMY_COLS], int rows, int cols);
void start_enemy_shot(enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT], enemyStatus* chosenEnemy);
void update_enemy_shot(enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT], playerStatus* player, shield_t shields[MAX_SHIELD_AMOUNT][MAX_SHIELD_HEIGHT][MAX_SHIELD_LENGTH]);
void destroy_all_enemy_lasers(laser_t lasers[MAX_ENEMY_LASER_AMOUNT]);



#endif //__MOVEMENT__