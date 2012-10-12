#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

namespace Bill {

	class Game {
	public:
		ALLEGRO_DISPLAY *display;

		Game();
		~Game() {}

		bool init();
		void game_loop();
		void shutdown();

		virtual int sub_init() = 0;
		virtual void sub_loop_init() = 0;
		virtual bool sub_loop_process(ALLEGRO_EVENT &ev) = 0;
		virtual void sub_loop_redraw() = 0;

		ALLEGRO_FONT *font;

	private:
		ALLEGRO_EVENT_QUEUE *event_queue;
		ALLEGRO_TIMER *timer;
	};

}
