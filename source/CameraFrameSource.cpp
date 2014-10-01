#include "CameraFrameSource.h"

bool CameraFrameSource::open()
{
	return true;
}

bool CameraFrameSource::close()
{
	return true;
}

QImage CameraFrameSource::fetchFrame()
{
	return QImage();
}
