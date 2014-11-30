#ifndef _LOCKINGTIMER_H
#define _LOCKINGTIMER_H 

#include "Timer.h"

#include <QTimer>

class LockingTimer : public QObject, public Timer
{
Q_OBJECT

public:
	LockingTimer(Engine &engine);
	~LockingTimer();
	virtual void waitFor(int ms);

private slots:
	void onTimerTick();

private:
	QTimer timer;
};

#endif /* _LOCKINGTIMER_H */
