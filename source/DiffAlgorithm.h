#ifndef _DIFFALGORITHM_H
#define _DIFFALGORITHM_H 

#include "EventMonitor.h"
#include "EventHandler.h"

#include <opencv2/opencv.hpp>
#include <QSharedPointer>
#include <QVector>
#include <QList>
#include <QMap>

class Frame;
class Area;

class DiffAlgorithm : public EventHandler
{

public:
	DiffAlgorithm(const EventMonitor &monitor);
	virtual ~DiffAlgorithm();

	virtual void handleNewFrame(QSharedPointer<const Frame> framePtr);

	inline const QVector<QRectF> &getChangedAreas() const { return changedAreas; }
	void addArea(const Area *area);
	
	int getAreaTicks(const Area *area);

private:
	QString findAreaGroup(const QRectF &rect) const;
	const Area *findArea(const QPointF &point) const;
	void differentiateFrames(const cv::Mat &curFrame);
	void detectChanges(const cv::Mat &diffFrame);
	void assignChangesToGroups();
	const Area *findBestMatchingArea(const QList<QRectF> &changes) const;

	std::list<cv::Mat> frameHistory;
	QVector<QRectF> changedAreas;
	cv::Mat result;

	std::vector<const Area*> areas;
	QMap<QString, const Area*> lastVisited;
	QMap<const Area*, float> ticks;
};

#endif /* _DIFFALGORITHM_H */
