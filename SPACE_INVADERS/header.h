#ifndef __HEADER__
#define __HEADER__

#include "allegro.h"

enum LEVEL_OPTIONS_E { NO_ERROR_START_GAME, DIFFICULTY, SCOREBOARD, QUIT_GAME, RESUME_GAME, QUIT_TO_MENU, BAD_ASSET, BAD_DISPLAY, BAD_QUEUE, BAD_TIMER };

#define DISPLAY_WIDTH 1280
#define DISPLAY_HEIGHT 960

#define NO_FLAGS 0 

#define TIMER_FPS(n)	(1.0/n)

#define SPACESHIP_SIZE 46

#define ENEMY_WIDTH 51
#define ENEMY_HEIGHT 38

#define MOTHERSHIP_WIDTH 64
#define MOTHERSHIP_HEIGHT 28
#define MOTHERSHIP_FREQUENCY_TIMER 300


#define LEVEL1_ROWS 5
#define LEVEL1_COLS 8

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
#define FONT_FILE_PATH "assets/menu/space_invaders_font.ttf"

#define MENU_FONT_SIZE 80
#define HUD_FONT_SIZE 40

#define INITIAL_SHIELD_HEALTH_PART 2
#define MAX_SHIELD_LENGTH 4
#define MAX_SHIELD_HEIGHT 3
#define MAX_SHIELD_AMOUNT 4
#define INDIVIDUAL_SHIELD_THICKNESS 36
#define SHIELD_Y (0.7*DISPLAY_HEIGHT)
#define MAX_SHIELD_ALLEGRO_LENGTH (INDIVIDUAL_SHIELD_THICKNESS*MAX_SHIELD_LENGTH) //MEdida real q toma allegro 

#define SHIELD_OFFSET (DISPLAY_WIDTH - (4*MAX_SHIELD_ALLEGRO_LENGTH))/(MAX_SHIELD_AMOUNT + 1)

enum PLAYER_STATES_E { NOT_MOVING, MOVING_LEFT, MOVING_RIGHT };

typedef struct{
	float x;
	unsigned int score;
	unsigned int lives;
	enum SPACESHIP_STATUS_E state;
	ALLEGRO_BITMAP* bitmap;
} playerStatus;

typedef struct {
	float x;
	float y;
	ALLEGRO_BITMAP* bitmap;
	bool alive;

}	enemyStatus;

typedef struct {
	float x;
	float y;
	bool moving;
}	laser_t;

typedef struct {
	float x;
	float y;
	bool moving;
}	enemyLaser_t;

typedef struct {
	float x;
	float y;
	int health;
} shield_t;

typedef struct {
	float x;
	float y;
	ALLEGRO_BITMAP* bitmap;
	enum SPACESHIP_STATUS_E state;
	bool isAlive;
	unsigned int timer;
} mothership_t;

#endif // !__HEADER__
