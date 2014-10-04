#ifndef _FRAMESOURCE_H
#define _FRAMESOURCE_H 

#include <Frame.h>

#include <QThreadPool>
#include <QRunnable>
#include <QImage>

class FrameSource : public QObject, public QRunnable
{

Q_OBJECT

public:
	FrameSource();

	bool startStreaming();
	bool stopStreaming();
	void run();

	virtual bool open() = 0;
	virtual void close() = 0;
	virtual Frame *fetchFrame() = 0;

signals:
	void frameReady(const Frame &frame);

private:
	bool isStreaming;
	QThreadPool threadPool;
};

#endif /* _FRAMESOURCE_H */
