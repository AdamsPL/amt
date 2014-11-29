#ifndef _EVENTMONITOR_H
#define _EVENTMONITOR_H 

#include <QSharedPointer>

class Frame;
class EventHandler;

class EventMonitor
{
public:
	virtual void emitNewFrameEvent(QSharedPointer<const Frame> framePtr) const = 0;
	virtual void emitNewDiffFrameEvent(QSharedPointer<const Frame> framePtr) const = 0;
};

#endif /* _EVENTMONITOR_H */
