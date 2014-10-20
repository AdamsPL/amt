#ifndef _LOCKINGTIMER_H
#define _LOCKINGTIMER_H 

#include "Timer.h"

#include <QMutex>
#include <QWaitCondition>

class LockingTimer : public Timer
{
public:
	LockingTimer();
	~LockingTimer();
	virtual void waitFor(int ms);

private:
	QMutex mutex;
	QWaitCondition condition;
};

#endif /* _LOCKINGTIMER_H */
