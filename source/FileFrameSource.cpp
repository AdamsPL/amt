#include "FileFrameSource.h"

FileFrameSource::FileFrameSource(QString filename)
	: filename(filename)
{
}

bool FileFrameSource::open()
{
	return capture.open(filename.toStdString());
}
