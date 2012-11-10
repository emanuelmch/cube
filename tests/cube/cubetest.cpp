#include "cubetest.h"

#include "../../src/cube/rotate.h"

using Bill::Cube::Cube;
using Bill::Cube::Face;
using Bill::Cube::Rotate;

CPPUNIT_TEST_SUITE_REGISTRATION(CubeTest);

static inline void assertArrayEquals(const std::string msg, const int *actual, const int v0, const int v1, const int v2, const int v3, const int v4, const int v5, const int v6, const int v7, const int v8) {
	CPPUNIT_ASSERT_EQUAL_MESSAGE(msg + "0", v0, actual[0]);
	CPPUNIT_ASSERT_EQUAL_MESSAGE(msg + "1", v1, actual[1]);
	CPPUNIT_ASSERT_EQUAL_MESSAGE(msg + "2", v2, actual[2]);
	CPPUNIT_ASSERT_EQUAL_MESSAGE(msg + "3", v3, actual[3]);
	CPPUNIT_ASSERT_EQUAL_MESSAGE(msg + "4", v4, actual[4]);
	CPPUNIT_ASSERT_EQUAL_MESSAGE(msg + "5", v5, actual[5]);
	CPPUNIT_ASSERT_EQUAL_MESSAGE(msg + "6", v6, actual[6]);
	CPPUNIT_ASSERT_EQUAL_MESSAGE(msg + "7", v7, actual[7]);
	CPPUNIT_ASSERT_EQUAL_MESSAGE(msg + "8", v8, actual[8]);
}

static inline void assertArraySingleValue(const std::string msg, const int *actual, const int face) {
	assertArrayEquals(msg, actual, face, face, face, face, face, face, face, face, face);
}

static inline void assertCubeClearValues(Bill::Cube::Cube *cube) {
	for (int face = 0; face < Bill::Cube::FACE_COUNT; face++) {
		int *values = cube->get((Face)face);
		std::string msg = "Face ";
		msg += face;
		msg += ":";
		assertArraySingleValue(msg, values, face);
	}
}

void CubeTest::setUp() {}
void CubeTest::tearDown() {}

void CubeTest::testNewCube() {
	Cube cube;

	assertCubeClearValues(&cube);
}

void CubeTest::testClear() {
	Cube cube;

	cube.shuffle();
	cube.clear();

	assertCubeClearValues(&cube);
}

void CubeTest::testRotateUp() {
	Cube cube;

	Rotate rotate(true, Face::UP);
	cube.rotate(&rotate);

	int *up = cube.get(Face::UP);
	int *down = cube.get(Face::DOWN);
	int *left = cube.get(Face::LEFT);
	int *right = cube.get(Face::RIGHT);
	int *front = cube.get(Face::FRONT);
	int *back = cube.get(Face::BACK);

	assertArraySingleValue("Face UP:", up, Face::UP);
	assertArraySingleValue("Face DOWN:", down, Face::DOWN);
	assertArrayEquals("Face LEFT:", left, Face::FRONT, Face::FRONT, Face::FRONT, Face::LEFT, Face::LEFT, Face::LEFT, Face::LEFT, Face::LEFT, Face::LEFT);
	assertArrayEquals("Face RIGHT:", right, Face::BACK, Face::BACK, Face::BACK, Face::RIGHT, Face::RIGHT, Face::RIGHT, Face::RIGHT, Face::RIGHT, Face::RIGHT);
	assertArrayEquals("Face FRONT:", front, Face::RIGHT, Face::RIGHT, Face::RIGHT, Face::FRONT, Face::FRONT, Face::FRONT, Face::FRONT, Face::FRONT, Face::FRONT);
	assertArrayEquals("Face BACK:", back, Face::LEFT, Face::LEFT, Face::LEFT, Face::BACK, Face::BACK, Face::BACK, Face::BACK, Face::BACK, Face::BACK);
}

void CubeTest::testRotateUpFromShuffled() {
	Cube cube;
	cube.shuffle();

	int oldUp[9], oldDown[9], oldLeft[9], oldRight[9], oldFront[9], oldBack[9];
	memcpy(oldUp, cube.get(Face::UP), sizeof(int) * 9);
	memcpy(oldDown, cube.get(Face::DOWN), sizeof(int) * 9);
	memcpy(oldLeft, cube.get(Face::LEFT), sizeof(int) * 9);
	memcpy(oldRight, cube.get(Face::RIGHT), sizeof(int) * 9);
	memcpy(oldFront, cube.get(Face::FRONT), sizeof(int) * 9);
	memcpy(oldBack, cube.get(Face::BACK), sizeof(int) * 9);

	Rotate rotate(true, Face::UP);
	cube.rotate(&rotate);

	int *up = cube.get(Face::UP);
	int *down = cube.get(Face::DOWN);
	int *left = cube.get(Face::LEFT);
	int *right = cube.get(Face::RIGHT);
	int *front = cube.get(Face::FRONT);
	int *back = cube.get(Face::BACK);

	assertArrayEquals("Face UP:", up, oldUp[6], oldUp[3], oldUp[0], oldUp[7], oldUp[4], oldUp[1], oldUp[8], oldUp[5], oldUp[2]);
	assertArrayEquals("Face DOWN:", down, oldDown[0], oldDown[1], oldDown[2], oldDown[3], oldDown[4], oldDown[5], oldDown[6], oldDown[7], oldDown[8]);
	assertArrayEquals("Face LEFT:", left, oldFront[0], oldFront[1], oldFront[2], oldLeft[3], oldLeft[4], oldLeft[5], oldLeft[6], oldLeft[7], oldLeft[8]);
	assertArrayEquals("Face RIGHT:", right, oldBack[0], oldBack[1], oldBack[2], oldRight[3], oldRight[4], oldRight[5], oldRight[6], oldRight[7], oldRight[8]);
	assertArrayEquals("Face FRONT:", front, oldRight[0], oldRight[1], oldRight[2], oldFront[3], oldFront[4], oldFront[5], oldFront[6], oldFront[7], oldFront[8]);
	assertArrayEquals("Face BACK:", back, oldLeft[0], oldLeft[1], oldLeft[2], oldBack[3], oldBack[4], oldBack[5], oldBack[6], oldBack[7], oldBack[8]);
}

void CubeTest::testRotateLeft() {
	Cube cube;

	Rotate rotate(true, Face::LEFT);
	cube.rotate(&rotate);

	int *up = cube.get(Face::UP);
	int *down = cube.get(Face::DOWN);
	int *left = cube.get(Face::LEFT);
	int *right = cube.get(Face::RIGHT);
	int *front = cube.get(Face::FRONT);
	int *back = cube.get(Face::BACK);

	assertArraySingleValue("Face LEFT:", left, Face::LEFT);
	assertArraySingleValue("Face RIGHT:", right, Face::RIGHT);
	assertArrayEquals("Face UP:", up, Face::BACK, Face::UP, Face::UP, Face::BACK, Face::UP, Face::UP, Face::BACK, Face::UP, Face::UP);
	assertArrayEquals("Face DOWN:", down, Face::FRONT, Face::DOWN, Face::DOWN, Face::FRONT, Face::DOWN, Face::DOWN, Face::FRONT, Face::DOWN, Face::DOWN);
	assertArrayEquals("Face FRONT:", front, Face:: UP, Face::FRONT, Face::FRONT, Face::UP, Face::FRONT, Face::FRONT, Face::UP, Face::FRONT, Face::FRONT);
	assertArrayEquals("Face BACK:", back, Face::BACK, Face::BACK, Face::DOWN, Face::BACK, Face::BACK, Face::DOWN, Face::BACK, Face::BACK, Face::DOWN);
}

void CubeTest::testRotateLeftFromShuffled() {
	// TODO
}

void CubeTest::testRotateFront() {
	Cube cube;

	Rotate rotate(true, Face::FRONT);
	cube.rotate(&rotate);

	int *up = cube.get(Face::UP);
	int *down = cube.get(Face::DOWN);
	int *left = cube.get(Face::LEFT);
	int *right = cube.get(Face::RIGHT);
	int *front = cube.get(Face::FRONT);
	int *back = cube.get(Face::BACK);

	assertArraySingleValue("Face FRONT:", front, Face::FRONT);
	assertArraySingleValue("Face BACK:", back, Face::BACK);
	assertArrayEquals("Face LEFT:", left, Face::LEFT, Face::LEFT, Face::DOWN, Face::LEFT, Face::LEFT, Face::DOWN, Face::LEFT, Face::LEFT, Face::DOWN);
	assertArrayEquals("Face RIGHT:", right, Face::UP, Face::RIGHT, Face::RIGHT, Face::UP, Face::RIGHT, Face::RIGHT, Face::UP, Face::RIGHT, Face::RIGHT);
	assertArrayEquals("Face UP:", up, Face::UP, Face::UP, Face::UP, Face::UP, Face::UP, Face::UP, Face::LEFT, Face::LEFT, Face::LEFT);
	assertArrayEquals("Face DOWN:", down, Face::RIGHT, Face::RIGHT, Face::RIGHT, Face::DOWN, Face::DOWN, Face::DOWN, Face::DOWN, Face::DOWN, Face::DOWN);
}

void CubeTest::testRotateFrontFromShuffled() {
	// TODO
}

void CubeTest::testRotateRight() {
	Cube cube;

	Rotate rotate(true, Face::RIGHT);
	cube.rotate(&rotate);

	int *up = cube.get(Face::UP);
	int *down = cube.get(Face::DOWN);
	int *left = cube.get(Face::LEFT);
	int *right = cube.get(Face::RIGHT);
	int *front = cube.get(Face::FRONT);
	int *back = cube.get(Face::BACK);

	assertArraySingleValue("Face RIGHT:", right, Face::RIGHT);
	assertArraySingleValue("Face LEFT:", left, Face::LEFT);
	assertArrayEquals("Face UP:", up, Face::UP, Face::UP, Face::FRONT, Face::UP, Face::UP, Face::FRONT, Face::UP, Face::UP, Face::FRONT);
	assertArrayEquals("Face DOWN:", down, Face::DOWN, Face::DOWN, Face::BACK, Face::DOWN, Face::DOWN, Face::BACK, Face::DOWN, Face::DOWN, Face::BACK);
	assertArrayEquals("Face FRONT:", front, Face::FRONT, Face::FRONT, Face::DOWN, Face::FRONT, Face::FRONT, Face::DOWN, Face::FRONT, Face::FRONT, Face::DOWN);
	assertArrayEquals("Face BACK:", back, Face::UP, Face::BACK, Face::BACK, Face::UP, Face::BACK, Face::BACK, Face::UP, Face::BACK, Face::BACK);
}

void CubeTest::testRotateRightFromShuffled() {
	// TODO
}

void CubeTest::testRotateBack() {
	Cube cube;

	Rotate rotate(true, Face::BACK);
	cube.rotate(&rotate);

	int *up = cube.get(Face::UP);
	int *down = cube.get(Face::DOWN);
	int *left = cube.get(Face::LEFT);
	int *right = cube.get(Face::RIGHT);
	int *front = cube.get(Face::FRONT);
	int *back = cube.get(Face::BACK);

	assertArraySingleValue("Face BACK:", back, Face::BACK);
	assertArraySingleValue("Face FRONT:", front, Face::FRONT);
	assertArrayEquals("Face LEFT:", left, Face::UP, Face::LEFT, Face::LEFT, Face::UP, Face::LEFT, Face::LEFT, Face::UP, Face::LEFT, Face::LEFT);
	assertArrayEquals("Face RIGHT:", right, Face::RIGHT, Face::RIGHT, Face::DOWN, Face::RIGHT, Face::RIGHT, Face::DOWN, Face::RIGHT, Face::RIGHT, Face::DOWN);
	assertArrayEquals("Face UP:", up, Face::RIGHT, Face::RIGHT, Face::RIGHT, Face::UP, Face::UP, Face::UP, Face::UP, Face::UP, Face::UP);
	assertArrayEquals("Face DOWN:", down, Face::DOWN, Face::DOWN, Face::DOWN, Face::DOWN, Face::DOWN, Face::DOWN, Face::LEFT, Face::LEFT, Face::LEFT);
}

void CubeTest::testRotateBackFromShuffled() {
	// TODO
}

void CubeTest::testRotateDown() {
	Cube cube;

	Rotate rotate(true, Face::DOWN);
	cube.rotate(&rotate);

	int *up = cube.get(Face::UP);
	int *down = cube.get(Face::DOWN);
	int *left = cube.get(Face::LEFT);
	int *right = cube.get(Face::RIGHT);
	int *front = cube.get(Face::FRONT);
	int *back = cube.get(Face::BACK);

	assertArraySingleValue("Face DOWN:", down, Face::DOWN);
	assertArraySingleValue("Face UP:", up, Face::UP);
	assertArrayEquals("Face LEFT:", left, Face::LEFT, Face::LEFT, Face::LEFT, Face::LEFT, Face::LEFT, Face::LEFT, Face::BACK, Face::BACK, Face::BACK);
	assertArrayEquals("Face RIGHT:", right, Face::RIGHT, Face::RIGHT, Face::RIGHT, Face::RIGHT, Face::RIGHT, Face::RIGHT, Face::FRONT, Face::FRONT, Face::FRONT);
	assertArrayEquals("Face FRONT:", front, Face::FRONT, Face::FRONT, Face::FRONT, Face::FRONT, Face::FRONT, Face::FRONT, Face::LEFT, Face::LEFT, Face::LEFT);
	assertArrayEquals("Face BACK:", back, Face::BACK, Face::BACK, Face::BACK, Face::BACK, Face::BACK, Face::BACK, Face::RIGHT, Face::RIGHT, Face::RIGHT);
}

void CubeTest::testRotateDownFromShuffled() {
	// TODO
}

