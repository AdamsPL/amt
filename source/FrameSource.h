#ifndef _FRAMESOURCE_H
#define _FRAMESOURCE_H 

#include <Frame.h>

class FrameSource
{

public:
	virtual bool open() = 0;
	virtual void close() = 0;
	virtual Frame *fetchFrame() = 0;
};

#endif /* _FRAMESOURCE_H */
