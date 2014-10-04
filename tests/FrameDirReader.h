#ifndef _FRAME_DIR_READER_H
#define _FRAME_DIR_READER_H

#include <QString>
#include <QImage>
#include <QDir>
#include <QList>

class FrameDirReader
{
public:
	bool readExpectedFrames(QString frameDir);
	void verifyFrame(const QImage &frame);
	int getUnusedFrames();

private:
	QImage popFrame();
	QList<QImage> expectedFrames;
};

#endif
