#include "EventListener.h"

EventListener::EventListener(AbstractEventHandler *handler)
	: handler(handler)
{
}

EventListener::~EventListener()
{
}

void EventListener::handleNewFrame(QSharedPointer<const Frame> framePtr)
{
	handler->handleNewFrame(framePtr);
}

void EventListener::handleNewDiffFrame(QSharedPointer<const Frame> framePtr)
{
	handler->handleNewDiffFrame(framePtr);
}
