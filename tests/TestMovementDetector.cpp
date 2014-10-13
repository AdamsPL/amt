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

	const Frame *fg0, *fg1;
   
	fg0	= md.createForegroundFrame();

	EXPECT_NE(nullFrame, fg0);

	md.onNewFrame(firstFrame);
	md.onNewFrame(secondFrame);

	fg1	= md.createForegroundFrame();
	EXPECT_NE(nullFrame, fg1);
	EXPECT_FALSE(*fg0 == *fg1);
}
