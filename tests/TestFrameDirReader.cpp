#include "FrameDirReader.h"
#include "Samples.h"

#include <gtest/gtest.h>

TEST(TestFrameDirReader, testInitialization)
{
	FrameDirReader fdr;
	int count = 5;
	Frame *frame;

	EXPECT_EQ(0, fdr.getUnusedFrames());
	while(count-- > 0) {
		frame = fdr.popFrame();
		EXPECT_TRUE(frame->isNull());
		delete frame;
	}
}

TEST(TestFrameDirReader, testBadDirectory)
{
	FrameDirReader fdr;
	EXPECT_FALSE(fdr.readExpectedFrames("foo/bar"));
}

TEST(TestFrameDirReader, testReadingFrames)
{
	FrameDirReader fdr;
	int frameCount;
	Frame *frame;

	EXPECT_TRUE(fdr.readExpectedFrames(Samples::ratsFrameDir));

	frameCount = fdr.getUnusedFrames();
	EXPECT_EQ(Samples::ratsFrameCount, frameCount);

	while(frameCount--) {
		frame = fdr.popFrame();
		EXPECT_FALSE(frame->isNull());
		delete frame;
	}

	EXPECT_EQ(0, fdr.getUnusedFrames());

	frame = fdr.popFrame();
	EXPECT_TRUE(frame->isNull());
	delete frame;

	EXPECT_EQ(0, fdr.getUnusedFrames());
}
