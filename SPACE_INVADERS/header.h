#ifndef __HEADER__
#define __HEADER__

#include "allegro.h"

enum ERROR_OPTIONS_E { NO_ERROR_START_GAME, RESUME_GAME, QUIT_GAME, QUIT_TO_MENU, BAD_ASSET, BAD_DISPLAY, BAD_QUEUE, BAD_TIMER };

#define DISPLAY_WIDTH 1280
#define DISPLAY_HEIGHT 960

#define NO_FLAGS 0 

#define TIMER_FPS(n)	(1.0/n)

#define SPACESHIP_SIZE 46

#define ENEMY_WIDTH 51
#define ENEMY_HEIGHT 38

#define LEVEL1_ROWS 3
#define LEVEL1_COLS 6

#define PLAYERY	840

#define LASER_LENGTH 20
#define LASER_WIDTH 4

#define MAX_ENEMY_LASER_AMOUNT 20

#define ENEMY_DIRECTION_RIGHT 1
#define ENEMY_DIRECTION_LEFT 0
#define INITIAL_X_OFFSET 60
#define INITIAL_Y_OFFSET 60
#define DEFAULT_ENEMY_DIRECTION ENEMY_DIRECTION_RIGHT
#define ENEMY1_FILE_PATH "sprites/enemy1f.png"

#define INITIAL_SHIELD_HEALTH 5
#define MAX_SHIELD_LENGTH 3 // son cuadrados
#define MAX_SHIELD_HEIGHT MAX_SHIELD_LENGTH
#define MAX_SHIELD_AMOUNT 4
#define INDIVIDUAL_SHIELD_THICKNESS 26
#define SHIELD_Y (0.75*DISPLAY_HEIGHT)
#define MAX_SHIELD_ALLEGRO_LENGTH (INDIVIDUAL_SHIELD_THICKNESS*MAX_SHIELD_LENGTH) //MEdida real q toma allegro 

#define SHIELD_OFFSET (DISPLAY_WIDTH - (4*MAX_SHIELD_ALLEGRO_LENGTH))/(MAX_SHIELD_AMOUNT + 1)



typedef struct{
	float x;
	unsigned int score;
	unsigned int lives;
	ALLEGRO_BITMAP* bitmap;
} playerStatus;

typedef struct {
	float x;
	float y;
	ALLEGRO_BITMAP* bitmap;
	bool alive;

}	enemyStatus;

#endif // !__HEADER__
