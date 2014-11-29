#include "EventHandler.h"

EventHandler::EventHandler(EventMonitor *parent)
	: parent(parent)
{
}

EventHandler::~EventHandler()
{
}

void EventHandler::handleNewFrame(QSharedPointer<const Frame>)
{
}

void EventHandler::handleNewDiffFrame(QSharedPointer<const Frame>)
{
}
