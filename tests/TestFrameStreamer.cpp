#include "FrameStreamer.h"
#include "MockFrameSource.h"
#include "MockFrameListener.h"
#include "Samples.h"

#include <QImage>
#include <QEventLoop>
#include <QCoreApplication>

#include <QDebug>

using ::testing::_;
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::InSequence;
using ::testing::ReturnNew;
using ::testing::InvokeWithoutArgs;
using ::testing::DoAll;

Frame *nullFrame = NULL;

TEST(FrameStreamerTest, testInitialization)
{
	FrameStreamer streamer;

	streamer.startStreaming();
	streamer.stopStreaming();
}

TEST(FrameStreamerTest, testOpenAndcloseOnFrameSource)
{
	FrameStreamer streamer;
	MockFrameSource mfs;
	QEventLoop loop;

	EXPECT_CALL(mfs, open())
		.WillRepeatedly(Return(true));

	EXPECT_CALL(mfs, fetchFrame())
		.Times(AtLeast(1))
		.WillRepeatedly(DoAll(InvokeWithoutArgs(&loop, &QEventLoop::quit), Return(nullFrame)));

	EXPECT_CALL(mfs, close());

	streamer.setFrameSource(&mfs);

	streamer.startStreaming();
	loop.exec();
	streamer.stopStreaming();
}

TEST(FrameSourceTest, testStopFetchFrameWhenFrameIsNull)
{
	FrameStreamer streamer;
	MockFrameListener listener;
	MockFrameSource mfs;
	QEventLoop loop;

	Frame *frame0 = new Frame(Samples::exampleFrame);
	Frame *frame1 = new Frame(Samples::exampleFrame);
	Frame *frame2 = new Frame(Samples::exampleFrame);

	EXPECT_CALL(mfs, open())
		.WillRepeatedly(Return(true));

	EXPECT_CALL(mfs, fetchFrame())
		.Times(4)
		.WillOnce(Return(frame0))
		.WillOnce(Return(frame1))
		.WillOnce(Return(frame2))
		.WillRepeatedly(Return(nullFrame));

	EXPECT_CALL(listener, onNewFrame(frame0));
	EXPECT_CALL(listener, onNewFrame(frame1));
	EXPECT_CALL(listener, onNewFrame(frame2))
		.Times(1)
		.WillOnce(InvokeWithoutArgs(&loop, &QEventLoop::quit));

	EXPECT_CALL(mfs, close());

	streamer.setFrameSource(&mfs);
	streamer.addListener(&listener);
	
	streamer.startStreaming();
	loop.exec();
	streamer.stopStreaming();
}

TEST(FrameSourceTest, testStopStreaming)
{
	FrameStreamer streamer;
	QEventLoop loop;
	MockFrameSource mfs;
	InSequence seq;

	EXPECT_CALL(mfs, open())
		.WillRepeatedly(Return(true));

	EXPECT_CALL(mfs, fetchFrame())
		.Times(10)
		.WillRepeatedly(ReturnNew<Frame>(Samples::exampleFrame));

	EXPECT_CALL(mfs, fetchFrame())
		.WillOnce(DoAll(InvokeWithoutArgs(&loop, &QEventLoop::quit), ReturnNew<Frame>(Samples::exampleFrame)))
		.WillRepeatedly(ReturnNew<Frame>(Samples::exampleFrame));

	EXPECT_CALL(mfs, close());

	streamer.setFrameSource(&mfs);

	streamer.startStreaming();
	loop.exec();
	streamer.stopStreaming();
}
