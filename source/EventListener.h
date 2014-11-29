#ifndef _EVENTLISTENER_H
#define _EVENTLISTENER_H 

#include "AbstractEventHandler.h"

#include <QSharedPointer>

class Frame;

class EventListener : public AbstractEventHandler
{
public:
	EventListener(AbstractEventHandler *handler);
	virtual ~EventListener();

	virtual void handleNewFrame(QSharedPointer<const Frame> framePtr);
	virtual void handleNewDiffFrame(QSharedPointer<const Frame> framePtr);

private:
	AbstractEventHandler *handler;
};

#endif /* _EVENTLISTENER_H */
