#ifndef _EVENTHANDLER_H
#define _EVENTHANDLER_H 

#include <QSharedPointer>

class EventMonitor;
class Frame;

class EventHandler
{
public:
	EventHandler(EventMonitor *parent);
	virtual ~EventHandler();

	inline EventMonitor *getEventMonitor() const { return parent; }

	virtual void handleNewFrame(QSharedPointer<const Frame> framePtr);
	virtual void handleNewDiffFrame(QSharedPointer<const Frame> framePtr);

private:
	EventMonitor *parent;
};

#endif /* _EVENTHANDLER_H */
