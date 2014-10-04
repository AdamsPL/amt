#include "FrameDirReader.h"

#include <gtest/gtest.h>

bool FrameDirReader::readExpectedFrames(QString frameDir)
{
	QDir dir(frameDir);
	QString filename;

	foreach(filename, dir.entryList(QDir::Files)) {
		expectedFrames << QImage(filename);
	}

	return (getUnusedFrames() > 0);
}

void FrameDirReader::verifyFrame(const QImage &frame)
{
	EXPECT_EQ(frame, popFrame());
}

int FrameDirReader::getUnusedFrames()
{
	return expectedFrames.size();
}

QImage FrameDirReader::popFrame()
{
	if (getUnusedFrames() == 0)
		return QImage();

	QImage result = expectedFrames.first();
	expectedFrames.removeFirst();

	return result;
}

