#ifndef _MOVEMENTDETECTOR_H
#define _MOVEMENTDETECTOR_H 

#include "FrameListener.h"

#include <opencv2/opencv.hpp>
#include <QSharedPointer>
#include <queue>

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
	void differentiateFrames(const cv::Mat &curFrame);
	void detectContours(const cv::Mat &diffFrame);

	std::list<cv::Mat> frameHistory;
	cv::Mat result;
};

#endif /* _MOVEMENTDETECTOR_H */
