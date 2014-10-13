#ifndef _MOVEMENTDETECTOR_H
#define _MOVEMENTDETECTOR_H 

#include "FrameListener.h"

#include <opencv2/opencv.hpp>
#include <QSharedPointer>

class MovementDetector : public FrameListener
{
Q_OBJECT

public:
	MovementDetector();
	virtual ~MovementDetector();

	void onNewFrame(const Frame *frame);
	const Frame *createForegroundFrame();

signals:
	void movementDetected(QSharedPointer<const Frame> ptr);

private:
	cv::BackgroundSubtractor *substractorPtr;
	cv::Mat foreground;

	cv::Mat prevFrame;
	cv::Mat currentFrame;
	cv::Mat nextFrame;
};

#endif /* _MOVEMENTDETECTOR_H */
