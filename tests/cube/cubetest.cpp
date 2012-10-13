#include "cubetest.h"

using Bill::Cube::Cube;
using Bill::Cube::Face;

CPPUNIT_TEST_SUITE_REGISTRATION(CubeTest);

void CubeTest::setUp() {}
void CubeTest::tearDown() {}

void CubeTest::testNewCube() {
	Cube cube;

	testCubeClearValues(&cube);
}

void CubeTest::testClear() {
	Cube cube;

	cube.shuffle();
	cube.clear();

	testCubeClearValues(&cube);
}

void CubeTest::testCubeClearValues(Bill::Cube::Cube *cube) {
	for (int face = 0; face < Bill::Cube::FACE_COUNT; face++) {
		int *values = cube->get((Face)face);
		testFaceSingleValue(face, values);
	}
}

void CubeTest::testFaceSingleValue(int face, int *values) {
	for (int i = 0; i < 9; i++)
		CPPUNIT_ASSERT_EQUAL(face, values[i]);
}

