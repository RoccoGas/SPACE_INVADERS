#ifndef __MOVEMENT__
#define __MOVEMENT__ 

#include "allegro.h"
#include "header.h"


void update_player(player_t* player, ALLEGRO_KEYBOARD_STATE keyboardState, laser_t* laser);
void update_enemy_y(enemy_t enemy[MAX_ENEMY_ROWS][MAX_ENEMY_COLS]);
void update_enemy_x(enemy_t enemy[MAX_ENEMY_ROWS][MAX_ENEMY_COLS], unsigned int enemyDirection, int difficulty);
void enemy_movement_1(enemy_t enemy[MAX_ENEMY_ROWS][MAX_ENEMY_COLS], unsigned int* enemyDirection, unsigned int* downFlag, enemy_t* mostLeftEnemy, enemy_t* mostRightEnemy, int difficulty);
void shoot_laser(player_t* player, laser_t* laser);

void update_laser(player_t* player, laser_t* laser, 
					enemy_t enemy[MAX_ENEMY_ROWS][MAX_ENEMY_COLS], enemy_t** mostRight, enemy_t** mostLeft, 
					enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT], shield_t shields[MAX_SHIELD_AMOUNT][MAX_SHIELD_HEIGHT][MAX_SHIELD_LENGTH],
					mothership_t* mothership);

void update_mothership(mothership_t* mothership);
enemy_t* update_most_left(enemy_t enemy[MAX_ENEMY_ROWS][MAX_ENEMY_COLS]);
enemy_t* update_most_right(enemy_t enemy[MAX_ENEMY_ROWS][MAX_ENEMY_COLS]);

int count_alive_enemies(enemy_t enemy[MAX_ENEMY_ROWS][MAX_ENEMY_COLS]);
int count_alive_lasers(enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT]);


enemy_t* decide_enemy_shot(enemy_t enemy[MAX_ENEMY_ROWS][MAX_ENEMY_COLS], int rows, int cols);
void start_enemy_shot(enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT], enemy_t* chosenEnemy);
void update_enemy_shot(enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT], player_t* player, shield_t shields[MAX_SHIELD_AMOUNT][MAX_SHIELD_HEIGHT][MAX_SHIELD_LENGTH]);
void destroy_all_enemy_lasers(laser_t lasers[MAX_ENEMY_LASER_AMOUNT]);



#endif //__MOVEMENT__