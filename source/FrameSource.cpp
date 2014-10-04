#include "FrameSource.h"

FrameSource::FrameSource()
	: isStreaming(false)
{
	setAutoDelete(false);
	threadPool.setMaxThreadCount(1);
}

bool FrameSource::startStreaming()
{
	isStreaming = true;
	threadPool.start(this);
}

void FrameSource::run()
{
	if (!open())
		isStreaming = false;

	while(isStreaming) {
		Frame *frame = fetchFrame();
		if (frame->isNull())
			isStreaming = false;
		else
			emit frameReady(*frame);
		delete frame;
	}
	close();
}

bool FrameSource::stopStreaming()
{
	isStreaming = false;
	threadPool.waitForDone();

	return true;
}
