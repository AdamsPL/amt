#include "Area.h"

#include <gmock/gmock.h>
#include <opencv2/opencv.hpp>

using namespace cv;

TEST(AreaTest, testSinglePoint)
{
	Area area;
	Point testPoint(0, 0);

	EXPECT_FALSE(area.contains(testPoint));
	area.addPoint(testPoint);
	EXPECT_TRUE(area.contains(testPoint));
}

TEST(AreaTest, testPointInPolygon)
{
	Area area;
	Point testPoint(0, 0);

	area.addPoint(Point(4, 4));
	EXPECT_FALSE(area.contains(testPoint));

	area.addPoint(Point(1, 0));
	EXPECT_FALSE(area.contains(testPoint));

	area.addPoint(Point(0, 1));
	EXPECT_FALSE(area.contains(testPoint));

	area.addPoint(Point(-1, -1));
	EXPECT_TRUE(area.contains(testPoint));
}

TEST(AreaTest, testIfPolygonIsConvex)
{
	Area area;
	Point testPoint(0, 0);

	area.addPoint(Point(4, 4));
	EXPECT_FALSE(area.contains(testPoint));

	area.addPoint(Point(-1, 0));
	EXPECT_FALSE(area.contains(testPoint));

	area.addPoint(Point(3, 3));
	EXPECT_FALSE(area.contains(testPoint));

	area.addPoint(Point(0, -1));
	EXPECT_TRUE(area.contains(testPoint));
}

TEST(AreaTest, testSquareArea)
{
	Area area;
	const int size = 4;

	area.addPoint(Point(-size, size));
	area.addPoint(Point(-size, -size));
	area.addPoint(Point(size, size));
	area.addPoint(Point(size, -size));

	for (int y = -size; y <= size; ++y) {
		for (int x = -size; x <= size; ++x) {
			EXPECT_TRUE(area.contains(Point(x, y)));
		}
	}

	EXPECT_FALSE(area.contains(Point(-size - 1, -size)));
	EXPECT_FALSE(area.contains(Point(size + 1, -size)));
	EXPECT_FALSE(area.contains(Point(-size - 1, size)));
	EXPECT_FALSE(area.contains(Point(size + 1, size)));
}

TEST(AreaTest, testClearing)
{
	Area area;
	Point testPoint(0, 0);

	area.addPoint(testPoint);
	EXPECT_TRUE(area.contains(testPoint));
	area.clear();
	EXPECT_FALSE(area.contains(testPoint));
}
