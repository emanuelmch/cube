#include "cube.h"

#include <iostream>

Bill::Cube::Cube::Cube() {
	this->clear();
}

Bill::Cube::Cube::~Cube() {}

int * Bill::Cube::Cube::get(Face face) {
	switch (face) {
	case UP:
		return up;
	case DOWN:
		return down;
	case FRONT:
		return front;
	case BACK:
		return back;
	case LEFT:
		return left;
	default:
	case RIGHT:
		return right;
	}
}

static void rotateSides(bool clockwise, int *src, int *front, int *left, int *back, int *right, int from, int to, int step) {
	if (clockwise) {
		int dest[8];

		dest[0] = src[6];
		dest[1] = src[3];
		dest[2] = src[0];

		dest[3] = src[7];
		dest[4] = src[4];
		dest[5] = src[1];

		dest[6] = src[8];
		dest[7] = src[5];
		dest[8] = src[2];

		memcpy(src, dest, sizeof(int) * 8);

		if (step == 0) {
			int front6 = front[6];
			int front7 = front[7];
			int front8 = front[8];

			front[6] = left[0];
			front[7] = left[3];
			front[8] = left[6];

			left[0] = back[2];
			left[3] = back[1];
			left[6] = back[0];

			back[2] = right[8];
			back[1] = right[5];
			back[0] = right[2];

			right[8] = front6;
			right[5] = front7;
			right[2] = front8;
		} else {
			for (int i = from; i <= to; i += step) {
				int temp = front[i];
				front[i] = right[i];
				right[i] = back[i];
				back[i] = left[i];
				left[i] = temp;
			}
		}
	} else {
		int dest[8];

		dest[0] = src[2];
		dest[1] = src[5];
		dest[2] = src[8];

		dest[3] = src[1];
		dest[4] = src[4];
		dest[5] = src[7];

		dest[6] = src[6];
		dest[7] = src[3];
		dest[8] = src[0];

		memcpy(src, dest, sizeof(int) * 8);

		if (step == 0) {
			int front6 = front[6];
			int front7 = front[7];
			int front8 = front[8];
			
			front[6] = right[8];
			front[7] = right[5];
			front[8] = right[2];

			right[8] = back[2];
			right[5] = back[1];
			right[2] = back[0];

			back[2] = left[0];
			back[1] = left[3];
			back[0] = left[6];

			left[0] = front6;
			left[3] = front7;
			left[6] = front8;
		} else {
			for (int i = from; i <= to; i += step) {
				int temp = front[i];
				front[i] = left[i];
				left[i] = back[i];
				back[i] = right[i];
				right[i] = temp;
			}
		}
	}
}

void Bill::Cube::Cube::clear() {
	for (int i = 0; i < 9; i++) {
		up[i] = 0;
		left[i] = 1;
		front[i] = 2;
		right[i] = 3;
		back[i] = 4;
		down[i] = 5;
	}
}

void Bill::Cube::Cube::rotate(Rotate *rotate) {
	switch (rotate->face) {
	case UP:
		rotateSides(rotate->clockwise, up, front, left, back, right, 0, 2, 1);
		break;
	case LEFT:
		rotateSides(rotate->clockwise, left, up, front, down, back, 0, 6, 3);
		break;
	case FRONT:
		rotateSides(rotate->clockwise, front, up, right, down, left, 0, 0, 0);
		break;
	case RIGHT:
		rotateSides(rotate->clockwise, right, up, back, down, front, 2, 8, 3);
		break;	
	case BACK:
		rotateSides(rotate->clockwise, back, up, left, down, right, 0, 0, 0);
		break;	
	case DOWN:
		rotateSides(rotate->clockwise, down, front, right, down, left, 6, 8, 1);
		break;	
	}
}

void Bill::Cube::Cube::shuffle() {
	for (int i = 0; i < 50; i++) {
		Rotate command;
		command.clockwise = (bool)(rand() % 2);
		command.face = (Face)(rand() % FACE_COUNT);
		this->rotate(&command);
	}
}

