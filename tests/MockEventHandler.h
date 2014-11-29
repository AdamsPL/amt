#ifndef _MOCKEVENTHANDLER_H
#define _MOCKEVENTHANDLER_H 

#include "EventHandler.h"

#include <gmock/gmock.h>

class MockEventHandler : public EventHandler
{
public:
	MockEventHandler(const EventMonitor &monitor) : EventHandler(monitor) {}
	MOCK_METHOD1(handleNewFrame, void(QSharedPointer<const Frame>));
	MOCK_METHOD1(handleNewDiffFrame, void(QSharedPointer<const Frame>));
};

#endif /* _MOCKEVENTHANDLER_H */
