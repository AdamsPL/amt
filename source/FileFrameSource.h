#ifndef _FILEFRAMESOURCE_H
#define _FILEFRAMESOURCE_H 

#include "FrameSource.h"

#include <QString>

class FileFrameSource : public FrameSource
{
public:
	FileFrameSource(QString filename);

	virtual bool open();
	virtual bool close();
	virtual QImage fetchFrame();
};

#endif /* _FILEFRAMESOURCE_H */
