#include "Frame.h"
#include "Samples.h"

#include <gtest/gtest.h>

#include <QCryptographicHash>

using namespace cv;

TEST(TestFrame, testImgConvertion)
{
	QImage img(Samples::exampleFrame);
	Frame frame(imread(Samples::exampleFrame.toStdString()));
	QCryptographicHash hash(QCryptographicHash::Md5);

	img = img.convertToFormat(Frame::getImageFormat());

	hash.addData(reinterpret_cast<const char *>(frame.getImg().constBits()), frame.getImg().byteCount());
	QByteArray frameHash = hash.result();
	
	hash.reset();

	hash.addData(reinterpret_cast<const char *>(img.constBits()), img.byteCount());
	QByteArray imgHash = hash.result();

	EXPECT_TRUE(imgHash == frameHash);
}

TEST(TestFrame, testMatConvertion)
{
	Mat mat = imread(Samples::exampleFrame.toStdString());
	Frame frame(mat);
	QCryptographicHash hash(QCryptographicHash::Md5);

	hash.addData(reinterpret_cast<const char *>(frame.getData().data), frame.getData().total() * frame.getData().channels());
	QByteArray imgHash = hash.result();
	
	hash.reset();

	hash.addData(reinterpret_cast<const char *>(mat.data), mat.total() * mat.channels());
	QByteArray matHash = hash.result();

	EXPECT_TRUE(imgHash == matHash);
}

TEST(TestFrame, testEquality)
{
	Frame exampleFrame(Samples::exampleFrame);
	Frame exampleFrame2(Samples::exampleFrame2);

	EXPECT_TRUE(exampleFrame == exampleFrame);
	EXPECT_TRUE(exampleFrame2 == exampleFrame2);
	EXPECT_FALSE(exampleFrame == exampleFrame2);
	EXPECT_FALSE(exampleFrame2 == exampleFrame);
}
