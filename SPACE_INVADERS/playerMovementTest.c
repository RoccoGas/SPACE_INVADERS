//ESTO ES UN ARCHIVO SEPARADO (compilarlo solo)!!
////lo hice asi porque tenia miedo cagar algo del posta, dsp habria que unirlo
//
//#include <stdio.h>
//#include <Windows.h>
//#include <assert.h>
//#include <allegro5\allegro.h>
//#include <allegro5/allegro_image.h>
//
//#define PLAYERY 840 //a esta altura no se que tan bien entra el HUD, tal vez haya que ponerlo mas arriba
//
//int main(void) {
//	ALLEGRO_DISPLAY* display;
//	ALLEGRO_BITMAP* bitmap;
//	ALLEGRO_EVENT_QUEUE* queue;
//	ALLEGRO_TIMER* timer;
//	ALLEGRO_EVENT event;
//	ALLEGRO_KEYBOARD_STATE keyState;
//	ALLEGRO_COLOR black;
//
//
//	unsigned int x = 0;
//
//	const char* bitmapSpaceshipFilepath = "sprites/spaceshipf.png";
//
//	al_init();
//	timer = al_create_timer(1.0 / 20);
//	al_start_timer(timer);
//	queue = al_create_event_queue();
//	al_install_keyboard();
//	black = al_map_rgb(0, 0, 0); //asigno color negro
//	al_register_event_source(queue, al_get_timer_event_source(timer));
//
//	display = al_create_display(1280, 960);
//
//	al_init_image_addon();
//	bitmap = al_load_bitmap(bitmapSpaceshipFilepath);
//	assert(bitmap != NULL);
//
//	while (1) {
//		al_get_keyboard_state(&keyState);
//
//		if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) {
//			x += 10;
//		}
//		
//		else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) {
//			x -= 10;
//		}
//		
//
//		al_wait_for_event(queue, &event);
//
//		if (event.type == ALLEGRO_EVENT_TIMER) {
//			al_clear_to_color(black);
//			al_draw_bitmap(bitmap, x, PLAYERY, 0);
//			al_flip_display();
//		}
//
//	}
//
//
//
//	al_destroy_bitmap(bitmap);
//	al_destroy_display(display);
//	al_destroy_event_queue(queue);
//	al_destroy_timer(timer);
//	al_uninstall_keyboard();
//}