#ifndef __HEADER__
#define __HEADER__

#include "allegro.h"

enum ERROR_OPTIONS_E { NO_ERROR_START_GAME, RESUME_GAME, QUIT_GAME, QUIT_TO_MENU, BAD_ASSET, BAD_DISPLAY, BAD_QUEUE, BAD_TIMER };

#define DISPLAY_WIDTH 1280
#define DISPLAY_HEIGHT 960

#define NO_FLAGS 0 

#define TIMER_FPS(n)	(1.0/n)

#define SPACESHIP_SIZE 46

#define PLAYERY	840

#define PLAYER_Y 20

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

}	enemyStatus;

#endif // !__HEADER__
