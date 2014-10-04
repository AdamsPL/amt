#include "FileFrameSource.h"
#include "FrameDirReader.h"
#include "Samples.h"

#include <gtest/gtest.h>

#include <QDebug>

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

TEST(TestFileFrameSource, testIfAllExtractedFramesAreCorrect)
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

		EXPECT_TRUE(*expFrame == *actFrame);

		delete expFrame;
		delete actFrame;
		iter++;
	}
	fileFrameSource.close();
}
