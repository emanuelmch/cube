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

static void rotateSides(bool clockwise, int *front, int *left, int *back, int *right, int from, int to, int step) {
	if (clockwise) {
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

static void rotateFace(bool clockwise, int *face) {
	int temp[8];

	if (clockwise) {
		temp[0] = face[6];
		temp[1] = face[3];
		temp[2] = face[0];

		temp[3] = face[7];
		temp[4] = face[4];
		temp[5] = face[1];

		temp[6] = face[8];
		temp[7] = face[5];
		temp[8] = face[2];
	} else {
		temp[0] = face[2];
		temp[1] = face[5];
		temp[2] = face[8];

		temp[3] = face[1];
		temp[4] = face[4];
		temp[5] = face[7];

		temp[6] = face[6];
		temp[7] = face[3];
		temp[8] = face[0];
	}

	memcpy(face, temp, sizeof(int) * 8);
}

void Bill::Cube::Cube::rotate(Rotate *rotate) {
	switch (rotate->face) {
	case UP:
		rotateFace(rotate->clockwise, up);
		rotateSides(rotate->clockwise, front, left, back, right, 0, 2, 1);
		break;
	case LEFT:
		rotateFace(rotate->clockwise, left);
		rotateSides(rotate->clockwise, up, front, down, back, 0, 6, 3);
		break;
	case FRONT:
		rotateFace(rotate->clockwise, front);
		rotateSides(rotate->clockwise, up, right, down, left, 0, 0, 0);
		break;
	case RIGHT:
		rotateFace(rotate->clockwise, right);
		rotateSides(rotate->clockwise, up, back, down, front, 2, 8, 3);
		break;	
	case BACK:
		rotateFace(rotate->clockwise, back);
		rotateSides(rotate->clockwise, up, left, down, right, 0, 0, 0);
		break;	
	case DOWN:
		rotateFace(rotate->clockwise, down);
		rotateSides(rotate->clockwise, front, right, back, left, 6, 8, 1);
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

