#include "QtEventListener.h"

QtEventListener::QtEventListener(AbstractEventHandler *handler)
	: QObject(), EventListener(handler)
{
}

QtEventListener::~QtEventListener()
{
}

void QtEventListener::handleNewFrame(QSharedPointer<const Frame> framePtr)
{
	EventListener::handleNewFrame(framePtr);
}

void QtEventListener::handleNewDiffFrame(QSharedPointer<const Frame> framePtr)
{
	EventListener::handleNewDiffFrame(framePtr);
}
