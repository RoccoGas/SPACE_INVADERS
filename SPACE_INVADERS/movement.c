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

void update_player(playerStatus* player, ALLEGRO_KEYBOARD_STATE keyboardState, laser_t* laser) {
	if (player->state == MOVING_RIGHT) {
		player->x += 3;
	}
	else if (player->state == MOVING_LEFT) {
		player->x -= 3;
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

void update_laser(laser_t* laser, enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS], enemyStatus** mostRight, enemyStatus** mostLeft, enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT], shield_t shields[MAX_SHIELD_AMOUNT][MAX_SHIELD_HEIGHT][MAX_SHIELD_LENGTH]) {
	unsigned int i, j, k;

	laser->y -= 20;
	if (laser->y < 0) { // llego al techo
		laser->moving = false;
		return;
	}
	
	if (laser->moving) {
		for (i = 0; i < MAX_ENEMY_LASER_AMOUNT; i++) { // Veo si choca con un laser enemigo
			if (enemyLasers[i].moving) {
				if ((enemyLasers[i].x -(LASER_WIDTH/2 + 3) <= laser->x) && (enemyLasers[i].x + (LASER_WIDTH / 2 + 3) >= laser->x) && ( laser->y >  enemyLasers[i].y) && ( laser->y < enemyLasers[i].y + LASER_LENGTH)) {
					enemyLasers[i].moving = false;
					laser->moving = false;
					printf("CHOCARON LOS LASERS!\n");
					return;
				}
			}
		}
		for (i = 0; i < LEVEL1_ROWS; i++) {
			for (j = 0; j < LEVEL1_COLS; j++) {
				if ((laser->x > enemy[i][j].x) && (laser->x < enemy[i][j].x + ENEMY_WIDTH) && (laser->y > enemy[i][j].y) && (laser->y < enemy[i][j].y + ENEMY_HEIGHT) && (enemy[i][j].alive)) { //Choco con enemigo
					laser->moving = false;
					enemy[i][j].alive = false;
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

		for (k = 0; k < MAX_SHIELD_AMOUNT; k++) {
			for (i = 0; i < MAX_SHIELD_HEIGHT; i++) {
				for (j = 0; j < MAX_SHIELD_LENGTH; j++) { //Cada for genera un escudo "grande"
					if ((shields[k][i][j].health > 0) && (laser->x > shields[k][i][j].x) && (laser->x < shields[k][i][j].x + INDIVIDUAL_SHIELD_THICKNESS) && (laser->y  > shields[k][i][j].y) && (laser->y < shields[k][i][j].y + INDIVIDUAL_SHIELD_THICKNESS) && ((laser->moving))) { // choco el laser contra el escudo
						laser->moving = false;
						shields[k][i][j].health--;
					}
				}
			}
		}

	}
}
void draw_laser(laser_t laser) {
	if (laser.moving == false) {
		return;
	}
	al_draw_line(laser.x, laser.y, laser.x, laser.y + LASER_LENGTH, RED, LASER_WIDTH);
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

enemyStatus*  decide_enemy_shot(enemyStatus enemy[LEVEL1_ROWS][LEVEL1_COLS]) { //devuelve un puntero al enemigo que va a disparar el proximo disparo
	//printf("ENTRE A DECISE ENEMY SHOT!\n");
	int i, j;
	srand(time(NULL));
	
	int shootingEnemyX = rand() % LEVEL1_COLS;
	
	for (j = shootingEnemyX; j < LEVEL1_COLS; j++) {
		for (i = LEVEL1_ROWS - 1; i >= 0; i--) { 
			if (enemy[i][j].alive) {
				return &enemy[i][j];
			}
		}
	}
	for (j = shootingEnemyX - 1; j >= 0 ; j--) { // Para no hacer dos veces el mismo caso 
		for (i = LEVEL1_ROWS - 1; i >= 0; i--) {
			if (enemy[i][j].alive) {
				return &enemy[i][j];
			}
		}
	}

	return NULL;
}

void start_enemy_shot(enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT], enemyStatus* chosenEnemy) {
	if (count_alive_lasers(enemyLasers) == MAX_ENEMY_LASER_AMOUNT) {
		printf("MAXIMA CANTIDAD DE LASERS\n");
		return;
	}
	int i;
	for (i = 0; i < MAX_ENEMY_LASER_AMOUNT; i++) {
		if (enemyLasers[i].moving == false) {
			enemyLasers[i].moving = true;
			enemyLasers[i].x = chosenEnemy->x + ENEMY_WIDTH / 2;
			enemyLasers[i].y = chosenEnemy->y + ENEMY_HEIGHT;
			return;
		}
	}

}

void update_enemy_shot(enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT], playerStatus* player, shield_t shields[MAX_SHIELD_AMOUNT][MAX_SHIELD_HEIGHT][MAX_SHIELD_LENGTH]) {
	int n;
	int i, k, j;
	for (n = 0; n < MAX_ENEMY_LASER_AMOUNT; n++) {
		if (enemyLasers[n].moving) { // actualizo posicion
			enemyLasers[n].y += 3;
		}
		if ((enemyLasers[n].x > player->x) && (enemyLasers[n].x < player->x + SPACESHIP_SIZE) && (enemyLasers[n].y > PLAYERY) && (enemyLasers[n].y < PLAYERY + SPACESHIP_SIZE) && ((enemyLasers[n].moving))) {// choca contra el jugador
			printf("PERDISTE!");
			enemyLasers[n].moving = false;
		}
		else if (enemyLasers[n].y > DISPLAY_HEIGHT) {
			enemyLasers[n].moving = false;
		}
		else {
			for (k = 0; k < MAX_SHIELD_AMOUNT; k++) {
				for (i = 0; i < MAX_SHIELD_HEIGHT; i++) {
					for (j = 0; j < MAX_SHIELD_LENGTH; j++) { //Cada for genera un escudo "grande"
						if ((shields[k][i][j].health > 0) && (enemyLasers[n].x > shields[k][i][j].x) && (enemyLasers[n].x < shields[k][i][j].x + INDIVIDUAL_SHIELD_THICKNESS) && (enemyLasers[n].y > shields[k][i][j].y) && (enemyLasers[n].y < shields[k][i][j].y + INDIVIDUAL_SHIELD_THICKNESS) && ((enemyLasers[n].moving))) { // choco el laser contra el escudo
							enemyLasers[n].moving = false;
							shields[k][i][j].health--;
						}
					}
				}
			}
		}
	}
	
}

void draw_enemy_laser(enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT]) {
	int i;
	for (i = 0; i < MAX_ENEMY_LASER_AMOUNT; i++) {
		if (enemyLasers[i].moving == true) {
			al_draw_line(enemyLasers[i].x, enemyLasers[i].y, enemyLasers[i].x, enemyLasers[i].y + LASER_LENGTH, GREEN, LASER_WIDTH);
		}
	}
}

void draw_shields(shield_t shields[MAX_SHIELD_AMOUNT][MAX_SHIELD_HEIGHT][MAX_SHIELD_LENGTH]) {
	int i, k, j;
	for (k = 0; k < MAX_SHIELD_AMOUNT; k++) {
		for (i = 0; i < MAX_SHIELD_HEIGHT; i++) {
			for (j = 0; j < MAX_SHIELD_LENGTH; j++) { //Cada for genera un escudo "grande"
				if (shields[k][i][j].health > 0) {
					al_draw_filled_rectangle(shields[k][i][j].x, shields[k][i][j].y, shields[k][i][j].x + INDIVIDUAL_SHIELD_THICKNESS, shields[k][i][j].y + INDIVIDUAL_SHIELD_THICKNESS, BLUE);
				}
			}
		}
	}
}