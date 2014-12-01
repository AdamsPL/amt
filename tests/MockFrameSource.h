#ifndef _MOCKFRAMESOURCE_H
#define _MOCKFRAMESOURCE_H 

#include "gmock/gmock.h"

#include "FrameSource.h"

class MockFrameSource : public FrameSource
{
public:
	MOCK_METHOD0(getFps, int());
	MOCK_METHOD0(open, bool());
	MOCK_METHOD0(close, void());
	MOCK_METHOD0(fetchFrame, Frame*());
};

#endif /* _MOCKFRAMESOURCE_H */
