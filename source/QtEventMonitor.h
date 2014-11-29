#ifndef _QTEVENTMONITOR_H
#define _QTEVENTMONITOR_H 

#include "EventMonitor.h"

#include <QObject>

class QtEventMonitor : public QObject, public EventMonitor
{
Q_OBJECT

public:
	virtual EventListener *createListener(AbstractEventHandler *handler) const;
	virtual void emitNewFrameEvent(QSharedPointer<const Frame> framePtr) const;
	virtual void emitNewDiffFrameEvent(QSharedPointer<const Frame> framePtr) const;

signals:
	void newFrameEvent(QSharedPointer<const Frame> framePtr) const;
	void newDiffFrameEvent(QSharedPointer<const Frame> framePtr) const;
};

#endif /* _QTEVENTMONITOR_H */
