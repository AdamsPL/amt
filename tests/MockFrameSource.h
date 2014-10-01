#ifndef _MOCKFRAMESOURCE_H
#define _MOCKFRAMESOURCE_H 

#include "gmock/gmock.h"

#include "FrameSource.h"

class MockFrameSource : public FrameSource
{
public:
	MOCK_METHOD0(open, bool());
	MOCK_METHOD0(close, bool());
	MOCK_METHOD0(fetchFrame, QImage());
};

#endif /* _MOCKFRAMESOURCE_H */
