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

	std::vector<cv::Rect> &getChangedAreas();

signals:
	void movementDetected(QSharedPointer<const Frame> ptr);

private:
	void differentiateFrames(const cv::Mat &curFrame);
	void detectChanges(const cv::Mat &diffFrame);

	std::list<cv::Mat> frameHistory;
	std::vector<cv::Rect> changedAreas;
	cv::Mat result;
};

#endif /* _MOVEMENTDETECTOR_H */
