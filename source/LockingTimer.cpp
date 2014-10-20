#include "LockingTimer.h"

LockingTimer::LockingTimer()
{
}

LockingTimer::~LockingTimer()
{
	mutex.unlock();
}

void LockingTimer::waitFor(int ms)
{
	condition.wait(&mutex, ms);
}
