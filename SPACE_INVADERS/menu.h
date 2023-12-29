
#ifndef __MENU__
#define __MENU__ 

#include "header.h"
#include "allegro.h"

#define MENU_FONT_SIZE 80
#define HUD_FONT_SIZE 40
#define MENU_FPS 10 // La unica manera de q funcione los eventos de allegro es con un frame muy bajo en este caso

enum ERROR_OPTIONS_E pause_menu(ALLEGRO_DISPLAY* display); //igual q menu de comienzo solo, que no genera un nuevo display, usa el viejo
enum ERROR_OPTIONS_E start_menu(ALLEGRO_DISPLAY* display);


#endif // __MENU__
