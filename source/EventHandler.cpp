#include "EventHandler.h"

#include "EventMonitor.h"
#include "EventListener.h"

#include <QDebug>

EventHandler::EventHandler(const EventMonitor &monitor)
	: AbstractEventHandler(), monitor(monitor), listener(0)
{
	listener = monitor.createListener(this);
}

EventHandler::~EventHandler()
{
	delete listener;
}

void EventHandler::handleNewFrame(QSharedPointer<const Frame> framePtr)
{
}

void EventHandler::handleNewDiffFrame(QSharedPointer<const Frame> framePtr)
{
}
