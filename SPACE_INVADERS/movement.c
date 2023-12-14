#include "movement.h"
#include <stdio.h>


void enemy_movement_1(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS], unsigned int * enemyDirection, unsigned int* downFlag, enemyStatus mostLeftEnemy, enemyStatus mostRightEnemy) { //se usa en ciclos, conviene tener bitmap como parametro
	int i, j;


	if ((mostRightEnemy.x + ENEMY_WIDTH) >= DISPLAY_WIDTH && *downFlag == 0) { //todos los sprites de los enemigos tienen el mismo tamaño (o al menos el ancho, arreglar que hacemos)
		update_enemy_y(enemy);
		*enemyDirection = ENEMY_DIRECTION_LEFT;
		*downFlag = 1;
	}	
	else if (mostLeftEnemy.x <= 0 && *downFlag == 0) {                            
		update_enemy_y(enemy);
		*enemyDirection = ENEMY_DIRECTION_RIGHT;
		*downFlag = 1;
	}
	else if (*enemyDirection == ENEMY_DIRECTION_RIGHT) {
		update_enemy_x(enemy, *enemyDirection);
		*downFlag = 0;
	}
	else if (*enemyDirection == ENEMY_DIRECTION_LEFT) {
		update_enemy_x(enemy, *enemyDirection);
		*downFlag = 0;
	}



}


void update_enemy_x(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS], unsigned int enemyDirection) {
	int i, j;

	for (i = 0; i < LEVEL1_ROWS; i++) {
		for (j = 0; j < LEVEL1_COLS; j++) {

			if (enemyDirection == ENEMY_DIRECTION_RIGHT) {
				enemy[i][j].x += 2;
			}

			else if (enemyDirection == ENEMY_DIRECTION_LEFT) {
				enemy[i][j].x -= 2;
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
}

void draw_all_enemies(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS]) {
	int i, j;

	for (i = 0; i < LEVEL1_ROWS; i++) {
		for (j = 0; j < LEVEL1_COLS; j++) {
			if (enemy[i][j].alive) {
				al_draw_bitmap(enemy[i][j].bitmap, enemy[i][j].x, enemy[i][j].y, 0);
			}
		}
	}
}

void shoot_laser(playerStatus* player, laser_t* laser) {
	if (laser->moving == true) {
		return;
	}
	laser->moving = true;
	laser->x = player->x + (SPACESHIP_SIZE / 2);
	laser->y = PLAYERY;
}

void update_laser(laser_t* laser, enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS], enemyStatus mostRight, enemyStatus mostLeft) {
	laser->y -= 20;
	if (laser->y < 0) { // llego al techo
		laser->moving = false;
		return;
	}
	
	unsigned int i, j;
	if (laser->moving) {
		for (i = 0; i < LEVEL1_ROWS; i++) {
			for (j = 0; j < LEVEL1_COLS; j++) {
				if ((laser->x > enemy[i][j].x) && (laser->x < enemy[i][j].x + ENEMY_WIDTH) && (laser->y > enemy[i][j].y) && (laser->y < enemy[i][j].y + ENEMY_HEIGHT) && (enemy[i][j].alive)) { //Choco
					laser->moving = false;
					enemy[i][j].alive = false;
					if (&enemy[i][j] == &mostLeft) {
						update_most_left(enemy, &mostLeft);


					}
					else if (&enemy[i][j] == &mostRight) {
						update_most_right(enemy, &mostRight);
					}
					return;
				}
				

			}
		}
	}
}
void draw_laser(laser_t laser) {
	if (laser.moving == false) {
		return;
	}
	al_draw_line(laser.x, laser.y, laser.x, laser.y + LASER_LENGTH, RED, 4);
}

void update_most_right(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS], enemyStatus* mostRight) {
	 int i, j; 

	for (i = LEVEL1_COLS - 1; i >= 0; i--) {
		for (j = 0; j < LEVEL1_ROWS; j++) {
			if (enemy[j][i].alive) {
				*mostRight = enemy[j][i];
				/*printf("UPDATED MOST RIGHT!\n");
				printf("mostRight from: %p to %p\n", mostRight, &enemy[j][i]);*/

				return;

			}
		}
	}
}
void update_most_left(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS], enemyStatus* mostLeft) {
	int i, j;
	for (i = 0; i < LEVEL1_COLS; i++) {
		for (j = 0; j < LEVEL1_ROWS; j++) {
			if (enemy[j][i].alive) {
				*mostLeft = enemy[j][i];
				/*printf("UPDATED MOST LEFT!\n");
				printf("mostLeft from: %p to %p\n", *aux, &enemy[j][i]);*/

				return;
			}
		}
	}
	
}