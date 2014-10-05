#include "FrameDirReader.h"


FrameDirReader::~FrameDirReader()
{
	Frame *f;
	foreach(f, expectedFrames)
		delete f;
	expectedFrames.clear();
}

bool FrameDirReader::readExpectedFrames(QString frameDir)
{
	QDir dir(frameDir);
	QString filename;

	foreach(filename, dir.entryList(QDir::Files)) {
		Frame *frame = new Frame(dir.filePath(filename));
		expectedFrames << frame;
	}

	return (getUnusedFrames() > 0);
}

int FrameDirReader::getUnusedFrames()
{
	return expectedFrames.size();
}

Frame *FrameDirReader::popFrame()
{
	if (getUnusedFrames() == 0)
		return 0;

	Frame *result = expectedFrames.first();
	expectedFrames.removeFirst();

	return result;
}

