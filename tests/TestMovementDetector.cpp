#include "MovementDetector.h"

#include "Frame.h"
#include "Samples.h"

#include <gtest/gtest.h>

TEST(MovementDetector, testForegroundAndBackgroundFramesAreUpdated)
{
	MovementDetector md;
	const Frame *nullFrame = NULL;
	const Frame *firstFrame = new Frame(Samples::exampleFrame);
	const Frame *secondFrame = new Frame(Samples::exampleFrame2);

	const Frame *bg0, *bg1, *fg0, *fg1;
   
	bg0	= md.createBackgroundFrame();
	fg0	= md.createForegroundFrame();

	EXPECT_NE(nullFrame, bg0);
	EXPECT_NE(nullFrame, fg0);
	EXPECT_FALSE(*bg0 == *fg0);

	md.onNewFrame(firstFrame);
	md.onNewFrame(secondFrame);

	bg1	= md.createBackgroundFrame();
	fg1	= md.createForegroundFrame();
	EXPECT_NE(nullFrame, bg1);
	EXPECT_NE(nullFrame, fg1);
	EXPECT_FALSE(*bg1 == *fg1);

	EXPECT_FALSE(*bg0 == *bg1);
	EXPECT_FALSE(*fg0 == *fg1);
}
