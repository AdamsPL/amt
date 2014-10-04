#include "Frame.h"
#include "Samples.h"

#include <gtest/gtest.h>

#include <QCryptographicHash>

#include <QDebug>

using namespace cv;

TEST(TestFrame, testInitialisation)
{
	Frame frame;
	EXPECT_TRUE(frame.getImg().isNull());
}

TEST(TestFrame, testConvertion)
{
	Mat mat = imread(Samples::exampleFrame.toStdString());
	Frame frame(mat);
	QCryptographicHash hash(QCryptographicHash::Md5);

	hash.addData(reinterpret_cast<const char *>(frame.getImg().constBits()), frame.getImg().byteCount());
	QByteArray imgHash = hash.result();
	
	hash.reset();

	hash.addData(reinterpret_cast<const char *>(frame.getData().data), frame.getData().total() * frame.getData().channels());
	QByteArray matHash = hash.result();

	EXPECT_FALSE(frame.getImg().isNull());
	EXPECT_EQ(frame.getData().total() * frame.getData().channels(), frame.getImg().byteCount());
	EXPECT_TRUE(imgHash == matHash);
}

TEST(TestFrame, testEquality)
{
	Frame nullFrame;
	Frame exampleFrame(Samples::exampleFrame);

	EXPECT_TRUE(nullFrame == nullFrame);
	EXPECT_TRUE(exampleFrame == exampleFrame);
	EXPECT_FALSE(nullFrame == exampleFrame);
}
