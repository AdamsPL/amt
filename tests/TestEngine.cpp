#include <gtest/gtest.h>

#include "Engine.h"
#include "MockTimer.h"
#include "MockFrameSource.h"
#include "MockEventMonitor.h"
#include "Samples.h"

using ::testing::Return;
using ::testing::_;

TEST(TestEngine, testInitialization)
{
	Engine engine;
	engine.iterate();
}

TEST(TestEngine, testTimer)
{
	Engine engine;
	const int delay = 200;
	MockTimer timer;

	engine.setFrameDelay(delay);
	engine.setTimer(&timer);

	EXPECT_CALL(timer, waitFor(delay));

	engine.iterate();
}

TEST(TestEngine, testFrameFetching)
{
	MockEventMonitor monitor;
	Engine engine;
	Frame *frame = new Frame(Samples::exampleFrame);
	MockFrameSource src;
	QSharedPointer<const Frame> *framePtr = new QSharedPointer<const Frame>(frame);

	engine.setSource(&src);
	engine.setEventMonitor(&monitor);

	EXPECT_CALL(src, fetchFrame())
		.Times(1)
		.WillRepeatedly(Return(frame));

	EXPECT_CALL(monitor, emitNewFrameEvent(*framePtr));

	engine.iterate();
}