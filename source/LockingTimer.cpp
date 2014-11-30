#include "LockingTimer.h"

LockingTimer::LockingTimer(Engine &engine)
	: Timer(engine)
{
	timer.setSingleShot(true);
	connect(&timer, SIGNAL(timeout()), this, SLOT(onTimerTick()), Qt::QueuedConnection);
}

void LockingTimer::onTimerTick()
{
	trigger();
}

LockingTimer::~LockingTimer()
{
}

void LockingTimer::waitFor(int ms)
{
	timer.start(ms);
}
