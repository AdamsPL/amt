#ifndef _MOCKFRAMELISTENER_H
#define _MOCKFRAMELISTENER_H 

#include "FrameListener.h"

#include <gmock/gmock.h>

class MockFrameListener : public FrameListener
{
public:
	MOCK_METHOD1(onNewFrame, void(const Frame *frame));
};

#endif /* _MOCKFRAMELISTENER_H */
