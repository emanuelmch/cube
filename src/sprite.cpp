#include "sprite.h"

Bill::Sprite::Sprite(int width, int height) {
	this->bitmap = NULL;
	this->width = width;
	this->height = height;
	this->color = al_map_rgb(0, 0, 255);
}

Bill::Sprite::~Sprite() {
	if (bitmap) {
		al_destroy_bitmap(bitmap);
		bitmap = NULL;
	}
}

void Bill::Sprite::paint() {
	if (!bitmap)
		this->bitmap = al_create_bitmap(width, height);

	ALLEGRO_BITMAP *current = al_get_target_bitmap();

	al_set_target_bitmap(this->bitmap);
	al_clear_to_color(this->color);
	
	al_set_target_bitmap(current);
}

void Bill::Sprite::draw() {
	al_draw_bitmap(bitmap, this->x, this->y, 0);
}

