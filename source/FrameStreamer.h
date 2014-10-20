#ifndef _FRAMESTREAMER_H
#define _FRAMESTREAMER_H 

#include <QThreadPool>
#include <QRunnable>

class FrameListener;
class FrameSource;
class Frame;
class Timer;

class FrameStreamer : public QObject, public QRunnable
{
Q_OBJECT

public:
	FrameStreamer();
	virtual ~FrameStreamer();

	void addListener(FrameListener *listener);
	void setFrameSource(FrameSource *source);
	void setTimer(Timer *timer);
	void setFrameDelay(int delay);

	bool isStreaming() const;
	void startStreaming();
	void stopStreaming();

signals:
	void frameReady(QSharedPointer<const Frame> frame);

protected:
	virtual void run();

private:
	FrameSource *src;
	Timer *timer;
	bool isStreamingFlag;
	QThreadPool threadPool;
	int frameDelay;
};

#endif /* _FRAMESTREAMER */
