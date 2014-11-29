#include "FrameMovementExtractor.h"

#include "Frame.h"

#include <QDebug>

using namespace cv;

static const int frameWidth = 320;
static const int frameHeight = 240;
static const int historyLength = 6;

FrameMovementExtractor::FrameMovementExtractor()
{
	result = Mat::zeros(frameHeight, frameWidth, CV_8UC1);
	for (int i = 0; i < historyLength; ++i) {
		frameHistory.push_back(Mat(frameHeight, frameWidth, CV_8UC1));
	}
}

void FrameMovementExtractor::onNewFrame(const Frame *frame)
{
	Mat curFrame;

	resize(frame->getData(), curFrame, Size(frameWidth, frameHeight));
	cvtColor(curFrame, curFrame, CV_RGB2GRAY, 1);
	GaussianBlur(curFrame, curFrame, Size(3, 3), 0, 0, BORDER_DEFAULT);

	differentiateFrames(curFrame);
	detectChanges(result);
}

void FrameMovementExtractor::differentiateFrames(const cv::Mat &curFrame)
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

void FrameMovementExtractor::detectChanges(const cv::Mat &frame)
{
	std::vector<std::vector<cv::Point> > contours;
	Mat diffFrame = frame.clone();
	changedAreas.clear();

	findContours(diffFrame, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	for (int i = 0; i < contours.size(); ++i) {
		Rect shape = boundingRect(contours[i]);
		int size = shape.width * shape.height;
		if (size > 25) {
			changedAreas.push_back(shape);
		}
	}
}

const Frame *FrameMovementExtractor::createForegroundFrame()
{
	return new Frame(result);
}

FrameMovementExtractor::~FrameMovementExtractor()
{
}

std::vector<cv::Rect> &FrameMovementExtractor::getChangedAreas()
{
	return changedAreas;
}
