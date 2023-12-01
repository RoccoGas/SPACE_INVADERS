#ifndef __HEADER__
#define __HEADER__

enum ERROR_OPTIONS_E { NO_ERROR_START_GAME, RESUME_GAME, QUIT_GAME, QUIT_TO_MENU, BAD_ASSET, BAD_DISPLAY, BAD_QUEUE, BAD_TIMER };

#define DISPLAY_WIDTH 1280
#define DISPLAY_HEIGHT 960

#define NO_FLAGS 0 

#define TIMER_FPS(n)	(1.0/n)

#define PLAYER_Y 20

typedef struct{
	float x;
	unsigned int score;
	unsigned int lives;
} playerStatus;

#endif // !__HEADER__
