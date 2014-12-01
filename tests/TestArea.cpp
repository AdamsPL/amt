#include "Area.h"

#include <gmock/gmock.h>

#include <QDebug>

TEST(AreaTest, testSinglePoint)
{
	Area area;
	QPointF testPoint(0, 0);

	EXPECT_FALSE(area.contains(testPoint));
	area.add(testPoint);
	EXPECT_TRUE(area.contains(testPoint));
}

TEST(AreaTest, testSquareArea)
{
	Area area;
	const int size = 5;

	area.add(QPointF(-size, size));
	area.add(QPointF(-size, -size));
	area.add(QPointF(size, -size));
	area.add(QPointF(size, size));

	for (int y = -size+1; y <= size-1; ++y) {
		for (int x = -size+1; x <= size-1; ++x) {
			EXPECT_TRUE(area.contains(QPointF(x, y)));
		}
	}
	EXPECT_FALSE(area.contains(QPointF(size+1, size+1)));
	EXPECT_FALSE(area.contains(QPointF(size+1, -size-1)));
	EXPECT_FALSE(area.contains(QPointF(size-1, size+1)));
	EXPECT_FALSE(area.contains(QPointF(size-1, -size-1)));
}

TEST(AreaTest, testClearing)
{
	Area area;
	QPointF testPoint(0, 0);

	area.add(testPoint);
	EXPECT_TRUE(area.contains(testPoint));
	area.clear();
	EXPECT_FALSE(area.contains(testPoint));
}
