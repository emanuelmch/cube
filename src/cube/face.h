#pragma once

#include <allegro5/allegro.h>

namespace Bill {
namespace Cube {

	const int FACE_COUNT = 6;

	enum Face {
		UP, DOWN, LEFT, RIGHT, FRONT, BACK
	};

	static inline ALLEGRO_COLOR getFaceColor(Face f) {
		switch (f) {
		case UP:
			return al_map_rgb(255, 255, 255);
		case DOWN:
			return al_map_rgb(255, 255, 0);
		case LEFT:
			return al_map_rgb(124, 252, 0);
		case RIGHT:
			return al_map_rgb(0, 0, 255);
		case FRONT:
			return al_map_rgb(255, 0, 0);
		case BACK:
			return al_map_rgb(255, 165, 0);
		}
		return al_map_rgb(0, 0, 0);
	}

}
}
