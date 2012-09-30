#include "game.h"

#include <iostream>

int main() {
	Bill::Game game;

	if (game.init())
		game.game_loop();

	game.shutdown();

	return 0;
}

