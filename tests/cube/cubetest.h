#pragma once

#include "../../src/cube/cube.h"
#include "../../src/cube/face.h"

#include <cppunit/extensions/HelperMacros.h>

class CubeTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(CubeTest);

	CPPUNIT_TEST(testNewCube);
	CPPUNIT_TEST(testClear);

	CPPUNIT_TEST(testRotateUp);
	CPPUNIT_TEST(testRotateUpFromShuffled);
	CPPUNIT_TEST(testRotateLeft);
	CPPUNIT_TEST(testRotateLeftFromShuffled);
	CPPUNIT_TEST(testRotateFront);
	CPPUNIT_TEST(testRotateFrontFromShuffled);
	CPPUNIT_TEST(testRotateRight);
	CPPUNIT_TEST(testRotateRightFromShuffled);
	CPPUNIT_TEST(testRotateBack);
	CPPUNIT_TEST(testRotateBackFromShuffled);
	CPPUNIT_TEST(testRotateDown);
	CPPUNIT_TEST(testRotateDownFromShuffled);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testNewCube();
	void testClear();

	void testRotateUp();
	void testRotateUpFromShuffled();
	void testRotateLeft();
	void testRotateLeftFromShuffled();
	void testRotateFront();
	void testRotateFrontFromShuffled();
	void testRotateRight();
	void testRotateRightFromShuffled();
	void testRotateBack();
	void testRotateBackFromShuffled();
	void testRotateDown();
	void testRotateDownFromShuffled();

	// TODO:
	// testRotateTwice
	// testRotateCounterClockwise
	// testRotateTwiceBothDirectionsAreEqual
	// testRotateCounterClockwiseSameAsRotatingThreeTimes
};

