#include "MovementDetector.h"

#include "Frame.h"

#include <QDebug>

using namespace cv;

MovementDetector::MovementDetector()
	: foreground(10, 10, CV_8UC3)
{
	substractorPtr = new BackgroundSubtractorMOG();
	//substractorPtr->setInt("nmixtures", 1);
	//substractorPtr->setBool("detectShadows", false);
	//substractorPtr->setInt("history", 1);
	prevFrame = Mat(480, 640, CV_8UC1);
	currentFrame = Mat(480, 640, CV_8UC1);
	nextFrame = Mat(480, 640, CV_8UC1);
}

void MovementDetector::onNewFrame(const Frame *frame)
{
	const int size = 127;
	Mat erodeKernl = getStructuringElement(MORPH_ELLIPSE, Size(size, size));
	Mat dilateKernl = getStructuringElement(MORPH_ELLIPSE, Size(size, size));
	Mat result, diff1, diff2;

	std::vector<std::vector<cv::Point> > contours;

	prevFrame = currentFrame.clone();
	currentFrame = nextFrame.clone();

	cvtColor(frame->getData(), nextFrame, CV_RGB2GRAY, 1);
	resize(nextFrame, nextFrame, Size(640, 480));
	//blur(nextFrame, nextFrame, Size(3, 3));

	absdiff(prevFrame, nextFrame, diff1);
	absdiff(currentFrame, nextFrame, diff2);
	bitwise_and(diff1, diff2, result);

	GaussianBlur(result, result, Size(3, 3), 0, 0, BORDER_DEFAULT);
	threshold(result, result, 15, 255, CV_THRESH_BINARY);
	dilate(foreground, foreground, dilateKernl);
	erode(foreground, foreground, erodeKernl);

	findContours(result, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	
	for (int i = 0; i < contours.size(); ++i) {
		std::vector<cv::Point> hull;
		convexHull(contours[i], hull);
		fillConvexPoly(result, &hull[0], hull.size(), Scalar(255, 255, 255));
	}
	emit movementDetected(QSharedPointer<const Frame>(new Frame(result)));
}

/*
void MovementDetector::onNewFrame(const Frame *frame)
{
	Mat erodeKernl = getStructuringElement(MORPH_ELLIPSE, Size(2, 2));
	Mat dilateKernl = getStructuringElement(MORPH_ELLIPSE, Size(2, 2));

	Mat tmpFrame;
	std::vector<std::vector<cv::Point> > contours;

	//resize(frame->getData(), tmpFrame, Size(320, 240));
	blur(tmpFrame, tmpFrame, Size(3, 3));

	(*substractorPtr)(tmpFrame, foreground);

	//GaussianBlur(foreground, foreground, Size(15, 15), 0, 0, BORDER_DEFAULT);

	//threshold(foreground, foreground, 120.0f,255,CV_THRESH_BINARY);
	erode(foreground, foreground, erodeKernl);
	dilate(foreground, foreground, dilateKernl);

	findContours(foreground,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE);
	
	for (int i = 0; i < contours.size(); ++i) {
		Rect rect = boundingRect(contours[i]);
		int size = rect.width * rect.height;
		if (size >= 36)
			rectangle(foreground, rect, Scalar(255, 255, 255));
	}

	emit movementDetected(QSharedPointer<const Frame>(createForegroundFrame()));
}
*/

const Frame *MovementDetector::createForegroundFrame()
{
	return new Frame(foreground);
}

MovementDetector::~MovementDetector()
{
	delete substractorPtr;
}
