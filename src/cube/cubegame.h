#pragma once

#include "cube.h"

#include "../game.h"
#include "../sprite.h"

namespace Bill {
namespace Cube {

	class CubeGame : public Game {
	public:
		CubeGame();
		~CubeGame();

		virtual int sub_init();
		virtual void sub_loop_init();
		virtual bool sub_loop_process(ALLEGRO_EVENT &ev);
		virtual void sub_loop_redraw();
	private:
		const int MENU_OPTIONS = 8;

		Bill::Cube::Cube cube;
		Sprite *faces[6];
		bool drawn = false;
	};

}
}

