#pragma once

#include "../../src/cube/cube.h"
#include "../../src/cube/face.h"

#include <cppunit/extensions/HelperMacros.h>

class CubeTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(CubeTest);
	CPPUNIT_TEST(testNewCube);
	CPPUNIT_TEST(testClear);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testNewCube();
	void testClear();

private:
	void testCubeClearValues(Bill::Cube::Cube *cube);
	void testFaceSingleValue(int face, int *values);
};

