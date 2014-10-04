#include "MockFrameSource.h"

#include <QImage>
#include <QMutex>

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::InSequence;

/*
ACTION_P2(UnlockAndReturnNew, mutex, val)
{
	mutex->unlock();
	return new Frame();
}

TEST(FrameSourceTest, testOpenAndcloseOnStartAndStopStreaming)
{
	MockFrameSource mfs;
	QMutex mutex;
	InSequence seq;

	mutex.lock();

	EXPECT_CALL(mfs, open())
		.Times(1)
		.WillRepeatedly(Return(true));
	EXPECT_CALL(mfs, fetchFrame())
		.WillRepeatedly(UnlockAndReturnNew(&mutex, 0));
	EXPECT_CALL(mfs, close())
		.Times(1);

	EXPECT_TRUE(mfs.startStreaming());
	mutex.lock();
	EXPECT_TRUE(mfs.stopStreaming());
	mutex.unlock();
}

TEST(FrameSourceTest, testStopFetchFrameWhenFrameIsNull)
{
	QImage img(100, 100, QImage::Format_RGB32);
	MockFrameSource mfs;
	QMutex mutex;
	InSequence seq;

	ASSERT_FALSE(img.isNull());

	mutex.lock();

	EXPECT_CALL(mfs, open())
		.WillRepeatedly(Return(true));

	EXPECT_CALL(mfs, fetchFrame())
		.Times(5)
		.WillOnce(Return(img))
		.WillOnce(Return(img))
		.WillOnce(Return(img))
		.WillOnce(Return(img))
		.WillRepeatedly(UnlockAndReturnNew(&mutex, 0));

	EXPECT_CALL(mfs, close())
		.WillOnce(Return());

	EXPECT_TRUE(mfs.startStreaming());
	mutex.lock();
	EXPECT_TRUE(mfs.stopStreaming());
	mutex.unlock();
}
*/
