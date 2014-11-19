#include "Area.h"

#include <gmock/gmock.h>
#include <opencv2/opencv.hpp>

using namespace cv;

TEST(AreaTest, testSinglePoint)
{
	Area area;
	Point testPoint(0, 0);

	EXPECT_FALSE(area.contains(testPoint));
	area.add(testPoint);
	EXPECT_TRUE(area.contains(testPoint));
}

TEST(AreaTest, testPointInPolygon)
{
	Area area;
	Point testPoint(0, 0);

	area.add(Point(4, 4));
	EXPECT_FALSE(area.contains(testPoint));

	area.add(Point(1, 0));
	EXPECT_FALSE(area.contains(testPoint));

	area.add(Point(0, 1));
	EXPECT_FALSE(area.contains(testPoint));

	area.add(Point(-1, -1));
	EXPECT_TRUE(area.contains(testPoint));
}

TEST(AreaTest, testIfPolygonIsConvex)
{
	Area area;
	Point testPoint(0, 0);

	area.add(Point(4, 4));
	EXPECT_FALSE(area.contains(testPoint));

	area.add(Point(-1, 0));
	EXPECT_FALSE(area.contains(testPoint));

	area.add(Point(3, 3));
	EXPECT_FALSE(area.contains(testPoint));

	area.add(Point(0, -1));
	EXPECT_TRUE(area.contains(testPoint));
}

TEST(AreaTest, testSquareArea)
{
	Area area;
	const int size = 4;

	area.add(Point(-size, size));
	area.add(Point(-size, -size));
	area.add(Point(size, size));
	area.add(Point(size, -size));

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

	area.add(testPoint);
	EXPECT_TRUE(area.contains(testPoint));
	area.clear();
	EXPECT_FALSE(area.contains(testPoint));
}

TEST(AreaTest, testSettingGroup)
{
	Area area;
	QString group("newGroup");

	EXPECT_TRUE(area.getGroup().isEmpty());
	area.setGroup(group);
	EXPECT_EQ(group, area.getGroup());
}
