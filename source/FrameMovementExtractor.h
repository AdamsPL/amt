#ifndef _FRAMEMOVEMENTEXTRACTOR_H
#define _FRAMEMOVEMENTEXTRACTOR_H 

#include "FrameListener.h"

#include <opencv2/opencv.hpp>
#include <QSharedPointer>
#include <queue>

class FrameMovementExtractor : public FrameListener
{
Q_OBJECT

public:
	FrameMovementExtractor();
	virtual ~FrameMovementExtractor();

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

#endif /* _FRAMEMOVEMENTEXTRACTOR */
