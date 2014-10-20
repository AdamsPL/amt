#include "MovementDetector.h"

#include "Frame.h"
#include "Samples.h"

#include <gtest/gtest.h>

#include <QDebug>

TEST(MovementDetector, testForegroundAndBackgroundFramesAreUpdated)
{
	MovementDetector md;
	const Frame *nullFrame = NULL;
	const Frame *firstFrame = new Frame(Samples::exampleFrame);
	const Frame *secondFrame = new Frame(Samples::exampleFrame2);

	const Frame *fg0, *fg1;
   
	fg0	= md.createForegroundFrame();

	EXPECT_NE(nullFrame, fg0);

	md.onNewFrame(firstFrame);
	md.onNewFrame(secondFrame);

	fg1	= md.createForegroundFrame();
	EXPECT_NE(nullFrame, fg1);
	EXPECT_FALSE(*fg0 == *fg1);
}

TEST(MovementDetector, testChangedAreas)
{
	MovementDetector md;
	const Frame *firstFrame = new Frame(Samples::exampleFrame);
	const Frame *secondFrame = new Frame(Samples::exampleFrame9);
	int i;
	const int iterations = 10;

	EXPECT_EQ(md.getChangedAreas().size(), 0);

	for (i = 0; i < iterations; ++i)
		md.onNewFrame(firstFrame);

	EXPECT_EQ(md.getChangedAreas().size(), 0);

	md.onNewFrame(secondFrame);

	EXPECT_TRUE(md.getChangedAreas().size() > 5);
	EXPECT_TRUE(md.getChangedAreas().size() < 15);
}
