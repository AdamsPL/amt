#include "AreaGroup.h"
#include "Area.h"

#include <gmock/gmock.h>
#include <opencv2/opencv.hpp>

using namespace cv;

TEST(AreaGroupTest, testAddingAndRemovingAreas)
{
	AreaGroup areaGroup;
	Area area;
	Point testPoint(0, 0);

	ASSERT_FALSE(areaGroup.contains(testPoint));

	areaGroup.add(&area);
	EXPECT_FALSE(areaGroup.contains(testPoint));

	area.add(testPoint);
	EXPECT_TRUE(areaGroup.contains(testPoint));

	areaGroup.remove(&area);
	EXPECT_FALSE(areaGroup.contains(testPoint));
}
