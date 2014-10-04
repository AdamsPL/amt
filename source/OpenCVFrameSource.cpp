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
		return new Frame();

	return new Frame(frame);
}
