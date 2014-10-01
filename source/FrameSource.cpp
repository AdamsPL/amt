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
		QImage img = fetchFrame();
		if (img.isNull())
			isStreaming = false;
		else
			emit frameReady(img);
	}
	close();
}

bool FrameSource::stopStreaming()
{
	isStreaming = false;
	threadPool.waitForDone();

	return true;
}
