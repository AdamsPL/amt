#ifndef _FRAMESOURCE_H
#define _FRAMESOURCE_H 

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
	virtual bool close() = 0;
	virtual QImage fetchFrame() = 0;

signals:
	void frameReady(QImage img);

private:
	bool isStreaming;
	QThreadPool threadPool;
};

#endif /* _FRAMESOURCE_H */
