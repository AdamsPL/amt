#ifndef _FRAME_DIR_READER_H
#define _FRAME_DIR_READER_H

#include "Frame.h"

#include <QString>
#include <QDir>
#include <QList>

class FrameDirReader
{
public:
	~FrameDirReader();

	bool readExpectedFrames(QString frameDir);
	int getUnusedFrames();
	Frame *popFrame();

private:
	QList<Frame*> expectedFrames;
};

#endif
