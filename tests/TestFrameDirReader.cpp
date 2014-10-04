#include "FrameDirReader.h"
#include "Samples.h"

#include <gtest/gtest.h>

TEST(TestFrameDirReader, testInitialization)
{
	FrameDirReader fdr;
	int count = 5;

	EXPECT_EQ(0, fdr.getUnusedFrames());
	while(count-- > 0)
		fdr.verifyFrame(QImage());
}

TEST(TestFrameDirReader, testBadDirectory)
{
	FrameDirReader fdr;
	EXPECT_FALSE(fdr.readExpectedFrames("foo/bar"));
}

TEST(TestFrameDirReader, testReadingFrames)
{
	FrameDirReader fdr;

	EXPECT_TRUE(fdr.readExpectedFrames(Samples::ratsFrameDir));
	EXPECT_EQ(Samples::ratsFrameCount, fdr.getUnusedFrames());
}
