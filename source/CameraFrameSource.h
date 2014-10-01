#ifndef _CAMERAFRAMESOURCE_H
#define _CAMERAFRAMESOURCE_H 

#include "FrameSource.h"

class CameraFrameSource : public FrameSource
{
public:
	virtual bool open();
	virtual bool close();
	virtual QImage fetchFrame();
};

#endif /* _CAMERAFRAMESOURCE_H */
