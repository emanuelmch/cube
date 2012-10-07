#include "cubegame.h"

#include "cube.h"
#include "face.h"

#include <allegro5/allegro_native_dialog.h>

#include <iostream>

static const char *GAME_TITLE = "Bill's Awesome Game";

static const int BLOCK_SIZE = 32;

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;

static inline void show_error(ALLEGRO_DISPLAY *display, const char *error) {
	if (display == NULL) {
		std::cerr << error << std::endl;
		al_rest(3.0);
	} else {
		al_show_native_message_box(display, GAME_TITLE, "Error", error, NULL, ALLEGRO_MESSAGEBOX_ERROR);
	}
}

Bill::Cube::CubeGame::CubeGame() : Game() {
	for (int i = 0; i < 6; i++) {
		faces[i] = new Sprite(BLOCK_SIZE, BLOCK_SIZE);
		faces[i]->color = getFaceColor((Face)i);
		faces[i]->paint();
	}

	this->cube.shuffle();
}

Bill::Cube::CubeGame::~CubeGame() {
	for (int i = 0; i < 6; i++) {
		delete faces[i];
	}
}

int Bill::Cube::CubeGame::sub_init() {
	return true;
}

void Bill::Cube::CubeGame::sub_loop_init() {
}

bool Bill::Cube::CubeGame::sub_loop_process(ALLEGRO_EVENT &ev) {
	ev = ev;
	if (drawn)
		return false;

	return true;
}

static inline void draww(Bill::Sprite *block, int x, int y) {
	block->x = x;
	block->y = y;

	block->draw();
}

static inline void drawme(Bill::Sprite **faces, int *colors, int x1, int x2, int x3, int y1, int y2, int y3) {
	draww(faces[colors[0]], x1, y1);
	draww(faces[colors[1]], x2, y1);
	draww(faces[colors[2]], x3, y1);
	draww(faces[colors[3]], x1, y2);
	draww(faces[colors[4]], x2, y2);
	draww(faces[colors[5]], x3, y2);
	draww(faces[colors[6]], x1, y3);
	draww(faces[colors[7]], x2, y3);
	draww(faces[colors[8]], x3, y3);
}

void Bill::Cube::CubeGame::sub_loop_redraw() {
	// draw up
	drawme(faces, cube.get(Face::UP), 115, 150, 185, 5, 40, 75);
	// draw left
	drawme(faces, cube.get(Face::LEFT), 5, 40, 75, 115, 150, 185);
	// draw front
	drawme(faces, cube.get(Face::FRONT), 115, 150, 185, 115, 150, 185);
	// draw right
	drawme(faces, cube.get(Face::RIGHT), 225, 260, 295, 115, 150, 185);
	// draw back
	drawme(faces, cube.get(Face::BACK), 335, 370, 405, 115, 150, 185);
	// draw down
	drawme(faces, cube.get(Face::DOWN), 115, 150, 185, 225, 260, 295);
}

