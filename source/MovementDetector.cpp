#include "MovementDetector.h"

#include "Frame.h"

#include <QDebug>

using namespace cv;

MovementDetector::MovementDetector()
	: foreground(10, 10, CV_8UC4), background(10, 10, CV_8UC4)
{
	substractorPtr = new BackgroundSubtractorMOG2();
	substractorPtr->setInt("nmixtures", 3);
	substractorPtr->setBool("detectShadows", false);
	substractorPtr->setInt("history", 4);
}

void MovementDetector::onNewFrame(const Frame *frame)
{
	(*substractorPtr)(frame->getData(), foreground);
	substractorPtr->getBackgroundImage(background);
}

const Frame *MovementDetector::createForegroundFrame()
{
	return new Frame(foreground);
}

const Frame *MovementDetector::createBackgroundFrame()
{
	return new Frame(background);
}

MovementDetector::~MovementDetector()
{
	delete substractorPtr;
}
