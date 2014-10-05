#include "FrameStreamer.h"

#include "FrameListener.h"
#include "FrameSource.h"

#include <QDebug>

FrameStreamer::FrameStreamer()
	: isStreamingFlag(false), src(NULL)
{
	setAutoDelete(false);
	threadPool.setMaxThreadCount(1);
}

bool FrameStreamer::isStreaming() const
{
	return isStreamingFlag;
}

void FrameStreamer::addListener(FrameListener *listener)
{
	connect(this, SIGNAL(frameReady(const Frame*)), listener, SLOT(onNewFrameSlot(const Frame*)));
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
		Frame *frame = src->fetchFrame();
		if (!frame)
			isStreamingFlag = false;
		else {
			emit frameReady(frame);
		}
		delete frame;
	}
	src->close();
}

void FrameStreamer::stopStreaming()
{
	isStreamingFlag = false;
	threadPool.waitForDone();
}
