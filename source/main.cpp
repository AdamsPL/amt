#include <QApplication>

#include "MainWindowWidget.h"
#include "FrameStreamer.h"
#include "FrameMovementExtractor.h"

/*
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;
*/

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	
	FrameStreamer fs;
	MainWindowWidget mainWidget;
	FrameMovementExtractor md;

	mainWidget.setFrameStreamer(&fs);
	mainWidget.setFrameMovementExtractor(&md);
	mainWidget.connectComponents();

	mainWidget.show();

	/*

	Mat frame;
	Mat fore;

	VideoCapture capture;
	BackgroundSubtractorMOG2 bg;

	bg.setInt("history", 4);
	bg.setInt("nmixtures", 2);
	bg.setBool("detectShadows", false);

	if (argc < 2) {
		cout << "capture.open(): " << capture.open(0) << endl;
	}else {
		cout << "capture.open(): " << capture.open(argv[1]) << endl;
	}

	std::vector<std::vector<cv::Point> > contours;


	while(capture.read(frame)) {
		bg.operator()(frame, fore);

		GaussianBlur(fore, fore, Size(7,7), 0, 0, BORDER_DEFAULT);
		threshold(fore, fore, 80.0f,255,CV_THRESH_BINARY);

		cv::findContours(fore,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE);

		for (int i = 0; i < contours.size(); ++i) {
			Rect rect = boundingRect(contours[i]);
			rectangle(frame, rect, Scalar(0, 0, 255));
		}

		imshow("frame", frame);
		imshow("fore", fore);
		waitKey(1);
	}

	return 0;

	*/
	return app.exec();
}
