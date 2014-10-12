#ifndef _MOVEMENTDETECTOR_H
#define _MOVEMENTDETECTOR_H 

#include "FrameListener.h"

#include <opencv2/opencv.hpp>

class MovementDetector : public FrameListener
{
public:
	MovementDetector();
	virtual ~MovementDetector();

	void onNewFrame(const Frame *frame);
	const Frame *createForegroundFrame();
	const Frame *createBackgroundFrame();

private:
	cv::BackgroundSubtractor *substractorPtr;
	cv::Mat background;
	cv::Mat foreground;
};

#endif /* _MOVEMENTDETECTOR_H */
