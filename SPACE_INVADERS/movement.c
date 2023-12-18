#include "movement.h"
#include <stdio.h>


void enemy_movement_1(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS], unsigned int * enemyDirection, unsigned int* downFlag, enemyStatus* mostLeftEnemy, enemyStatus* mostRightEnemy) { //se usa en ciclos, conviene tener bitmap como parametro



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
	//printf("ENTRE A UPDATE_ENEMY_Y!\n");
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

void update_laser(laser_t* laser, enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS], enemyStatus** mostRight, enemyStatus** mostLeft) {
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
					//printf("MATE AL ENEMIGO: %p\n", &enemy[i][j]);
					if (&enemy[i][j] == *mostLeft) {
						printf("UPdate de mostleft de  %p a ", *mostLeft);
						*mostLeft = update_most_left(enemy);
						printf("%p\n ", *mostLeft);
						enemy[i][j].alive = false;


					}
					else if (&enemy[i][j] == *mostRight) {
						printf("UPdate de mostright!!!!\n");
						*mostRight = update_most_right(enemy);
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

enemyStatus* update_most_right(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS]) {
	 int i, j; 

	for (i = LEVEL1_COLS - 1; i >= 0; i--) {
		for (j = 0; j < LEVEL1_ROWS; j++) {
			if (enemy[j][i].alive) {
				return &enemy[j][i];
			}
		}
	}
	return NULL;
}
enemyStatus*  update_most_left(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS]) {
	int i, j;
	for (i = 0; i < LEVEL1_COLS; i++) {
		for (j = 0; j < LEVEL1_ROWS; j++) {
			if (enemy[j][i].alive) {
				//enemy[j][i].alive = false;
				

				return &enemy[j][i];
			}
		}
	}
	return NULL;
	
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

int count_alive_lasers(enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT]) {
	int i;
	int counter = 0;
	for (i = 0; i < MAX_ENEMY_LASER_AMOUNT; i++) {
		if (enemyLasers[i].moving) {
			counter++;
		}
	}
	return counter;
}

enemyStatus*  decide_enemy_shot(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS], enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT]) { //devuelve un puntero al enemigo que va a disparar el proximo disparo
	printf("ENTRE A DECISE ENEMY SHOT!\n");
	int i, j;
	srand(time(NULL));
	
	int shootingEnemyX = rand() % LEVEL1_COLS;
	int shootingEnemyY = rand() % LEVEL1_ROWS;
	
	if (!enemy[shootingEnemyY][shootingEnemyX].alive) {
		for (i = shootingEnemyY; i < LEVEL1_ROWS; i++) {
			for (j = shootingEnemyX; j < LEVEL1_COLS; j++) {
				if (enemy[i][j].alive) {
					if (count_alive_lasers(enemyLasers) < MAX_ENEMY_LASER_AMOUNT) {
						start_enemy_shot(enemyLasers, enemy[i][j].x, enemy[i][j].y);
					}
					return;
				}
			}
		}

		for (i = shootingEnemyY; i >= 0; i--) {
			for (j = shootingEnemyX; j >= 0; j--) {
				if (enemy[i][j].alive) {
					if (count_alive_lasers(enemyLasers) < MAX_ENEMY_LASER_AMOUNT) {
						start_enemy_shot(enemyLasers, enemy[i][j].x, enemy[i][j].y);
					}
					return;
					
				}
			}

		}
	}
}

void start_enemy_shot(enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT], float x, float y) {
	int i;
	for (i = 0; i < MAX_ENEMY_LASER_AMOUNT; i++) {
		if (enemyLasers[i].moving == false) {
			enemyLasers[i].moving = true;
			enemyLasers[i].x = x;
			enemyLasers[i].y = y;
		}
	}

}

void update_enemy_shot(enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT], playerStatus* player) {
	int i;
	for (i = 0; i < MAX_ENEMY_LASER_AMOUNT; i++) {
		if (enemyLasers[i].moving) { // actualizo posicion
			enemyLasers[i].y += 3;
		}
		if ((enemyLasers[i].x > player->x) && (enemyLasers[i].x < player->x + SPACESHIP_SIZE) && (enemyLasers[i].y > PLAYERY) && (enemyLasers[i].y < PLAYERY + SPACESHIP_SIZE) && ((enemyLasers[i].moving))) {// choca contra el jugador
			printf("PERDISTE!");
			enemyLasers[i].moving = false;
		}
		if (enemyLasers[i].y > DISPLAY_HEIGHT) {
			enemyLasers[i].moving = false;
		}
	}
}

void draw_enemy_laser(enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT]) {
	int i;
	for (i = 0; i < MAX_ENEMY_LASER_AMOUNT; i++) {
		if (enemyLasers[i].moving == false) {
			break;
		}
		al_draw_line(enemyLasers[i].x, enemyLasers[i].y, enemyLasers[i].x, enemyLasers[i].y + LASER_LENGTH, BLUE, 4);
	}
}