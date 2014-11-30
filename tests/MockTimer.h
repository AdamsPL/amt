#ifndef _MOCKTIMER_H
#define _MOCKTIMER_H 

#include "gmock/gmock.h"

#include "Timer.h"

class Engine;

class MockTimer : public Timer
{
public:
	MockTimer(Engine &engine) : Timer(engine) {}
	MOCK_METHOD1(waitFor, void(int));
};

#endif /* _MOCKTIMER_H */
