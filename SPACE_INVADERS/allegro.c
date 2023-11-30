#include "allegro.h"

#include <stdio.h>

bool initialize_allegro() {                      //Funcion que inicializa todo allegro. No recibe nada. Devuelve un true si esta todo ok, false si hay error.

    if (!al_init()) {
        fprintf(stdout, "Failed to initialize Allegro!");
        return false;
    }

    if (!al_init_image_addon()) {       // ADDON necesario para manejo de imagenes 
        fprintf(stdout, "Failed to initialize image addon!");
        return false;
    }

    if (!al_init_font_addon()) {        // ADDON necesario para manejo de fuentes 
        fprintf(stdout, "Failed to initialize font addon!");
        al_shutdown_image_addon();
        return false;
    }

    if (!al_init_primitives_addon()) {   // ADDON necesario para manejo de formas
        fprintf(stdout, "Failed to initialize primitives addon!");
        al_shutdown_image_addon();
        al_shutdown_font_addon();
        return false;
    }

    if (!al_init_ttf_addon()) {        // ADDON necesario para manejo de fuentes 
        fprintf(stdout, "Failed to initialize ttf addon!");
        al_shutdown_image_addon();
        al_shutdown_font_addon();
        al_shutdown_primitives_addon();
        return false;
    }

    if (!al_install_audio()) {
        fprintf(stdout, "Failed to install audio!");
        al_shutdown_image_addon();
        al_shutdown_font_addon();
        al_shutdown_primitives_addon();
        al_shutdown_ttf_addon();
        return false;
    }

    if (!al_init_acodec_addon()) {
        fprintf(stdout, "Failed to initialize acodec addon!");
        al_shutdown_image_addon();
        al_shutdown_font_addon();
        al_shutdown_primitives_addon();
        al_shutdown_ttf_addon();
        al_uninstall_audio();
        return false;
    }

    if (!al_install_keyboard()) {
        fprintf(stdout, "Failed to install keyboard!");
        al_shutdown_image_addon();
        al_shutdown_font_addon();
        al_shutdown_primitives_addon();
        al_shutdown_ttf_addon();
        al_uninstall_audio();
        return false;
    }

    if (!al_install_mouse()) {
        fprintf(stdout, "Failed to install mouse!");
        al_shutdown_image_addon();
        al_shutdown_font_addon();
        al_shutdown_primitives_addon();
        al_shutdown_ttf_addon();
        al_uninstall_audio();
        al_uninstall_keyboard();
        return false;
    }


    return true;

}

void destroy_allegro(void) {
    al_shutdown_image_addon();
    al_shutdown_ttf_addon();
    al_shutdown_font_addon();
    al_shutdown_primitives_addon();
    al_uninstall_audio();
    al_uninstall_mouse();
    al_uninstall_keyboard();
}