#include "Engine.h"

#include "Timer.h"
#include "Frame.h"
#include "FrameSource.h"
#include "EventMonitor.h"

#include <QSharedPointer>

#include <QDebug>

Engine::Engine()
	: timer(0), frameDelay(0), source(0), monitor(0)
{
}

void Engine::schedule()
{
	Frame *frame = 0;
	
	if (timer)
		timer->waitFor(frameDelay);
}

void Engine::fetchFrame()
{
	Frame *frame = 0;
	
	if (source)
		frame = source->fetchFrame();

	if (!frame || !monitor)
		return;

	monitor->emitNewFrameEvent(QSharedPointer<const Frame>(frame));
}

void Engine::setSource(FrameSource *src)
{
	if (source) {
		source->close();
		delete source;
	}
	source = src;
	source->open();
}
