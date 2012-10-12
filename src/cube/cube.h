#pragma once

#include "face.h"
#include "rotate.h"


namespace Bill {
namespace Cube {

	class Cube {
	public:
		Cube();
		~Cube();

		int * get(Face face);

		void clear();
		void rotate(Rotate *rotate); 
		void shuffle();

	private:
		int up[9];
		int left[9];
		int front[9];
		int right[9];
		int back[9];
		int down[9];
	};

}
}

