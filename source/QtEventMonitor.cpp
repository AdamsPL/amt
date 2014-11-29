#include "QtEventMonitor.h"

#include "QtEventListener.h"

EventListener *QtEventMonitor::createListener(AbstractEventHandler *handler) const
{
	QtEventListener *listener = new QtEventListener(handler);

	connect(this, SIGNAL(newFrameEvent(QSharedPointer<const Frame>)), listener, SLOT(handleNewFrame(QSharedPointer<const Frame>)));
	connect(this, SIGNAL(newDiffFrameEvent(QSharedPointer<const Frame>)), listener, SLOT(handleNewDiffFrame(QSharedPointer<const Frame>)));

	return listener;
}

void QtEventMonitor::emitNewFrameEvent(QSharedPointer<const Frame> framePtr) const
{
	emit newFrameEvent(framePtr);
}

void QtEventMonitor::emitNewDiffFrameEvent(QSharedPointer<const Frame> framePtr) const
{
	emit newDiffFrameEvent(framePtr);
}
