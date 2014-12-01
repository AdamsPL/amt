#include "DiffAlgorithm.h"

#include "Frame.h"
#include "Area.h"

#include <QMap>
#include <QDebug>

using namespace cv;

static const int frameWidth = 320;
static const int frameHeight = 240;
static const int historyLength = 6;

DiffAlgorithm::DiffAlgorithm(const EventMonitor &monitor)
	: EventHandler(monitor)
{
	result = Mat::zeros(frameHeight, frameWidth, CV_8UC1);
	for (int i = 0; i < historyLength; ++i) {
		frameHistory.push_back(Mat(frameHeight, frameWidth, CV_8UC1));
	}
}

DiffAlgorithm::~DiffAlgorithm()
{
}

void DiffAlgorithm::differentiateFrames(const cv::Mat &curFrame)
{
	Mat tmp;
	Mat erodeKernl = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
	Mat dilateKernl = getStructuringElement(MORPH_ELLIPSE, Size(2, 2));

	result = Mat::zeros(frameHeight, frameWidth, CV_8UC1);

	for(std::list<Mat>::const_iterator iter = frameHistory.begin(); iter != frameHistory.end(); iter++) {
		absdiff(*iter, curFrame, tmp);
		result += tmp / historyLength;
	}
	erode(result, result, erodeKernl);
	dilate(result, result, dilateKernl);
	threshold(result, result, 2, 255, THRESH_BINARY);

	frameHistory.push_back(curFrame);
	frameHistory.pop_front();
}

void DiffAlgorithm::detectChanges(const cv::Mat &frame)
{
	std::vector<std::vector<cv::Point> > contours;
	Mat diffFrame = frame.clone();
	changedAreas.clear();

	findContours(diffFrame, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	for (int i = 0; i < contours.size(); ++i) {
		Rect shape = boundingRect(contours[i]);
		changedAreas.push_back(QRectF(
			(float)shape.x / frameWidth,
			(float)shape.y / frameHeight,
			(float)shape.width / frameWidth,
			(float)shape.height / frameHeight
		));
	}
	assignChangesToGroups();
}

const Area *DiffAlgorithm::findBestMatchingArea(const QList<QRectF> &changes) const
{
	const Area *area;
	QRectF rect;
	QMap<const Area*, float> weightMap;
	float weight;
	const Area *bestMatch = 0;

	foreach(rect, changes) {
		area = findArea(rect.center());
		weight = rect.width() * rect.height();

		if (!weightMap.contains(area))
			weightMap[area] = 0.0f;
		weightMap[area] += weight;
	}
	foreach(area, weightMap.keys()) {
		if (!bestMatch || weightMap[area] > weightMap[bestMatch]) {
			bestMatch = area;
		}
	}

	return bestMatch;
}

void DiffAlgorithm::assignChangesToGroups()
{
	QString group;
	QMap<QString, QRectF> changeMap;
	const Area *area;

	for (int i = 0; i < changedAreas.size(); ++i) {
		QString group = findAreaGroup(changedAreas[i]);
		changeMap.insertMulti(group, changedAreas[i]);
	}

	foreach(group, changeMap.uniqueKeys()) {
		if (group.isEmpty())
			continue;
		area = findBestMatchingArea(changeMap.values(group));
		lastVisited[group] = area;
	}
	foreach(area, lastVisited.values()) {
		ticks[area] = getAreaTicks(area) + 1;
	}
}

void DiffAlgorithm::handleNewFrame(QSharedPointer<const Frame> framePtr)
{
	const Frame *frame = framePtr.data();
	Mat curFrame;

	resize(frame->getData(), curFrame, Size(frameWidth, frameHeight));
	cvtColor(curFrame, curFrame, CV_RGB2GRAY, 1);
	GaussianBlur(curFrame, curFrame, Size(3, 3), 0, 0, BORDER_DEFAULT);

	differentiateFrames(curFrame);
	detectChanges(result);
	getEventMonitor().emitNewDiffFrameEvent(QSharedPointer<const Frame>(new Frame(result)));
}

void DiffAlgorithm::addArea(const Area *area)
{
	areas.push_back(area);
}

const Area *DiffAlgorithm::findArea(const QPointF &point) const
{
	const Area *area;

	foreach(area, areas) {
		if (area->contains(point)) {
			return area;
		}
	}
	return 0;
}

QString DiffAlgorithm::findAreaGroup(const QRectF &rect) const
{
	const Area *area = findArea(rect.center());
	if (area)
		return area->getGroup();
	else
		return QString();
}

int DiffAlgorithm::getAreaTicks(const Area *area)
{
	if(!ticks.contains(area))
		return 0;
	else
		return ticks[area];
}
