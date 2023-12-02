#include "movement.h"
#include <stdio.h>

void enemyMovement(unsigned int enemyID, unsigned int firstEnemyID, unsigned int lastEnemyID, ALLEGRO_BITMAP* enemyBitmap, unsigned int* enemyX, unsigned int* enemyY, unsigned int* enemyDirection, unsigned int* downFlag) { //se usa en ciclos, conviene tener bitmap como parametro
	//downFlag es 1 si fue hacia abajo, 0 si no
	//los 3 primeros argumentos los tuve que poner para que se muevan muchos enemigos bien, y para q cuando los maten que en el nivel se cambie cual es el "borde" de la matriz de enemigos

	if ((*enemyX + ENEMY_WIDTH) >= DISPLAY_WIDTH && *downFlag == 0) { //todos los sprites de los enemigos tienen el mismo tamaño (o al menos el ancho, arreglar que hacemos)
		*enemyY += 20;
		//al_draw_bitmap(enemyBitmap, *enemyX, *enemyY, 0);
		*enemyDirection = ENEMY_DIRECTION_LEFT;
		*downFlag = 1;
	}

	else if (*enemyX <= 0 && *downFlag == 0) {
		*enemyY += 20;
		//al_draw_bitmap(enemyBitmap, *enemyX, *enemyY, 0);
		*enemyDirection = ENEMY_DIRECTION_RIGHT;
		*downFlag = 1;
	}

	else if (*enemyDirection == ENEMY_DIRECTION_RIGHT) {
		*enemyX += 5;
		if (enemyID == firstEnemyID) {
			*downFlag = 0;
		}
	}

	else if (*enemyDirection == ENEMY_DIRECTION_LEFT) {
		*enemyX -= 5;
		if (enemyID == lastEnemyID) {
			*downFlag = 0;
		}
	}

	al_draw_bitmap(enemyBitmap, *enemyX, *enemyY, 0);


}