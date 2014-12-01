#include "DiffAlgorithm.h"

#include "Frame.h"
#include "Samples.h"
#include "MockEventMonitor.h"

#include <gtest/gtest.h>

#include <QDebug>

using ::testing::_;
using ::testing::Return;

TEST(DiffAlgorithm, testChangedAreas)
{
	MockEventMonitor monitor;

	EXPECT_CALL(monitor, createListener(_))
		.WillRepeatedly(Return(static_cast<EventListener*>(0)));

	DiffAlgorithm diff(monitor);
	QSharedPointer<const Frame> firstFrame(new Frame(Samples::exampleFrame));
	QSharedPointer<const Frame> secondFrame(new Frame(Samples::exampleFrame9));
	int i;
	const int iterations = 10;
	const int changedAreas = 21;
	EXPECT_CALL(monitor, emitNewDiffFrameEvent(_))
		.Times(iterations + 1);

	EXPECT_EQ(diff.getChangedAreas().size(), 0);

	for (i = 0; i < iterations; ++i)
		diff.handleNewFrame(firstFrame);

	EXPECT_EQ(diff.getChangedAreas().size(), 0);

	diff.handleNewFrame(secondFrame);

	EXPECT_EQ(changedAreas, diff.getChangedAreas().size());
}
