#include "movement.h"
#include <stdio.h>


void enemy_movement_1(enemy_t enemy[MAX_ENEMY_ROWS][MAX_ENEMY_COLS], unsigned int * enemyDirection, unsigned int* downFlag, enemy_t* mostLeftEnemy, enemy_t* mostRightEnemy, int difficulty) { //se usa en ciclos, conviene tener bitmap como parametro



	if ((mostRightEnemy->x + ENEMY_WIDTH) >= DISPLAY_WIDTH && *downFlag == 0) { //todos los sprites de los enemigos tienen el mismo tama�o (o al menos el ancho, arreglar que hacemos)
		printf("CHOQUE CONTRA LA DERACHA!\n");
		update_enemy_y(enemy);
		*enemyDirection = ENEMY_DIRECTION_LEFT;
		*downFlag = 1;
	}	
	else if (mostLeftEnemy->x <= 0 && *downFlag == 0) {    
		printf("CHOQUE CONTRA LA IZQUIERDA!\n");

		update_enemy_y(enemy);
		*enemyDirection = ENEMY_DIRECTION_RIGHT;
		*downFlag = 1;
	}
	else if (*enemyDirection == ENEMY_DIRECTION_RIGHT) {
		update_enemy_x(enemy, *enemyDirection, difficulty);
		*downFlag = 0;
	}
	else if (*enemyDirection == ENEMY_DIRECTION_LEFT) {
		update_enemy_x(enemy, *enemyDirection, difficulty);
		*downFlag = 0;
	}



}

void update_player(player_t* player, ALLEGRO_KEYBOARD_STATE keyboardState, laser_t* laser) {
	if ((player->state == MOVING_RIGHT) && ((player->x + SPACESHIP_SIZE) < DISPLAY_WIDTH)) {
		player->x += 3;
	}
	else if ((player->state == MOVING_LEFT) && (player->x  > 0)) {
		player->x -= 3;
	}
}


void update_enemy_x(enemy_t enemy[MAX_ENEMY_ROWS][MAX_ENEMY_COLS], unsigned int enemyDirection, int difficulty) {
	int i, j;

	for (i = 0; i < MAX_ENEMY_ROWS; i++) {
		for (j = 0; j < MAX_ENEMY_COLS; j++) {

			if (enemyDirection == ENEMY_DIRECTION_RIGHT) {
				enemy[i][j].x +=  2 + 0.5*(float)difficulty;
			}

			else if (enemyDirection == ENEMY_DIRECTION_LEFT) {
				enemy[i][j].x -= 2 + 0.5*(float)difficulty;
			}

		}
	}
}


void update_enemy_y(enemy_t enemy[MAX_ENEMY_ROWS][MAX_ENEMY_COLS]) { // baja a todos los enemigos cuando se chocan contra la pared

	int i, j;
	for (i = MAX_ENEMY_ROWS - 1; i >= 0; i--) {
		for (j = 0; j < MAX_ENEMY_COLS; j++) {
			if (enemy[i][j].alive) { // enecuentra al enemigo "mas abajo"
				if ( enemy[i][j].y >ENEMY_SHIELD_GAP) {
					return;
				}
			}
		}
	}

	printf("ENTRE A UPDATE_ENEMY_Y!\n");
	for (i = 0; i < MAX_ENEMY_ROWS; i++) {
		for (j = 0; j < MAX_ENEMY_COLS; j++) {
			enemy[i][j].y += 20;
		}
	}
}
int count_alive_enemies(enemy_t enemy[MAX_ENEMY_ROWS][MAX_ENEMY_COLS]) {
	int i, j;
	int counter = 0;
	for (i = 0; i < MAX_ENEMY_ROWS; i++) {
		for (j = 0; j < MAX_ENEMY_COLS; j++) {
			if (enemy[i][j].alive) {
				counter++;
			}
		}
	}
	return counter;
}

void shoot_laser(player_t* player, laser_t* laser) {
	if (laser->moving == true) {
		return;
	}
	laser->moving = true;
	laser->x = player->x + (SPACESHIP_SIZE / 2);
	laser->y = PLAYERY;
}

void update_laser(player_t* player, laser_t* laser,
				enemy_t enemy[MAX_ENEMY_ROWS][MAX_ENEMY_COLS], enemy_t** mostRight, enemy_t** mostLeft,
				enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT], shield_t shields[MAX_SHIELD_AMOUNT][MAX_SHIELD_HEIGHT][MAX_SHIELD_LENGTH],
				mothership_t* mothership) {
	unsigned int i, j, k;

	laser->y -= 20;
	if (laser->y < 0) { // llego al techo
		laser->moving = false;
		return;
	}
	
	if (laser->moving) {
		for (i = 0; i < MAX_ENEMY_LASER_AMOUNT; i++) { // Veo si choca con un laser enemigo
			if (enemyLasers[i].moving) {
				if ((enemyLasers[i].x -(LASER_WIDTH/2 + 3) <= laser->x) && (enemyLasers[i].x + (LASER_WIDTH / 2 + 3) >= laser->x) && 
					( laser->y >  enemyLasers[i].y) && ( laser->y < enemyLasers[i].y + LASER_LENGTH)) { // chocaron los lasers
					enemyLasers[i].moving = false;
					laser->moving = false;
					printf("CHOCARON LOS LASERS!\n");
					return;
				}
			}
		}
		for (i = 0; i < MAX_ENEMY_ROWS; i++) {
			for (j = 0; j < MAX_ENEMY_COLS; j++) {
				if ((laser->x > enemy[i][j].x) && (laser->x < enemy[i][j].x + ENEMY_WIDTH) && 
					(laser->y > enemy[i][j].y) && (laser->y < enemy[i][j].y + ENEMY_HEIGHT) && 
					(enemy[i][j].alive)) { //Choco con enemigo
					laser->moving = false;
					enemy[i][j].alive = false;
					player->score += 100;
					if (&enemy[i][j] == *mostLeft) { //mato al enemigo de mas arriba y a la izquierda, hay que actualizarlo
						printf("UPdate de mostleft de  %p a ", *mostLeft);
						*mostLeft = update_most_left(enemy);
						printf("%p\n ", *mostLeft);
						enemy[i][j].alive = false;


					}
					else if (&enemy[i][j] == *mostRight) { // mato al enemigo de mas arriba a la derecha
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
					if ((shields[k][i][j].health > 0) && 
						(laser->x > shields[k][i][j].x) && (laser->x < shields[k][i][j].x + INDIVIDUAL_SHIELD_THICKNESS) && 
						(laser->y  > shields[k][i][j].y) && (laser->y < shields[k][i][j].y + INDIVIDUAL_SHIELD_THICKNESS) && 
						((laser->moving))) { // choco el laser contra el escudo
						laser->moving = false;
						shields[k][i][j].health--;
					}
				}
			}
		}
		if ((mothership->health > 0) && 
			(laser->x > mothership->x) && (laser->x < mothership->x + MOTHERSHIP_WIDTH) &&
			(laser->y > mothership->y) && (laser->y < mothership->y + MOTHERSHIP_HEIGHT) ) { //choca con la mothership

			mothership->health--;
			if(mothership->health == 0){
				player->score += 5000;
				mothership->timer = 0;
			}
			laser->moving = false;
			
			
		}
	}
}


enemy_t* update_most_right(enemy_t enemy[MAX_ENEMY_ROWS][MAX_ENEMY_COLS]) { // busca el enemigo mas arriva y a la derecha posible que este vivo, sirve para saber cuando este se choca contra
	 int i, j;																	// los costados del display para que bajen los enemigos

	for (i = MAX_ENEMY_COLS - 1; i >= 0; i--) {
		for (j = 0; j < MAX_ENEMY_ROWS; j++) {
			if (enemy[j][i].alive) {
				return &enemy[j][i];
			}
		}
	}
	return NULL;
}
enemy_t*  update_most_left(enemy_t enemy[MAX_ENEMY_ROWS][MAX_ENEMY_COLS]) {// busca el enemigo que esta mas arriba y a la izquierda posible  y devuelve un puntero a este
	int i, j;
	for (i = 0; i < MAX_ENEMY_COLS; i++) {
		for (j = 0; j < MAX_ENEMY_ROWS; j++) {
			if (enemy[j][i].alive) {
				

				return &enemy[j][i];
			}
		}
	}
	return NULL;
	
}

int count_alive_lasers(enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT]) { //cuenta los lasers vivos
	int i;
	int counter = 0;
	for (i = 0; i < MAX_ENEMY_LASER_AMOUNT; i++) {
		if (enemyLasers[i].moving) {
			counter++;
		}
	}
	return counter;
}

enemy_t*  decide_enemy_shot(enemy_t enemy[MAX_ENEMY_ROWS][MAX_ENEMY_COLS], int rows, int cols) { //devuelve un puntero al enemigo que va a disparar el proximo disparo
	//printf("ENTRE A DECISE ENEMY SHOT!\n");
	int i, j;
	//srand(time(NULL)); muevo el seed a main asi no me genera lo mismo
	

	
	
	int ciclos = rand() % 51;

	for (i = 0; i < ciclos; i++) {
		rand();
	}

	int shootingEnemyX = rand() % cols;
	int random = rand() % 2;

	if (random == 1) {
		for (j = shootingEnemyX; j < cols; j++) {
			for (i = rows - 1; i >= 0; i--) {
				if (enemy[i][j].alive) {
					return &enemy[i][j];
				}
			}
		}
		for (j = shootingEnemyX - 1; j >= 0; j--) { // Para no hacer dos veces el mismo caso 
			for (i = rows - 1; i >= 0; i--) {
				if (enemy[i][j].alive) {
					return &enemy[i][j];
				}
			}
		}
	}
	else {
		for (j = shootingEnemyX - 1; j >= 0; j--) { // Para no hacer dos veces el mismo caso 
			for (i = rows - 1; i >= 0; i--) {
				if (enemy[i][j].alive) {
					return &enemy[i][j];
				}
			}
		}
		for (j = shootingEnemyX; j < cols; j++) {
			for (i = rows - 1; i >= 0; i--) {
				if (enemy[i][j].alive) {
					return &enemy[i][j];
				}
			}
		}
	}

	return NULL;
}

void start_enemy_shot(enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT], enemy_t* chosenEnemy) { //comienza el disparo del enemigo con un enemigo elegido aleatoriamente
	if (count_alive_lasers(enemyLasers) == MAX_ENEMY_LASER_AMOUNT) {								//pero siempre de la fila mas de abajo
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

void update_enemy_shot(enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT], player_t* player, shield_t shields[MAX_SHIELD_AMOUNT][MAX_SHIELD_HEIGHT][MAX_SHIELD_LENGTH]) {
	int n;
	int i, k, j;
	for (n = 0; n < MAX_ENEMY_LASER_AMOUNT; n++) {
		if (enemyLasers[n].moving) { // actualizo posicion
			enemyLasers[n].y += 5;
		}
		if (((enemyLasers[n].moving)) && 
			(enemyLasers[n].x > player->x) && (enemyLasers[n].x < player->x + SPACESHIP_SIZE) && 
			(enemyLasers[n].y > PLAYERY) && (enemyLasers[n].y < PLAYERY + SPACESHIP_SIZE)) {// choca contra el jugador
			player->lives--;
			destroy_all_enemy_lasers(enemyLasers);
			al_rest(0.2);
			player->x = 0;
			if (player->lives == 0) {
				printf("PERDISTE!");
			}
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

void update_mothership(mothership_t* mothership) {
	if (mothership->health > 0) {
		switch (mothership->state)
		{
		case MOVING_LEFT:
			mothership->x -= 2.4;
			break;
		case MOVING_RIGHT:
			mothership->x += 2.4;
			break;
		}
		if ((mothership->x > DISPLAY_WIDTH + 200) || (mothership->x < -200)) { // si se va de la pantalla no la updateo mas
			mothership->health = 0;
			mothership->timer = 0;
		}
	}
}


void destroy_all_enemy_lasers(laser_t lasers[MAX_ENEMY_LASER_AMOUNT]) {
	int i;
	for (i = 0; i < MAX_ENEMY_LASER_AMOUNT; i++) {
		lasers[i].moving = false;
	}
}