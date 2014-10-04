#ifndef _OPENCVFRAMESOURCE_H
#define _OPENCVFRAMESOURCE_H 

#include "FrameSource.h"

class OpenCVFrameSource : public FrameSource
{
public:
	virtual bool open() = 0;
	virtual void close();
	virtual Frame *fetchFrame();

protected:
	cv::VideoCapture capture;
};

#endif /* _OPENCVFRAMESOURCE_H */
