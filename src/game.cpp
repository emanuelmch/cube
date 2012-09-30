#include "game.h"

#include <allegro5/allegro_native_dialog.h>

#include <iostream>

static const char *GAME_TITLE = "Bill's Awesome Game";

static const int FPS_MAX = 60;

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;

static const int BOUNCER_SIZE = 64;

static inline void show_error(ALLEGRO_DISPLAY *display, const char *error) {
	if (display == NULL) {
		std::cerr << error << std::endl;
		al_rest(3.0);
	} else {
		al_show_native_message_box(display, GAME_TITLE, "Error", error, NULL, ALLEGRO_MESSAGEBOX_ERROR);
	}
}

bool Bill::Game::init() {
	if (!al_init()) {
		show_error(display, "Failed to initialize Allegro!");
		return false;
	}

	al_set_new_display_flags(ALLEGRO_OPENGL);

	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!display) {
		show_error(display, "Failed to create display!");
		return false;
	}

	timer = al_create_timer(1.0 / FPS_MAX);
	if (!timer) {
		show_error(display, "Failed to create timer!");
		return false;
	}

	if (!al_install_keyboard()) {
		show_error(display, "Failed to initialize the keyboard!");
		return false;
	}

	event_queue = al_create_event_queue();
	if (!event_queue) {
		show_error(display, "Failed to create event queue!");
		return false;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	bouncer = new Sprite(BOUNCER_SIZE, BOUNCER_SIZE);
	bouncer->paint();
	if (!bouncer->bitmap) {
		show_error(display, "Failed to create bouncer!");
		return false;
	}

	return true;
}

void Bill::Game::game_loop() {
	bool redraw = true;
	int redrawCount = 0;

	bouncer->x = SCREEN_WIDTH / 2;
	bouncer->y = SCREEN_HEIGHT / 2;

	int bouncer_dx = -16;
	int bouncer_dy = -16;

	al_start_timer(timer);

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

	while (redrawCount < 50) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		switch (ev.type) {
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			return;
		case ALLEGRO_EVENT_KEY_UP:
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
		 		 return;
			break;
		case ALLEGRO_EVENT_TIMER:
			int bouncer_x = bouncer->x + bouncer_dx;
			int bouncer_y = bouncer->y + bouncer_dy;

			if (bouncer_x <= 0 || (bouncer_x+BOUNCER_SIZE) >= SCREEN_WIDTH) {
				bouncer_dx = -bouncer_dx;
				bouncer_x += bouncer_dx;
			}
			
			if (bouncer_y <= 0 || (bouncer_y+BOUNCER_SIZE) >= SCREEN_HEIGHT) {
				bouncer_dy = -bouncer_dy;
				bouncer_y += bouncer_dy;
			}

			bouncer->x = bouncer_x;
			bouncer->y = bouncer_y;

			redraw = true;
			break;
		}

		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));
			bouncer->draw();
			al_flip_display();

			redrawCount++;
		}
	}
}

void Bill::Game::shutdown() {
	if (display) {
		al_destroy_display(display);
		display = NULL;
	}

	if (event_queue) {
		al_destroy_event_queue(event_queue);
		event_queue = NULL;
	}

	if (timer) {
		al_destroy_timer(timer);
		timer = NULL;
	}

	if (bouncer) {
		delete bouncer;
		bouncer = NULL;
	}
}

