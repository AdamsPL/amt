#ifndef _ABSTRACTEVENTHANDLER_H
#define _ABSTRACTEVENTHANDLER_H 

#include <QSharedPointer>

class Frame;

class AbstractEventHandler
{
public:
	virtual void handleNewFrame(QSharedPointer<const Frame> framePtr) = 0;
	virtual void handleNewDiffFrame(QSharedPointer<const Frame> framePtr) = 0;
};

#endif /* _ABSTRACTEVENTHANDLER_H */
