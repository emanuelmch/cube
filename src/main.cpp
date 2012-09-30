#include "game.h"

#include "cube/cubegame.h"
#include <iostream>

int main() {
	Bill::Cube::CubeGame game;

	if (game.init())
		game.game_loop();

	game.shutdown();

	return 0;
}

