#pragma once

#include "sprite.h"

#include <allegro5/allegro.h>

namespace Bill {

	class Game {
	public:
		Game() {
			display = NULL;
			event_queue = NULL;
		}
		~Game() {}

		bool init();
		void game_loop();
		void shutdown();
	private:
		ALLEGRO_DISPLAY *display;
		ALLEGRO_EVENT_QUEUE *event_queue;
		ALLEGRO_TIMER *timer;

		Sprite *bouncer;
	};

}
