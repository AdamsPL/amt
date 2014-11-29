#ifndef _EVENTHANDLER_H
#define _EVENTHANDLER_H 

#include "AbstractEventHandler.h"

class EventMonitor;
class EventListener;

class EventHandler : public AbstractEventHandler
{
public:
	EventHandler(const EventMonitor &monitor);
	virtual ~EventHandler();
	
	inline const EventMonitor &getEventMonitor() const { return monitor; }

	virtual void handleNewFrame(QSharedPointer<const Frame> framePtr);
	virtual void handleNewDiffFrame(QSharedPointer<const Frame> framePtr);

private:
	const EventMonitor &monitor;
	EventListener *listener;
};

#endif /* _EVENTHANDLER_H */
