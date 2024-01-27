#include "drawing.h"
#include "allegro.h"
#include "header.h"

void draw_all_enemies(enemy_t enemy[MAX_ENEMY_ROWS][MAX_ENEMY_COLS], int rows, int cols) {
	int i, j;
	for (i = 0; i < MAX_ENEMY_ROWS; i++) {
		for (j = 0; j < MAX_ENEMY_COLS; j++) {
			if (enemy[i][j].alive) {
				al_draw_bitmap(enemy[i][j].bitmap, enemy[i][j].x, enemy[i][j].y, 0);
			}
		}
	}
}

void draw_laser(laser_t laser) {
	if (laser.moving == false) {
		return;
	}
	al_draw_line(laser.x, laser.y, laser.x, laser.y + LASER_LENGTH, RED, LASER_WIDTH);
}

void draw_enemy_laser(enemyLaser_t enemyLasers[MAX_ENEMY_LASER_AMOUNT]) {
	int i;
	for (i = 0; i < MAX_ENEMY_LASER_AMOUNT; i++) {
		if (enemyLasers[i].moving == true) {
			al_draw_line(enemyLasers[i].x, enemyLasers[i].y, enemyLasers[i].x, enemyLasers[i].y + LASER_LENGTH, GREEN, LASER_WIDTH);
		}
	}
}

void draw_mothership(mothership_t* mothership) {
	if (mothership->health > 0) {
		al_draw_bitmap(mothership->bitmap, mothership->x, mothership->y, 0);
	}
}

void draw_shields(shield_t shields[MAX_SHIELD_AMOUNT][MAX_SHIELD_HEIGHT][MAX_SHIELD_LENGTH]) {
	int i, k, j;
	for (k = 0; k < MAX_SHIELD_AMOUNT; k++) {
		for (i = 0; i < MAX_SHIELD_HEIGHT; i++) {
			for (j = 0; j < MAX_SHIELD_LENGTH; j++) { //Cada for genera un escudo "grande"
				if (shields[k][i][j].health > 0) {
					al_draw_filled_rectangle(shields[k][i][j].x, shields[k][i][j].y, shields[k][i][j].x + INDIVIDUAL_SHIELD_THICKNESS, shields[k][i][j].y + INDIVIDUAL_SHIELD_THICKNESS, shields[k][i][j].health == 1 ? RED : BLUE);
				}
			}
		}
	}
}
void draw_HUD(player_t* player, ALLEGRO_FONT* font) {
	al_draw_textf(font, WHITE, 10, DISPLAY_HEIGHT - 50, 0, "LIVES: %d", player->lives);
	al_draw_textf(font, WHITE, DISPLAY_WIDTH - 350, DISPLAY_HEIGHT - 50, 0, "SCORE: %d", player->score);

}
void draw_lose_screen() {
	ALLEGRO_FONT* HUDfont = al_load_font(FONT_FILE_PATH, 60, NO_FLAGS);
	if (HUDfont == NULL) {
		printf("Failed to load: %s\n", FONT_FILE_PATH);
		return BAD_ASSET;
	}
	al_clear_to_color(BLACK2);
	al_draw_textf(HUDfont, RED, DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "YOU LOSE");
	al_flip_display();
	al_rest(2.0);
}

void draw_win_screen() {
	ALLEGRO_FONT* HUDfont = al_load_font(FONT_FILE_PATH, 60, NO_FLAGS);
	if (HUDfont == NULL) {
		printf("Failed to load: %s\n", FONT_FILE_PATH);
		return BAD_ASSET;
	}
	al_clear_to_color(BLACK2);
	al_draw_textf(HUDfont, GREEN, DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "YOU WIN!!!");
	al_flip_display();
	al_rest(2.0);
}