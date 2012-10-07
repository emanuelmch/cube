#pragma once

#include "face.h"

namespace Bill {
namespace Cube {

	class Rotate {
	public:
		Rotate() : Rotate(false, Face::UP) {}
		Rotate(bool clockwise, Face face): clockwise(clockwise), face(face) {}

		~Rotate(){}

		bool clockwise;
		Face face;
	};

}
}
