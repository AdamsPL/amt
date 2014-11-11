#include "FileFrameSource.h"
#include "FrameDirReader.h"
#include "Samples.h"

#include <gtest/gtest.h>

TEST(TestFileFrameSource, testNotExistingFileHandling)
{
	const QString notExistingFile("foo.avi");
	FileFrameSource fileFrameSource(notExistingFile);

	EXPECT_FALSE(fileFrameSource.open());
}

TEST(TestFileFrameSource, testExistingFileHandling)
{
	FileFrameSource fileFrameSource(Samples::rats);

	EXPECT_TRUE(fileFrameSource.open());
}

TEST(TestFileFrameSource, DISABLED_testIfAllExtractedFramesAreCorrect)
{
	FileFrameSource fileFrameSource(Samples::rats);
	FrameDirReader frameDirReader;
	const int extraFrames = 5;
	int frameCount;
	int iter = 0;

	frameDirReader.readExpectedFrames(Samples::ratsFrameDir);
	frameCount = frameDirReader.getUnusedFrames() + extraFrames;

	fileFrameSource.open();
	while(frameCount-- > 0) {
		Frame *expFrame = frameDirReader.popFrame();
		Frame *actFrame = fileFrameSource.fetchFrame();

		EXPECT_TRUE((expFrame == NULL) == (actFrame == NULL));
		if (expFrame != NULL && actFrame != NULL)
			EXPECT_TRUE(*expFrame == *actFrame);

		delete expFrame;
		delete actFrame;
		iter++;
	}
	fileFrameSource.close();
}
