#ifndef _DIFFALGORITHM_H
#define _DIFFALGORITHM_H 

#include "EventMonitor.h"
#include "EventHandler.h"

#include <opencv2/opencv.hpp>
#include <QSharedPointer>
#include <queue>

class Frame;

class DiffAlgorithm : public EventHandler
{

public:
	DiffAlgorithm(EventMonitor *monitor);
	virtual ~DiffAlgorithm();

	virtual void handleNewFrame(QSharedPointer<const Frame> framePtr);

	inline const std::vector<cv::Rect> &getChangedAreas() const { return changedAreas; }
private:
	void differentiateFrames(const cv::Mat &curFrame);
	void detectChanges(const cv::Mat &diffFrame);

	std::list<cv::Mat> frameHistory;
	std::vector<cv::Rect> changedAreas;
	cv::Mat result;
};

#endif /* _DIFFALGORITHM_H */
