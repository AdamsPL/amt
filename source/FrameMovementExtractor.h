#ifndef _FRAMEMOVEMENTEXTRACTOR_H
#define _FRAMEMOVEMENTEXTRACTOR_H 

#include <opencv2/opencv.hpp>
#include <QSharedPointer>
#include <queue>

class Frame;

class FrameMovementExtractor
{

public:
	FrameMovementExtractor();
	virtual ~FrameMovementExtractor();

	void onNewFrame(const Frame *frame);
	const Frame *createForegroundFrame();

	std::vector<cv::Rect> &getChangedAreas();

private:
	void differentiateFrames(const cv::Mat &curFrame);
	void detectChanges(const cv::Mat &diffFrame);

	std::list<cv::Mat> frameHistory;
	std::vector<cv::Rect> changedAreas;
	cv::Mat result;
};

#endif /* _FRAMEMOVEMENTEXTRACTOR */
