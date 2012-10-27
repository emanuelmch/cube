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
	// TODO
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

	assertArraySingleValue("Face BACK:", back, Face::BACK);
	assertArraySingleValue("Face FRONT:", front, Face::FRONT);
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

	assertArraySingleValue("Face LEFT:", left, Face::LEFT);
	assertArraySingleValue("Face RIGHT:", right, Face::RIGHT);
	assertArrayEquals("Face UP:", up, Face::BACK, Face::UP, Face::UP, Face::BACK, Face::UP, Face::UP, Face::BACK, Face::UP, Face::UP);
	assertArrayEquals("Face DOWN:", down, Face::FRONT, Face::DOWN, Face::DOWN, Face::FRONT, Face::DOWN, Face::DOWN, Face::FRONT, Face::DOWN, Face::DOWN);
	assertArrayEquals("Face FRONT:", front, Face::UP, Face::FRONT, Face::FRONT, Face::UP, Face::FRONT, Face::FRONT, Face::UP, Face::FRONT, Face::FRONT);
	assertArrayEquals("Face BACK:", back, Face::BACK, Face::BACK, Face::DOWN, Face::BACK, Face::BACK, Face::DOWN, Face::BACK, Face::BACK, Face::DOWN);
}

void CubeTest::testRotateRightFromShuffled() {
	// TODO
}

void CubeTest::testRotateBack() {
	// TODO
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

	assertArraySingleValue("Face UP:", up, Face::UP);
	assertArraySingleValue("Face DOWN:", down, Face::DOWN);
	assertArrayEquals("Face LEFT:", left, Face::LEFT, Face::LEFT, Face::LEFT, Face::LEFT, Face::LEFT, Face::LEFT, Face::BACK, Face::BACK, Face::BACK);
	assertArrayEquals("Face RIGHT:", right, Face::RIGHT, Face::RIGHT, Face::RIGHT, Face::RIGHT, Face::RIGHT, Face::RIGHT, Face::FRONT, Face::FRONT, Face::FRONT);
	assertArrayEquals("Face FRONT:", front, Face::FRONT, Face::FRONT, Face::FRONT, Face::FRONT, Face::FRONT, Face::FRONT, Face::LEFT, Face::LEFT, Face::LEFT);
	assertArrayEquals("Face BACK:", back, Face::BACK, Face::BACK, Face::BACK, Face::BACK, Face::BACK, Face::BACK, Face::RIGHT, Face::RIGHT, Face::RIGHT);
}

void CubeTest::testRotateDownFromShuffled() {
	// TODO
}

