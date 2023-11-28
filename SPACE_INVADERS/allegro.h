
#ifndef __ALLEGRO__
#define __ALLEGRO__

#include <stdbool.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

// --------------------------     colores      -------------------------- //
#define BLACK           al_map_rgb(14,14,14)
#define WHITE           al_map_rgb(255,255,255)
#define RED             al_map_rgb(255,0,0)
#define GREEN           al_map_rgb(0,155,0)
#define BLUE			al_map_rgb(0,0,155)
#define GREY            al_map_rgb(128, 128, 128)
#define BACK            al_map_rgb(150, 175, 0)
#define YELLOW          al_map_rgb(255, 255, 0)

bool initialize_allegro();                     //Funcion que inicializa todo allegro. No recibe nada. Devuelve un true si esta todo ok, false si hay error.
void destroy_allegro(void);


#endif // __ALLEGRO__
