#ifndef _FILEFRAMESOURCE_H
#define _FILEFRAMESOURCE_H 

#include "OpenCVFrameSource.h"

#include <QString>

class FileFrameSource : public OpenCVFrameSource
{
public:
	FileFrameSource(QString filename);

	virtual bool open();

private:
	QString filename;
};

#endif /* _FILEFRAMESOURCE_H */
