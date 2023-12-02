#include "movement.h"

void enemyMovement(unsigned int enemyAmount, ALLEGRO_BITMAP* enemyBitmap, unsigned int* enemyX, unsigned int* enemyY, unsigned int* enemyDirection, unsigned int* downFlag) { //se usa en ciclos, conviene tener bitmap como parametro
	//downFlag es 1 si fue hacia abajo, 0 si no

	if ((*enemyX + ENEMY_WIDTH) >= DISPLAY_WIDTH && *downFlag == 0) { //todos los sprites de los enemigos tienen el mismo tamaño (o al menos el ancho, arreglar que hacemos)
		*enemyY += 20;
		al_draw_bitmap(enemyBitmap, *enemyX, *enemyY, 0);
		*enemyDirection = 0;
		*downFlag = 1;
	}

	else if (*enemyX <= 0 && *downFlag == 0) {
		*enemyY += 20;
		al_draw_bitmap(enemyBitmap, *enemyX, *enemyY, 0);
		*enemyDirection = 1;
		*downFlag = 1;
	}

	else if (*enemyDirection == 1) {
		*enemyX += 5;
		*downFlag = 0;
	}

	else if (*enemyDirection == 0) {
		*enemyX -= 5;
		*downFlag = 0;
	}

	al_draw_bitmap(enemyBitmap, *enemyX, *enemyY, 0);


}