#ifndef __INITIALIZE__
#define __INITIALIZE__

#include "header.h"

bool init_player(playerStatus* player);
bool init_enemy(enemyStatus* enemy, const char* enemyTypeFile);

bool init_all_enemies1(enemyStatus* enemy[LEVEL1_ROWS][LEVEL1_COLS], const char* enemyTypeFile);


#endif