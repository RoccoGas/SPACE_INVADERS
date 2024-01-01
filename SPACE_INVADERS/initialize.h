#ifndef __INITIALIZE__
#define __INITIALIZE__

#include "header.h"
#include "movement.h"

bool init_player(playerStatus* player);
bool init_enemy(enemyStatus* enemy, const char* enemyTypeFile);

bool init_all_enemies1(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS], const char* enemyTypeFile);
bool init_enemy_lasers(enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT]);
bool init_all_shields(shield_t shields[MAX_SHIELD_AMOUNT][MAX_SHIELD_HEIGHT][MAX_SHIELD_LENGTH]);
bool init_mothership(mothership_t* mothership);
void reset_mothership(mothership_t* mothership);


#endif