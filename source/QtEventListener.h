#ifndef _QTEVENTLISTENER_H
#define _QTEVENTLISTENER_H 

#include "EventListener.h"

#include <QObject>

class QtEventListener : public QObject, public EventListener
{
Q_OBJECT

public:
	QtEventListener(AbstractEventHandler *handler);
	virtual ~QtEventListener();

public slots:
	virtual void handleNewFrame(QSharedPointer<const Frame> framePtr);
	virtual void handleNewDiffFrame(QSharedPointer<const Frame> framePtr);
};

#endif /* _QTEVENTLISTENER_H */
