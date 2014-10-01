#include "FrameSource.h"

FrameSource::FrameSource()
	: isStreaming(false)
{
	threadPool.setMaxThreadCount(1);
}

bool FrameSource::startStreaming()
{
	if (!open())
		return false;
	isStreaming = true;

	threadPool.start(this);
}

void FrameSource::run()
{
	while(isStreaming) {
		QImage img = fetchFrame();
		if (img.isNull())
			stopStreaming();
		else
			emit frameReady(img);
	}
}

bool FrameSource::stopStreaming()
{
	close();
	isStreaming = false;
	return true;
}
