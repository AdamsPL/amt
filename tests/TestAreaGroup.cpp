#include "AreaGroup.h"
#include "Area.h"

#include <gmock/gmock.h>
#include <opencv2/opencv.hpp>

using namespace cv;

TEST(AreaGroupTest, testAddingAreas)
{
	AreaGroup areaGroup;
	Area area;
	Point testPoint(0, 0);

	ASSERT_FALSE(areaGroup.contains(testPoint));

	areaGroup.addArea(&area);
	EXPECT_FALSE(areaGroup.contains(testPoint));

	area.addPoint(testPoint);
	EXPECT_TRUE(areaGroup.contains(testPoint));
}
