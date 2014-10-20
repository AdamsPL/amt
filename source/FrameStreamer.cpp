#include "FrameStreamer.h"

#include "FrameListener.h"
#include "FrameSource.h"
#include "Frame.h"
#include "Timer.h"

#include <QSharedPointer>

Q_DECLARE_METATYPE(QSharedPointer<const Frame>)

FrameStreamer::FrameStreamer()
	: isStreamingFlag(false), src(NULL), timer(NULL), frameDelay(0)
{
	setAutoDelete(false);
	threadPool.setMaxThreadCount(1);
	qRegisterMetaType< QSharedPointer<const Frame> >();
}

FrameStreamer::~FrameStreamer()
{
	stopStreaming();
}

bool FrameStreamer::isStreaming() const
{
	return isStreamingFlag;
}

void FrameStreamer::addListener(FrameListener *listener)
{
	connect(this, SIGNAL(frameReady(QSharedPointer<const Frame>)), listener, SLOT(onNewFrameSlot(QSharedPointer<const Frame>)));
}

void FrameStreamer::setFrameSource(FrameSource *source)
{
	src = source;
}

void FrameStreamer::startStreaming()
{
	isStreamingFlag = true;
	threadPool.start(this);
}

void FrameStreamer::run()
{
	if (!src)
		return;

	if (!src->open())
		isStreamingFlag = false;

	while(isStreamingFlag) {
		if (timer)
			timer->waitFor(frameDelay);
		const Frame *frame = src->fetchFrame();
		if (!frame)
			isStreamingFlag = false;
		else {
			emit frameReady(QSharedPointer<const Frame>(frame));
		}
	}
	src->close();
}

void FrameStreamer::stopStreaming()
{
	isStreamingFlag = false;
	threadPool.waitForDone();
}

void FrameStreamer::setFrameDelay(int delay)
{
	frameDelay = delay;
}

void FrameStreamer::setTimer(Timer *timer)
{
	this->timer = timer;
}
