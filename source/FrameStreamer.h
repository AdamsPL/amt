#ifndef _FRAMESTREAMER_H
#define _FRAMESTREAMER_H 

#include <QThreadPool>
#include <QRunnable>

class FrameListener;
class FrameSource;
class Frame;

class FrameStreamer : public QObject, public QRunnable
{
Q_OBJECT

public:
	FrameStreamer();
	virtual ~FrameStreamer();

	void addListener(FrameListener *listener);
	void setFrameSource(FrameSource *source);

	bool isStreaming() const;
	void startStreaming();
	void stopStreaming();

signals:
	void frameReady(const Frame *frame);

protected:
	virtual void run();

private:
	FrameSource *src;
	bool isStreamingFlag;
	QThreadPool threadPool;
};

#endif /* _FRAMESTREAMER */
