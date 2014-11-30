#include <gtest/gtest.h>

#include "Samples.h"
#include "Frame.h"
#include "QtEventMonitor.h"
#include "QtEventListener.h"
#include "MockEventHandler.h"

#include <QEventLoop>

TEST(QtEvents, testEventPassing)
{
	QEventLoop loop;
	QtEventMonitor monitor;
	MockEventHandler handler(monitor);

	QSharedPointer<const Frame> ptr1(new Frame(Samples::exampleFrame9));
	QSharedPointer<const Frame> ptr2(new Frame(Samples::exampleFrame2));

	EXPECT_CALL(handler, handleNewFrame(ptr1));
	EXPECT_CALL(handler, handleNewDiffFrame(ptr2));

	monitor.emitNewFrameEvent(ptr1);
	monitor.emitNewDiffFrameEvent(ptr2);
	loop.processEvents(QEventLoop::AllEvents, 50);
}
