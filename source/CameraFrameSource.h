#ifndef _CAMERAFRAMESOURCE_H
#define _CAMERAFRAMESOURCE_H 

#include "OpenCVFrameSource.h"

class CameraFrameSource : public OpenCVFrameSource
{
public:
	virtual bool open();
};

#endif /* _CAMERAFRAMESOURCE_H */
