#ifndef _EVENTMONITOR_H
#define _EVENTMONITOR_H 

#include <QSharedPointer>

class Frame;
class AbstractEventHandler;
class EventListener;

class EventMonitor
{
public:
	virtual EventListener *createListener(AbstractEventHandler *handler) const = 0;
	virtual void emitNewFrameEvent(QSharedPointer<const Frame> framePtr) const = 0;
	virtual void emitNewDiffFrameEvent(QSharedPointer<const Frame> framePtr) const = 0;
};

#endif /* _EVENTMONITOR_H */
