#include "FileFrameSource.h"
#include "FrameDirReader.h"
#include "Samples.h"

#include <gtest/gtest.h>

TEST(TestFileFrameSource, testIfExtractedFramesAreCorrect)
{
	FrameDirReader frameDirReader;

	FileFrameSource fileFrameSource(Samples::rats);
	EXPECT_TRUE(fileFrameSource.open());
}
