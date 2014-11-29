#include "Engine.h"

#include "Timer.h"
#include "Frame.h"
#include "FrameSource.h"
#include "EventMonitor.h"

#include <QSharedPointer>

Engine::Engine()
	: timer(0), frameDelay(0), source(0), monitor(0)
{
}

void Engine::iterate()
{
	Frame *frame = 0;
	
	if (timer)
		timer->waitFor(frameDelay);

	if (source)
		frame = source->fetchFrame();

	if (frame && monitor)
		monitor->emitNewFrameEvent(QSharedPointer<const Frame>(frame));
}
