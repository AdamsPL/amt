#include "CameraFrameSource.h"
#include "FrameDirReader.h"
#include "Samples.h"

#include <gtest/gtest.h>

#include <QDebug>

TEST(TestCameraFrameSource, testCameraInitialization)
{
	CameraFrameSource cameraFrameSource;
	EXPECT_TRUE(cameraFrameSource.open());
}

TEST(TestCameraFrameSource, testIfAllFramesAreNotNull)
{
	CameraFrameSource cameraFrameSource;
	int frameCount = 16;

	cameraFrameSource.open();
	while(frameCount-- > 0) {
		Frame *actFrame = cameraFrameSource.fetchFrame();

		EXPECT_FALSE(actFrame->isNull());

		delete actFrame;
	}
	cameraFrameSource.close();
}
