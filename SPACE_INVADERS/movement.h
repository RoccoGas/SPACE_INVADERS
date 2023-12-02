#ifndef __MOVEMENT__
#define __MOVEMENT__ 

#include "allegro.h"
#include "header.h"
void enemyMovement(unsigned int enemyID, unsigned int firstEnemyID, unsigned int lastEnemyID, ALLEGRO_BITMAP* enemyBitmap, unsigned int* enemyX, unsigned int* enemyY, unsigned int* enemyDirection, unsigned int* downFlag);

#endif //__MOVEMENT__