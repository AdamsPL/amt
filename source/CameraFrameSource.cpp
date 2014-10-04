#include "CameraFrameSource.h"

bool CameraFrameSource::open()
{
	return capture.open(0);
}
