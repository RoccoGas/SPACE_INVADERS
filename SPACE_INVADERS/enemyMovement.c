#include "movement.h"
#include <stdio.h>

void enemyMovement(unsigned int enemyID, unsigned int firstEnemyID, unsigned int lastEnemyID, ALLEGRO_BITMAP* enemyBitmap, unsigned int* enemyX, unsigned int* enemyY, unsigned int* enemyDirection, unsigned int* downFlag) { //se usa en ciclos, conviene tener bitmap como parametro
	//downFlag es 1 si fue hacia abajo, 0 si no
	//los 3 primeros argumentos los tuve que poner para que se muevan muchos enemigos bien, y para q cuando los maten que en el nivel se cambie cual es el "borde" de la matriz de enemigos

	if ((*enemyX + ENEMY_WIDTH) >= DISPLAY_WIDTH && *downFlag == 0) { //todos los sprites de los enemigos tienen el mismo tamaño (o al menos el ancho, arreglar que hacemos)
		*enemyY += 20;
		*enemyDirection = ENEMY_DIRECTION_LEFT;
		*downFlag = 1;
	}

	else if (*enemyX <= 0 && *downFlag == 0) {
		*enemyY += 20;
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

void enemy_movement_1(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS], unsigned int * enemyDirection, unsigned int* downFlag, enemyStatus* mostLeftEnemy, enemyStatus* mostRightEnemy) { //se usa en ciclos, conviene tener bitmap como parametro
	int i, j;
	//downFlag es 1 si fue hacia abajo, 0 si no
	//los 3 primeros argumentos los tuve que poner para que se muevan muchos enemigos bien, y para q cuando los maten que en el nivel se cambie cual es el "borde" de la matriz de enemigos

	//for (i = 0; i < LEVEL1_ROWS; i++) {
		//for (j = 0; j < LEVEL1_COLS; j++) {


			if ((mostRightEnemy->x + ENEMY_WIDTH) >= DISPLAY_WIDTH && *downFlag == 0) { //todos los sprites de los enemigos tienen el mismo tamaño (o al menos el ancho, arreglar que hacemos)
				update_enemy_y(enemy);
				*enemyDirection = ENEMY_DIRECTION_LEFT;
				*downFlag = 1;
			}
			
			else if (mostLeftEnemy->x <= 0 && *downFlag == 0) {                            
				update_enemy_y(enemy);
				*enemyDirection = ENEMY_DIRECTION_RIGHT;
				*downFlag = 1;
			}

			else if (*enemyDirection == ENEMY_DIRECTION_RIGHT) {
				update_enemy_x(enemy, *enemyDirection);

				//if (&enemy[i][j] == mostRightEnemy) {
				*downFlag = 0;
				//}
			
			}

			else if (*enemyDirection == ENEMY_DIRECTION_LEFT) {
				update_enemy_x(enemy, *enemyDirection);


				//if (&enemy[i][j] == mostRightEnemy) {
					*downFlag = 0;
				//}

			}


	//	}
	//}

}


void update_enemy_x(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS], unsigned int enemyDirection) {
	int i, j;

	for (i = 0; i < LEVEL1_ROWS; i++) {
		for (j = 0; j < LEVEL1_COLS; j++) {

			if (enemyDirection == ENEMY_DIRECTION_RIGHT) {
				enemy[i][j].x += 5;
			}

			else if (enemyDirection == ENEMY_DIRECTION_LEFT) {
				enemy[i][j].x -= 5;
			}

		}
	}
	}


void update_enemy_y(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS]) {
	int i, j;

	for (i = 0; i < LEVEL1_ROWS; i++) {
		for (j = 0; j < LEVEL1_COLS; j++) {
			enemy[i][j].y += 20;
		}
	}
	printf("update enemyY\n");
}

void draw_all_enemies(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS]) {
	int i, j;

	for (i = 0; i < LEVEL1_ROWS; i++) {
		for (j = 0; j < LEVEL1_COLS; j++) {
			al_draw_bitmap(enemy[i][j].bitmap, enemy[i][j].x, enemy[i][j].y, 0);
		}
	}
}
