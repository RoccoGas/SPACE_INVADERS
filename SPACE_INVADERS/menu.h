
#ifndef __MENU__
#define __MENU__ 

#include "header.h"
#include "allegro.h"

#define MENU_FONT_SIZE 60
#define HUD_FONT_SIZE 40
#define MENU_FPS 10 // La unica manera de q funcione los eventos de allegro es con un frame muy bajo en este caso

enum LEVEL_OPTIONS_E pause_menu(ALLEGRO_DISPLAY* display); //igual q menu de comienzo solo, que no genera un nuevo display, usa el viejo
enum LEVEL_OPTIONS_E start_menu(ALLEGRO_DISPLAY* display);
enum LEVEL_OPTIONS_E difficulty_menu(ALLEGRO_DISPLAY* display, enum DIFFICULTY_MODE_E* difficulty);


#endif // __MENU__
