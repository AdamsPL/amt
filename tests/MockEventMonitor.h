#ifndef _MOCKEVENTMONITOR_H
#define _MOCKEVENTMONITOR_H 

#include "EventMonitor.h"

#include <gmock/gmock.h>

class MockEventMonitor : public EventMonitor
{
public:
	MOCK_CONST_METHOD1(emitNewFrameEvent, void(QSharedPointer<const Frame>));
	MOCK_CONST_METHOD1(emitNewDiffFrameEvent, void(QSharedPointer<const Frame>));
};

#endif /* _MOCKEVENTMONITOR_H */
