#include "MockFrameSource.h"

#include <QImage>
#include <QMutex>

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::InSequence;

ACTION_P2(UnlockAndReturn, mutex, val)
{
	mutex->unlock();
	return val;
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
		.WillRepeatedly(UnlockAndReturn(&mutex, QImage()));
	EXPECT_CALL(mfs, close())
		.Times(1)
		.WillRepeatedly(Return(true));

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
		.WillRepeatedly(UnlockAndReturn(&mutex, QImage()));

	EXPECT_CALL(mfs, close())
		.WillRepeatedly(Return(true));

	EXPECT_TRUE(mfs.startStreaming());
	mutex.lock();
	EXPECT_TRUE(mfs.stopStreaming());
	mutex.unlock();
}
