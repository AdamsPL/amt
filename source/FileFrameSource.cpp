#include "FileFrameSource.h"

FileFrameSource::FileFrameSource(QString filename)
{
}

bool FileFrameSource::open()
{
	return true;
}

bool FileFrameSource::close()
{
	return true;
}

QImage FileFrameSource::fetchFrame()
{
	return QImage();
}
