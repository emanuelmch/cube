#pragma once

#include <allegro5/allegro.h>

namespace Bill {

	class Sprite {
	public:
		Sprite(int width, int height);
		~Sprite();

		int x, y;
		int width, height;

		ALLEGRO_BITMAP *bitmap;
		ALLEGRO_COLOR color;

		void paint();
		void draw();
	};

}

