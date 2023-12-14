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
	int  aux = LEVEL1_COLS * LEVEL1_ROWS;
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
				if ((laser->x > enemy[i][j].x) && (laser->x < enemy[i][j].x + ENEMY_WIDTH) && (laser->y > enemy[i][j].y) && (laser->y < enemy[i][j].y + ENEMY_HEIGHT) && (enemy[i][j].alive)) { //Choco con enemigo
					laser->moving = false;
					enemy[i][j].alive = false;
					printf("MATE AL ENEMIGO: %p\n", &enemy[i][j]);
					if (&enemy[i][j] == &mostLeft) {
						printf("UPdate de mostleft!!!!\n");
						update_most_left(enemy, &mostLeft);
						enemy[i][j].alive = false;


					}
					else if (&enemy[i][j] == &mostRight) {
						printf("UPdate de mostright!!!!\n");

						update_most_right(enemy, &mostRight);
						enemy[i][j].alive = false;

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
				//enemy[j][i].alive = false;
				*mostRight = enemy[j][i];
				

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
				//enemy[j][i].alive = false;
				*mostLeft = enemy[j][i];
				

				return;
			}
		}
	}
	
}
int count_alive_enemies(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS]) {
	int i, j;
	int counter = 0;
	for (i = 0; i < LEVEL1_COLS; i++) {
		for (j = 0; j < LEVEL1_ROWS; j++) {
			if (enemy[j][i].alive) {
				counter++;
			}
		}
	}
	return counter;
}

//void enemy_shot(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS], enemyLaser_t enemyLasers[]) { 
//	int i, j, t;
//	srand(time(NULL));
//	
//	int shootingEnemyX = rand() % LEVEL1_COLS;
//	int shootingEnemyY = rand() % LEVEL1_ROWS;
//	
//	if (!enemy[shootingEnemyY][shootingEnemyX].alive) {
//		for (i = shootingEnemyY; i < LEVEL1_ROWS; i++) {
//			for (j = shootingEnemyX; j < LEVEL1_COLS; j++) {
//				if (enemy[i][j].alive) {
//					for (t = 0; t < MAX_ENEMY_LASER_AMOUNT; t++) {
//						if()
//
//					}
//					return;
//				}
//			}
//		}
//
//		for (i = shootingEnemyY; i >= 0; i--) {
//			for (j = shootingEnemyX; j >= 0; j--) {
//				if (enemy[i][j].alive) {
//
//					return;
//					
//				}
//			}
//
//		}
//	}
//}
//
//void update_enemy_shot(enemyLaser_t enemyLasers[]) {
//
//	if (enemyLaser->moving) {
//		
//	}
//	