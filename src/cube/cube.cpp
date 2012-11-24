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

void Bill::Cube::Cube::clear() {
	for (int i = 0; i < 9; i++) {
		up[i] = Face::UP;
		left[i] = Face::LEFT;
		front[i] = Face::FRONT;
		right[i] = Face::RIGHT;
		back[i] = Face::BACK;
		down[i] = Face::DOWN;
	}
}

static void rotateFace(bool clockwise, int *face) {
	int temp[9];

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

		temp[6] = face[0];
		temp[7] = face[3];
		temp[8] = face[6];
	}

	memcpy(face, temp, sizeof(int) * 9);
}

static void rotateUpDown(bool clockwise, int *front, int *left, int *back, int *right, int from, int to, int step) {
	if (clockwise) {
		for (int i = from; i <= to; i += step) {
			int temp = front[i];
			front[i] = right[i];
			right[i] = back[i];
			back[i] = left[i];
			left[i] = temp;
		}
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

static void rotateLeft(bool clockwise, int *up, int *front, int *down, int *back) {
	if (clockwise) {
		int up0 = up[0];
		int up3 = up[3];
		int up6 = up[6];
		up[0] = back[8];
		up[3] = back[5];
		up[6] = back[2];
		back[8] = down[0];
		back[5] = down[3];
		back[2] = down[6];
		down[0] = front[0];
		down[3] = front[3];
		down[6] = front[6];
		front[0] = up0;
		front[3] = up3;
		front[6] = up6;
	} else {
		int up0 = up[0];
		int up3 = up[3];
		int up6 = up[6];
		up[0] = front[0];
		up[3] = front[3];
		up[6] = front[6];
		front[0] = down[0];
		front[3] = down[3];
		front[6] = down[6];
		down[0] = back[8];
		down[3] = back[5];
		down[6] = back[2];
		back[8] = up0;
		back[5] = up3;
		back[2] = up6;
	}
}

static void rotateRight(bool clockwise, int *up, int *back, int *down, int *front) {
	if (clockwise) {
		int up2 = up[2];
		int up5 = up[5];
		int up8 = up[8];
		up[2] = front[2];
		up[5] = front[5];
		up[8] = front[8];
		front[2] = down[2];
		front[5] = down[5];
		front[8] = down[8];
		down[2] = back[6];
		down[5] = back[3];
		down[8] = back[0];
		back[6] = up2;
		back[3] = up5;
		back[0] = up8;
	} else {
		int up2 = up[2];
		int up5 = up[5];
		int up8 = up[8];
		up[2] = back[6];
		up[5] = back[3];
		up[8] = back[0];
		back[6] = down[2];
		back[3] = down[5];
		back[0] = down[8];
		down[2] = front[2];
		down[5] = front[5];
		down[8] = front[8];
		front[2] = up2;
		front[5] = up5;
		front[8] = up8;
	}
}

static void rotateFront(bool clockwise, int *front, int *left, int *back, int *right) {
	if (!clockwise) {
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
	}
}

static void rotateBack(bool clockwise, int *up, int *left, int *down, int *right) {
	if (clockwise) {
		int up0 = up[0];
		int up1 = up[1];
		int up2 = up[2];

		up[0] = right[2];
		up[1] = right[5];
		up[2] = right[8];

		right[2] = down[8];
		right[5] = down[7];
		right[8] = down[6];

		down[6] = left[0];
		down[7] = left[3];
		down[8] = left[6];

		left[0] = up2;
		left[3] = up1;
		left[6] = up0;
	} else {
		rotateBack(true, up, left, down, right);
		rotateBack(true, up, left, down, right);
		rotateBack(true, up, left, down, right);
	}
}

void Bill::Cube::Cube::rotate(Rotate *rotate) {
	switch (rotate->face) {
	case UP:
		rotateFace(rotate->clockwise, up);
		rotateUpDown(rotate->clockwise, front, left, back, right, 0, 2, 1);
		break;
	case DOWN:
		rotateFace(rotate->clockwise, down);
		rotateUpDown(rotate->clockwise, front, right, back, left, 6, 8, 1);
		break;

	case LEFT:
		rotateFace(rotate->clockwise, left);
		rotateLeft(rotate->clockwise, up, front, down, back);
		break;
	case RIGHT:
		rotateFace(rotate->clockwise, right);
		rotateRight(rotate->clockwise, up, back, down, front);
		break;

	case FRONT:
		rotateFace(rotate->clockwise, front);
		rotateFront(rotate->clockwise, up, right, down, left);
		break;
	case BACK:
		rotateFace(rotate->clockwise, back);
		rotateBack(rotate->clockwise, up, left, down, right);
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

