#include "Timer.h"

#include "Engine.h"

Timer::Timer(Engine &engine)
	: engine(engine)
{
}

void Timer::trigger()
{
	engine.fetchFrame();
}
