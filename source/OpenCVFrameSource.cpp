#include "OpenCVFrameSource.h"

using namespace cv;

void OpenCVFrameSource::close()
{
	capture.release();
}

Frame *OpenCVFrameSource::fetchFrame()
{
	Mat frame;

	if (!capture.read(frame))
		return NULL;

	return new Frame(frame);
}

int OpenCVFrameSource::getFps()
{
	return capture.get(CV_CAP_PROP_FPS);
}
