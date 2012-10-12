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
		case UP: // white #FFFFFF
			return al_map_rgb(0xFF, 0xFF, 0xFF);
		case DOWN: // yellow #FFD500
			return al_map_rgb(0xFF, 0xD5, 0x00);
		case LEFT: // red #C41E3A
			return al_map_rgb(0xC4, 0x1E, 0x3A);
		case RIGHT: // orange #FF5800
			return al_map_rgb(0xFF, 0x58, 0x00);
		case FRONT: // blue #0051BA
			return al_map_rgb(0x00, 0x51, 0xBA);
		case BACK: // green #009E60
			return al_map_rgb(0x00, 0x9E, 0x60);
		}
		return al_map_rgb(0, 0, 0);
	}

}
}
